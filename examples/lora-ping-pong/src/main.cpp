/*
 * LoRa ping/pong example.
 *
 * Supported boards:
 *   BOARD_T3_V16        LilyGO T3 LoRa32 V1.6.1, ESP32-PICO-D4 with SX1276
 *   BOARD_XIAO_SX1262   Seeed Wio-SX1262 with XIAO ESP32-S3, SX1262
 *
 * Supported roles:
 *   ROLE_PINGER defined    transmits a ping every PING_PERIOD_MS and reports
 *                          the matching pong
 *   ROLE_PINGER undefined  transmits one pong for each ping addressed to this
 *                          node
 *
 * The board and role are selected by preprocessor definitions set in
 * platformio.ini. The two nodes may use different boards.
 *
 * The pong carries the RSSI and SNR measured by the responder. The pinger
 * therefore reports signal quality for both transmission directions.
 */

#include <Arduino.h>
#include <RadioLib.h>
#include <SPI.h>

#include "protocol.h"

/* ---------------------------------------------------------------- hardware */
#if defined(BOARD_T3_V16)
static const int PIN_SCK = 5, PIN_MISO = 19, PIN_MOSI = 27;
static const int PIN_NSS = 18, PIN_RST = 23, PIN_DIO0 = 26, PIN_DIO1 = 33;
/* SX127x Module() argument order: NSS, DIO0, RESET, DIO1. */
SX1276 radio = new Module(PIN_NSS, PIN_DIO0, PIN_RST, PIN_DIO1);
static const char *BOARD_NAME = "T3 LoRa32 V1.6.1 / SX1276";

#elif defined(BOARD_XIAO_SX1262)
static const int PIN_SCK = 7, PIN_MISO = 8, PIN_MOSI = 9;
static const int PIN_NSS = 41, PIN_RST = 42, PIN_DIO1 = 39, PIN_BUSY = 40;
/* SX126x Module() argument order: NSS, DIO1, RESET, BUSY. */
SX1262 radio = new Module(PIN_NSS, PIN_DIO1, PIN_RST, PIN_BUSY);
static const char *BOARD_NAME = "Wio-SX1262 + XIAO ESP32-S3";

#else
#error "Define BOARD_T3_V16 or BOARD_XIAO_SX1262 in platformio.ini"
#endif

/* ------------------------------------------------------- radio parameters */
/* These values must be identical on both nodes. A difference in any one of
 * them results in no reception and no error report. */
#ifndef FREQ_MHZ
#define FREQ_MHZ 915.0     /* 868.0 for European 868 MHz modules */
#endif
#define BW_KHZ      125.0
#define SPREAD_FACT 9      /* range 7 to 12 */
#define CODING_RATE 7      /* 4/7 */
#define SYNC_WORD   0x12   /* private network value; RadioLib encodes it per chip */
#define TX_DBM      17
#define PREAMBLE    8

#define PING_PERIOD_MS 2000
#define PONG_WAIT_MS   1500

/* ------------------------------------------------------- node identifiers */
#ifndef NODE_ID
#define NODE_ID 1
#endif
#ifndef PEER_ID
#define PEER_ID 2
#endif

/* ------------------------------------------------------------------ state */
volatile bool rx_flag = false;   /* set by the radio interrupt handler */
static uint16_t seq = 0;         /* sequence number of the most recent ping */
static uint32_t sent_at = 0;     /* millis() when that ping was transmitted */
static bool awaiting_pong = false;
static uint32_t sent_count = 0;
static uint32_t recv_count = 0;

#if defined(ESP32)
ICACHE_RAM_ATTR
#endif
static void on_rx() { rx_flag = true; }

static void halt_on_error(const char *operation, int state) {
    Serial.printf("%s returned %d. Execution stopped.\n", operation, state);
    while (true) { delay(1000); }
}

static void fill_header(msg_header_t &h, uint8_t type, uint16_t sequence) {
    h.magic = PROTO_MAGIC;
    h.version = PROTO_VERSION;
    h.type = type;
    h.src = NODE_ID;
    h.dst = PEER_ID;
    h.seq = sequence;
}

/* Returns true if the header is valid, of the expected type, and addressed to
 * this node. */
static bool header_accepted(const msg_header_t &h, uint8_t expected_type) {
    if (h.magic != PROTO_MAGIC) return false;
    if (h.version != PROTO_VERSION) {
        Serial.printf("  discarded: message version %u, node version %u\n",
                      h.version, PROTO_VERSION);
        return false;
    }
    if (h.type != expected_type) return false;
    if (h.dst != NODE_ID && h.dst != ADDR_BROADCAST) return false;
    return true;
}

static void send_ping() {
    ping_msg_t m;
    fill_header(m.h, MSG_PING, ++seq);
    m.t_ms = millis();

    int state = radio.transmit((uint8_t *)&m, sizeof(m));
    if (state != RADIOLIB_ERR_NONE) {
        Serial.printf("ping %u: transmit returned %d\n", seq, state);
        return;
    }
    sent_count++;
    sent_at = millis();
    awaiting_pong = true;
    Serial.printf("ping %u transmitted, %u bytes\n", seq, (unsigned)sizeof(m));

    /* transmit() leaves the radio in standby. Reception must be restarted. */
    radio.startReceive();
}

