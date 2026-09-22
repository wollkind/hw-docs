#pragma once
#include <stdint.h>

/*
 * One header, both nodes. Edit it here and rebuild both ends — a protocol
 * header that lives in one place is the only version control a two-node link
 * gets.
 *
 * Rules this file follows:
 *  1. Fixed-width types only. `int` is 16 bits on an AVR and 32 on an ESP32.
 *  2. Packed structs. Without it the compiler inserts padding that differs
 *     between architectures, and the bytes on air stop matching the bytes in
 *     memory.
 *  3. Every message starts with the same header, so a receiver can read the
 *     type before it knows the shape.
 *  4. The two message types are DIFFERENT SIZES. Dispatch on length first and
 *     magic second: a truncated or foreign packet fails the length test before
 *     anything reads its fields.
 *  5. A version byte, so an old node meeting a new one says so instead of
 *     decoding garbage.
 */

#define PROTO_MAGIC   0x4C50u  /* 'LP', little-endian on both boards */
#define PROTO_VERSION 1

#define ADDR_BROADCAST 0xFF

enum : uint8_t {
    MSG_PING = 1,
    MSG_PONG = 2,
};

struct __attribute__((packed)) msg_header_t {
    uint16_t magic;    /* PROTO_MAGIC */
    uint8_t  version;  /* PROTO_VERSION */
    uint8_t  type;     /* MSG_* */
    uint8_t  src;      /* node id of the sender */
    uint8_t  dst;      /* node id, or ADDR_BROADCAST */
    uint16_t seq;      /* incremented per ping, echoed unchanged in the pong */
};

struct __attribute__((packed)) ping_msg_t {
    msg_header_t h;
    uint32_t t_ms;     /* sender's millis() at transmit */
};

struct __attribute__((packed)) pong_msg_t {
    msg_header_t h;
    uint32_t t_ms;      /* echoed from the ping, untouched */
    int16_t  rssi_cdbm; /* RSSI of the ping at the responder, dBm x100 */
    int16_t  snr_cdb;   /* SNR of the ping at the responder, dB x100 */
};

/* Sizes are part of the protocol: if these fire, both ends need rebuilding. */
static_assert(sizeof(msg_header_t) == 8, "msg_header_t size changed");
static_assert(sizeof(ping_msg_t) == 12, "ping_msg_t size changed");
static_assert(sizeof(pong_msg_t) == 16, "pong_msg_t size changed");
static_assert(sizeof(ping_msg_t) != sizeof(pong_msg_t),
              "message types must differ in size for length-first dispatch");
