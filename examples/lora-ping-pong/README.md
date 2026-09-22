# LoRa ping/pong example

A two-node link test for the LoRa boards in this library:

- [`boards/lilygo-t3-lora32-v1.6.1`](../../boards/lilygo-t3-lora32-v1.6.1/README.md): ESP32-PICO-D4 with SX1276
- [`boards/seeed-wio-sx1262-xiao-esp32s3`](../../boards/seeed-wio-sx1262-xiao-esp32s3/README.md): XIAO ESP32-S3 with SX1262

One source tree builds both boards and both roles. The two nodes may use
different boards; an SX1276 and an SX1262 interoperate when configured with
identical radio parameters.

## Verification status

Not built and not run. The PlatformIO ESP32 platform download is blocked by the
egress proxy in the environment where this was written.

Checks that were performed:

| Check | Result |
|---|---|
| `include/protocol.h` compiles, static assertions pass | Pass: header 8 bytes, ping 12 bytes, pong 16 bytes |
| Byte order of a populated `ping_msg_t` | Little-endian, confirmed by memory dump |
| `src/main.cpp` syntax check against stub headers | Pass for both board definitions |

The syntax check used locally written stub headers. It does not confirm that
the RadioLib calls match that library's actual signatures.

## Build and run

```sh
pio run -e t3_ping   -t upload    # node 1, T3 LoRa32
pio run -e xiao_pong -t upload    # node 2, Wio-SX1262 kit
pio device monitor -b 115200
```

Available environments: `t3_ping`, `t3_pong`, `xiao_ping`, `xiao_pong`. Any
ping and pong pair functions.

Output format on the pinger:

```
ping 7 transmitted, 12 bytes
pong 7, round trip 148 ms, local RSSI -41.0 dBm SNR 9.8 dB, remote RSSI -43.50 dBm SNR 9.25 dB, unanswered 0 of 7
```

`local` values are measured on the node printing the line. `remote` values are
measured by the other node and returned inside the pong.

## Message format

Defined in `include/protocol.h`.

| Structure | Size | Fields |
|---|---|---|
| `msg_header_t` | 8 bytes | magic (2), version (1), type (1), src (1), dst (1), seq (2) |
| `ping_msg_t` | 12 bytes | header, t_ms (4) |
| `pong_msg_t` | 16 bytes | header, t_ms (4), rssi_cdbm (2), snr_cdb (2) |

Properties of this format:

- Fields use fixed-width integer types. The width of `int` differs between
  target architectures.
- Structures are packed. Unpacked structures receive compiler padding that
  differs between architectures.
- The two message types have different sizes. A receiver checks the received
  length before reading any field.
- The header contains a version field. A node receiving an unknown version
  discards the message and prints a line.
- The pong copies the ping's timestamp without modification. Round trip time is
  therefore computed entirely from the pinger's clock. The two nodes do not
  share a time reference.
- No application-level checksum is present. The radio computes and verifies a
  CRC, and RadioLib reports `RADIOLIB_ERR_CRC_MISMATCH`.

Not implemented: retransmission, acknowledgement beyond the pong itself,
fragmentation of payloads larger than 255 bytes, encryption, duty cycle
limiting.

## Radio parameters

Set in `src/main.cpp`. All values must be identical on both nodes. A difference
in any one value results in no reception and no error report.

| Parameter | Value | Effect of increase |
|---|---|---|
| `FREQ_MHZ` | 915.0 | Must match the installed module. Use 868.0 for European modules. |
| `BW_KHZ` | 125.0 | Shorter transmission, lower sensitivity |
| `SPREAD_FACT` | 9 | Longer transmission, higher sensitivity. Range 7 to 12. |
| `CODING_RATE` | 7 | More error correction, longer transmission |
| `SYNC_WORD` | 0x12 | Separates networks on one frequency |
| `TX_DBM` | 17 | Higher output power |

Transmission duration at 125 kHz bandwidth, coding rate 4/5, for the 12-byte
ping: 41 ms at SF7, 144 ms at SF9, 1155 ms at SF12.

## Hardware behaviour handled by this code

- `transmit()` leaves the radio in standby. `startReceive()` is called after
  every transmission.
- On the SX1262 module, `begin(..., 1.8)` supplies the TCXO from DIO3 and
  `setDio2AsRfSwitch(true)` configures the antenna switch. Without both calls
  the radio initialises without error and receives no packets.
- The `Module()` constructor takes different pins per chip family: NSS, DIO0,
  RESET, DIO1 for the SX1276; NSS, DIO1, RESET, BUSY for the SX1262.
- Boards with native USB require a delay before the serial port exists. The
  XIAO environments also define `ARDUINO_USB_CDC_ON_BOOT=1`.

An antenna must be connected before either board is powered on.
