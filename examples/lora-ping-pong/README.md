# LoRa ping/pong

A two-node link demo for the LoRa boards in this library:

- [`boards/lilygo-t3-lora32-v1.6.1`](../../boards/lilygo-t3-lora32-v1.6.1/README.md) — ESP32-PICO-D4 + SX1276
- [`boards/seeed-wio-sx1262-xiao-esp32s3`](../../boards/seeed-wio-sx1262-xiao-esp32s3/README.md) — XIAO ESP32-S3 + SX1262

One source tree builds both boards and both roles. The boards can be mixed:
an SX1276 talks to an SX1262 as long as the air parameters match.

> **Not built or run here.** Written against the pin maps and radio settings
> recorded in the two board entries. `pio run` could not complete in the
> sandbox — the ESP32 platform download is blocked by the egress proxy. What
> *was* checked: `include/protocol.h` compiles and its `static_assert`s pass
> (header 8 / ping 12 / pong 16 bytes, little-endian on the wire), and
> `src/main.cpp` passes a syntax check against stub headers — which says
> nothing about whether the RadioLib calls match that library's real
> signatures. Treat the first flash as the test.

## Build

```sh
pio run -e t3_ping   -t upload    # node 1 on the T3
pio run -e xiao_pong -t upload    # node 2 on the XIAO kit
pio device monitor -b 115200
```

Any pairing works: `t3_ping` + `t3_pong`, `xiao_ping` + `xiao_pong`, or one of
each. The pinger prints; the ponger mostly answers.

Expected output on the pinger:

```
ping 7 sent (12 bytes)
pong 7  rtt 148 ms  here: RSSI -41.0 dBm SNR 9.8 dB  there: RSSI -43.50 dBm SNR 9.25 dB  loss 0/7
```

`here` is the pong as this node heard it; `there` is the ping as the *other*
node heard it, carried back inside the pong. Asymmetry between the two is the
useful signal — it usually means one antenna, not the path.

## What is actually on the air

12 bytes for a ping, 16 for a pong, plus the LoRa PHY's own preamble, header
and CRC. `include/protocol.h` is the whole protocol:

```
msg_header_t   magic(2) version(1) type(1) src(1) dst(1) seq(2)   = 8 bytes
ping_msg_t     header + t_ms(4)                                   = 12 bytes
pong_msg_t     header + t_ms(4) + rssi_cdbm(2) + snr_cdb(2)       = 16 bytes
```

Design choices worth copying into the next link:

- **Fixed-width types and `__attribute__((packed))`.** Otherwise padding differs
  between architectures and the bytes on air stop matching the bytes in memory.
  `static_assert` on every struct size makes a silent change loud.
- **Dispatch on length first, magic second.** The two message types are
  deliberately different sizes, so a truncated or foreign packet is rejected
  before any field is read. This is the same discipline as `pio-strip-com`'s
  ESP-NOW protocol.
- **A version byte.** An old node meeting a new one says so instead of decoding
  garbage.
- **Echo, don't restamp.** The pong returns the ping's `t_ms` untouched, so the
  round-trip time is computed entirely on the pinger's clock. Two nodes never
  share a time base.
- **Sequence numbers** give loss counting and stale-reply rejection for free.
- **No application CRC.** The LoRa PHY already CRCs the payload and RadioLib
  reports `RADIOLIB_ERR_CRC_MISMATCH`; adding another is wasted airtime.

Deliberately absent, because a two-node demo does not need them: retries,
acknowledgements, fragmentation for payloads over 255 bytes, encryption, and
any duty-cycle limiter (relevant in EU 868 bands).

## Air parameters

Set in `src/main.cpp` and identical on both ends — frequency, bandwidth,
spreading factor, coding rate, sync word and preamble length. One mismatch
means silence, with no error anywhere.

| Setting | Value | Effect of changing it |
|---|---|---|
| `FREQ_MHZ` | 915.0 | Must suit the module fitted. 868.0 for EU parts. |
| `BW_KHZ` | 125.0 | Narrower = more range, slower, less tolerant of drift |
| `SPREAD_FACT` | 9 | 7 fast/short … 12 slow/far; each step up roughly doubles airtime |
| `CODING_RATE` | 7 | 4/7 — more redundancy, more airtime |
| `SYNC_WORD` | 0x12 | Private network. RadioLib maps the byte to each chip family's encoding |
| `TX_DBM` | 17 | Within both modules' range; SX1262 can go higher |

Raising `SPREAD_FACT` to 12 and walking away is the interesting demo: the RTT
climbs into seconds, and the link survives well past where SF7 drops.

## Gotchas this code already handles

- `transmit()` leaves the radio idle, so every send is followed by
  `startReceive()`. Forgetting that is the classic "it answers once then goes
  deaf".
- On the SX1262 kit, `begin(..., 1.8)` powers the TCXO from DIO3 and
  `setDio2AsRfSwitch(true)` drives the antenna switch. Omit either and the
  radio initialises fine and hears nothing.
- The SX1276 and SX1262 take different `Module()` arguments: DIO0 + DIO1 for
  the SX127x, DIO1 + BUSY for the SX126x.
- Native-USB boards need a delay before the serial port exists; the XIAO envs
  also set `ARDUINO_USB_CDC_ON_BOOT=1`.

**Attach an antenna before powering either board.**
