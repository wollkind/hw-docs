#pragma once
#include <stdint.h>

/*
 * Message definitions for the LoRa ping/pong example.
 *
 * Both nodes compile this file. Any change requires rebuilding both nodes.
 *
 * Constraints applied here:
 *   - All fields use fixed-width integer types. The width of "int" differs
 *     between target architectures.
 *   - All structures are packed. Unpacked structures receive compiler padding
 *     that differs between architectures.
 *   - All messages begin with the same header, so that a receiver can read the
 *     message type before it knows the message length.
 *   - The two message types have different sizes. A receiver checks the
 *     received length before reading any field.
 *   - The header contains a version field. A node receiving an unknown version
 *     discards the message.
 */

#define PROTO_MAGIC   0x4C50u  /* ASCII "LP", stored little-endian */
#define PROTO_VERSION 1

#define ADDR_BROADCAST 0xFF

enum : uint8_t {
    MSG_PING = 1,
    MSG_PONG = 2,
};

struct __attribute__((packed)) msg_header_t {
    uint16_t magic;    /* PROTO_MAGIC */
    uint8_t  version;  /* PROTO_VERSION */
    uint8_t  type;     /* MSG_PING or MSG_PONG */
    uint8_t  src;      /* node identifier of the sender */
    uint8_t  dst;      /* node identifier of the recipient, or ADDR_BROADCAST */
    uint16_t seq;      /* incremented once per ping; copied into the pong */
};

struct __attribute__((packed)) ping_msg_t {
    msg_header_t h;
    uint32_t t_ms;     /* value of millis() on the sender at transmit time */
};

struct __attribute__((packed)) pong_msg_t {
    msg_header_t h;
    uint32_t t_ms;      /* copied from the ping without modification */
    int16_t  rssi_cdbm; /* RSSI of the ping at the responder, in 0.01 dBm units */
    int16_t  snr_cdb;   /* SNR of the ping at the responder, in 0.01 dB units */
};

/* Structure sizes form part of the message format. A failed assertion here
 * indicates that both nodes require rebuilding. */
static_assert(sizeof(msg_header_t) == 8, "msg_header_t size changed");
static_assert(sizeof(ping_msg_t) == 12, "ping_msg_t size changed");
static_assert(sizeof(pong_msg_t) == 16, "pong_msg_t size changed");
static_assert(sizeof(ping_msg_t) != sizeof(pong_msg_t),
              "message types must differ in size for length-based dispatch");
