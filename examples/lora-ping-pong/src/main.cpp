/*
 * LoRa ping/pong across two boards in this library:
 *   - LilyGO T3 LoRa32 V1.6.1  (ESP32-PICO-D4 + SX1276)
 *   - Seeed Wio-SX1262 + XIAO ESP32-S3 kit (SX1262)
 *
 * One source file builds all four combinations; the board comes from a
 * -DBOARD_* flag and the role from -DROLE_PINGER. See platformio.ini.
 *
 * The pinger sends a ping every PING_PERIOD_MS and waits for a pong. The
 * ponger answers every ping addressed to it, and puts the RSSI/SNR it
 * measured into the reply — so one console shows the link quality in BOTH
 * directions, which is the thing that actually tells you whether a link is
 * healthy.
 */

#include <Arduino.h>
#include <RadioLib.h>
#include <SPI.h>

#include "protocol.h"

/* ------------------------------------------------------------------ wiring */
#if defined(BOARD_T3_V16)
static const int PIN_SCK = 5, PIN_MISO = 19, PIN_MOSI = 27;
static const int PIN_NSS = 18, PIN_RST = 23, PIN_DIO0 = 26, PIN_DIO1 = 33;
/* SX127x: the "irq" argument is DIO0, the "gpio" argument is DIO1. */
SX1276 radio = new Module(PIN_NSS, PIN_DIO0, PIN_RST, PIN_DIO1);
static const char *BOARD_NAME = "T3 LoRa32 V1.6.1 / SX1276";

#elif defined(BOARD_XIAO_SX1262)
static const int PIN_SCK = 7, PIN_MISO = 8, PIN_MOSI = 9;
static const int PIN_NSS = 41, PIN_RST = 42, PIN_DIO1 = 39, PIN_BUSY = 40;
/* SX126x: the "irq" argument is DIO1, the "gpio" argument is BUSY. */
SX1262 radio = new Module(PIN_NSS, PIN_DIO1, PIN_RST, PIN_BUSY);
static const char *BOARD_NAME = "Wio-SX1262 + XIAO ESP32-S3";

#else
#error "Define BOARD_T3_V16 or BOARD_XIAO_SX1262 in platformio.ini"
#endif

/* -------------------------------------------------------------- air params */
/* Every one of these must match on both ends or the receiver hears nothing. */
#ifndef FREQ_MHZ
#define FREQ_MHZ 915.0     /* 868.0 in EU. Must suit the module actually fitted. */
#endif
#define BW_KHZ      125.0
#define SPREAD_FACT 9      /* 7 = fast/short, 12 = slow/far */
#define CODING_RATE 7      /* 4/7 */
#define SYNC_WORD   0x12   /* private network; RadioLib maps this per chip family */
#define TX_DBM      17
#define PREAMBLE    8

#define PING_PERIOD_MS 2000
#define PONG_WAIT_MS   1500

/* --------------------------------------------------------------- node ids */
#ifndef NODE_ID
#define NODE_ID 1
#endif
#ifndef PEER_ID
#define PEER_ID 2
#endif

/* ------------------------------------------------------------------ state */
volatile bool rx_flag = false;
static uint16_t seq = 0;
static uint32_t sent_at = 0;
static bool awaiting_pong = false;
static uint32_t sent_count = 0, recv_count = 0;

#if defined(ESP32)
ICACHE_RAM_ATTR
#endif
static void on_rx() { rx_flag = true; }

static void radio_fail(const char *what, int state) {
    Serial.printf("%s failed, code %d — halting\n", what, state);
    while (true) { delay(1000); }
}

static void fill_header(msg_header_t &h, uint8_t type, uint16_t s) {
    h.magic = PROTO_MAGIC;
    h.version = PROTO_VERSION;
    h.type = type;
    h.src = NODE_ID;
    h.dst = PEER_ID;
    h.seq = s;
}

/* Returns true when the header is one of ours and addressed to this node. */
static bool header_ok(const msg_header_t &h, uint8_t expect_type) {
    if (h.magic != PROTO_MAGIC) return false;
    if (h.version != PROTO_VERSION) {
        Serial.printf("  dropped: protocol v%u, this node speaks v%u\n",
                      h.version, PROTO_VERSION);
        return false;
    }
    if (h.type != expect_type) return false;
    if (h.dst != NODE_ID && h.dst != ADDR_BROADCAST) return false;
    return true;
}