static void handle_ping(const uint8_t *buf, size_t len) {
    if (len != sizeof(ping_msg_t)) return;   /* length check precedes field access */
    ping_msg_t in;
    memcpy(&in, buf, sizeof(in));
    if (!header_accepted(in.h, MSG_PING)) return;

    float rssi = radio.getRSSI();
    float snr = radio.getSNR();
    Serial.printf("ping %u received from node %u, RSSI %.1f dBm, SNR %.1f dB\n",
                  in.h.seq, in.h.src, rssi, snr);

    pong_msg_t out;
    fill_header(out.h, MSG_PONG, in.h.seq);  /* sequence number is copied */
    out.h.dst = in.h.src;
    out.t_ms = in.t_ms;                      /* timestamp is copied unmodified */
    out.rssi_cdbm = (int16_t)lround(rssi * 100.0f);
    out.snr_cdb = (int16_t)lround(snr * 100.0f);

    int state = radio.transmit((uint8_t *)&out, sizeof(out));
    if (state != RADIOLIB_ERR_NONE)
        Serial.printf("  pong %u: transmit returned %d\n", in.h.seq, state);
    radio.startReceive();
}

static void handle_pong(const uint8_t *buf, size_t len) {
    if (len != sizeof(pong_msg_t)) return;
    pong_msg_t in;
    memcpy(&in, buf, sizeof(in));
    if (!header_accepted(in.h, MSG_PONG)) return;
    if (in.h.seq != seq) {
        Serial.printf("  pong %u discarded, current sequence is %u\n",
                      in.h.seq, seq);
        return;
    }

    recv_count++;
    awaiting_pong = false;
    uint32_t rtt = millis() - in.t_ms;

    /* "local" values describe the pong as received here. "remote" values
     * describe the ping as received by the other node. */
    Serial.printf("pong %u, round trip %lu ms, "
                  "local RSSI %.1f dBm SNR %.1f dB, "
                  "remote RSSI %.2f dBm SNR %.2f dB, "
                  "unanswered %lu of %lu\n",
                  in.h.seq, (unsigned long)rtt,
                  radio.getRSSI(), radio.getSNR(),
                  in.rssi_cdbm / 100.0, in.snr_cdb / 100.0,
                  (unsigned long)(sent_count - recv_count),
                  (unsigned long)sent_count);
}

void setup() {
    Serial.begin(115200);
    delay(2000);  /* boards with native USB require a delay before the port exists */

    Serial.printf("\n%s, node %u, role %s, %.1f MHz, SF%d, BW %.0f kHz\n",
                  BOARD_NAME, (unsigned)NODE_ID,
#ifdef ROLE_PINGER
                  "pinger",
#else
                  "ponger",
#endif
                  (double)FREQ_MHZ, SPREAD_FACT, (double)BW_KHZ);

    SPI.begin(PIN_SCK, PIN_MISO, PIN_MOSI, PIN_NSS);

    int state;
#if defined(BOARD_XIAO_SX1262)
    /* On this module DIO3 supplies the TCXO at 1.8 V. Without this value the
     * radio initialises without error and receives no packets. */
    state = radio.begin(FREQ_MHZ, BW_KHZ, SPREAD_FACT, CODING_RATE,
                        SYNC_WORD, TX_DBM, PREAMBLE, 1.8);
    if (state != RADIOLIB_ERR_NONE) halt_on_error("begin()", state);
    /* On this module DIO2 controls the antenna switch. */
    state = radio.setDio2AsRfSwitch(true);
    if (state != RADIOLIB_ERR_NONE) halt_on_error("setDio2AsRfSwitch()", state);
#else
    state = radio.begin(FREQ_MHZ, BW_KHZ, SPREAD_FACT, CODING_RATE,
                        SYNC_WORD, TX_DBM, PREAMBLE);
    if (state != RADIOLIB_ERR_NONE) halt_on_error("begin()", state);
#endif

    radio.setPacketReceivedAction(on_rx);
    state = radio.startReceive();
    if (state != RADIOLIB_ERR_NONE) halt_on_error("startReceive()", state);

    Serial.println("Radio initialised. Receiving.");
}

void loop() {
    if (rx_flag) {
        rx_flag = false;

        size_t len = radio.getPacketLength();
        uint8_t buf[64];
        if (len == 0 || len > sizeof(buf)) {
            radio.startReceive();
            return;
        }
        int state = radio.readData(buf, len);
        if (state == RADIOLIB_ERR_NONE) {
#ifdef ROLE_PINGER
            handle_pong(buf, len);
#else
            handle_ping(buf, len);
#endif
        } else if (state == RADIOLIB_ERR_CRC_MISMATCH) {
            Serial.println("Packet discarded: CRC mismatch reported by the radio.");
        }
        radio.startReceive();
    }

#ifdef ROLE_PINGER
    static uint32_t last_ping = 0;

    if (awaiting_pong && millis() - sent_at > PONG_WAIT_MS) {
        awaiting_pong = false;
        Serial.printf("ping %u: no pong within %d ms, unanswered %lu of %lu\n",
                      seq, PONG_WAIT_MS,
                      (unsigned long)(sent_count - recv_count),
                      (unsigned long)sent_count);
    }
    if (!awaiting_pong && millis() - last_ping > PING_PERIOD_MS) {
        last_ping = millis();
        send_ping();
    }
#endif
}