static void send_ping() {
    ping_msg_t m;
    fill_header(m.h, MSG_PING, ++seq);
    m.t_ms = millis();

    int state = radio.transmit((uint8_t *)&m, sizeof(m));
    if (state != RADIOLIB_ERR_NONE) {
        Serial.printf("ping %u: transmit failed, code %d\n", seq, state);
        return;
    }
    sent_count++;
    sent_at = millis();
    awaiting_pong = true;
    Serial.printf("ping %u sent (%u bytes)\n", seq, (unsigned)sizeof(m));

    /* transmit() leaves the radio idle — go back to listening. */
    radio.startReceive();
}

static void handle_ping(const uint8_t *buf, size_t len) {
    if (len != sizeof(ping_msg_t)) return;          /* length first */
    ping_msg_t in;
    memcpy(&in, buf, sizeof(in));
    if (!header_ok(in.h, MSG_PING)) return;         /* magic second */

    float rssi = radio.getRSSI();
    float snr = radio.getSNR();
    Serial.printf("ping %u from node %u  RSSI %.1f dBm  SNR %.1f dB\n",
                  in.h.seq, in.h.src, rssi, snr);

    pong_msg_t out;
    fill_header(out.h, MSG_PONG, in.h.seq);         /* echo the sequence */
    out.h.dst = in.h.src;                           /* answer the sender */
    out.t_ms = in.t_ms;                             /* echo, do not restamp */
    out.rssi_cdbm = (int16_t)lround(rssi * 100.0f);
    out.snr_cdb = (int16_t)lround(snr * 100.0f);

    int state = radio.transmit((uint8_t *)&out, sizeof(out));
    if (state != RADIOLIB_ERR_NONE)
        Serial.printf("  pong %u: transmit failed, code %d\n", in.h.seq, state);
    radio.startReceive();
}

static void handle_pong(const uint8_t *buf, size_t len) {
    if (len != sizeof(pong_msg_t)) return;
    pong_msg_t in;
    memcpy(&in, buf, sizeof(in));
    if (!header_ok(in.h, MSG_PONG)) return;
    if (in.h.seq != seq) {
        Serial.printf("  stale pong %u (waiting for %u), ignored\n", in.h.seq, seq);
        return;
    }

    recv_count++;
    awaiting_pong = false;
    uint32_t rtt = millis() - in.t_ms;
    Serial.printf("pong %u  rtt %lu ms  here: RSSI %.1f dBm SNR %.1f dB"
                  "  there: RSSI %.2f dBm SNR %.2f dB  loss %lu/%lu\n",
                  in.h.seq, (unsigned long)rtt,
                  radio.getRSSI(), radio.getSNR(),
                  in.rssi_cdbm / 100.0, in.snr_cdb / 100.0,
                  (unsigned long)(sent_count - recv_count),
                  (unsigned long)sent_count);
}

void setup() {
    Serial.begin(115200);
    delay(2000);  /* native-USB boards need a moment before the port exists */

    Serial.printf("\n%s — node %u, %s, %.1f MHz SF%d BW%.0f\n",
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
    /* The kit's TCXO is powered from DIO3 at 1.8 V. Leave this at the default
     * and the radio initialises cleanly, then never hears a thing. */
    state = radio.begin(FREQ_MHZ, BW_KHZ, SPREAD_FACT, CODING_RATE,
                        SYNC_WORD, TX_DBM, PREAMBLE, 1.8);
    if (state != RADIOLIB_ERR_NONE) radio_fail("begin", state);
    /* DIO2 drives the antenna switch on this module. */
    state = radio.setDio2AsRfSwitch(true);
    if (state != RADIOLIB_ERR_NONE) radio_fail("setDio2AsRfSwitch", state);
#else
    state = radio.begin(FREQ_MHZ, BW_KHZ, SPREAD_FACT, CODING_RATE,
                        SYNC_WORD, TX_DBM, PREAMBLE);
    if (state != RADIOLIB_ERR_NONE) radio_fail("begin", state);
#endif

    radio.setPacketReceivedAction(on_rx);
    state = radio.startReceive();
    if (state != RADIOLIB_ERR_NONE) radio_fail("startReceive", state);

    Serial.println("radio up, listening");
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
            Serial.println("packet with bad CRC — the PHY caught it");
        }
        radio.startReceive();
    }

#ifdef ROLE_PINGER
    static uint32_t last_ping = 0;

    if (awaiting_pong && millis() - sent_at > PONG_WAIT_MS) {
        awaiting_pong = false;
        Serial.printf("ping %u: no pong in %d ms  loss %lu/%lu\n",
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
