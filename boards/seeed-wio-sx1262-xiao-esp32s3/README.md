# Seeed Wio-SX1262 with XIAO ESP32-S3 kit (SKU 102010611)

XIAO ESP32-S3 paired with a Wio-SX1262 LoRa module that mates through the XIAO **B2B connector** (not header pins). Ships pre-flashed with Meshtastic. XIAO side: [../seeed-xiao-esp32s3](../seeed-xiao-esp32s3/README.md). Chip: [../../chips/esp32-s3](../../chips/esp32-s3/README.md).
Used by: no project found.

## Key specs (Seeed wiki)

| | |
|---|---|
| MCU | ESP32-S3R8, Xtensa LX7 dual-core to 240 MHz |
| LoRa | Semtech SX1262, 862–930 MHz, U.FL antenna |
| Range | 2–5 km LoRa, 100 m+ Wi-Fi/BLE (Seeed's figures) |
| Wireless | 2.4 GHz Wi-Fi, BLE 5.0 + mesh |
| ESP32-S3 interfaces | 1× UART, 1× I2C, 1× I2S, 1× SPI (to the SX1262), 11× GPIO/PWM, 9× ADC, user LED, charge LED, RESET and BOOT buttons |
| Wio-SX1262 interfaces | 1× user button, SPI to the ESP32-S3 |
| Power | USB-C 5 V, battery 4.2 V, 100 mA charge current |
| Temperature | −40 °C to 65 °C |
| Size | 21 × 17.8 mm |

## Pinout

From Meshtastic's official `seeed-xiao-s3` variant, which targets exactly this kit:

| Signal | GPIO |
|---|---|
| LoRa SCK / MISO / MOSI | 7 / 8 / 9 |
| LoRa CS | 41 |
| LoRa RESET | 42 |
| LoRa DIO1 | 39 |
| LoRa BUSY | 40 |
| LoRa DIO2 / RXEN | 38 |
| I2C SDA / SCL | 5 / 6 |
| Program button | 21 (needs a pull-up) |
| Power LED | 48 |

Radio configuration in the same variant: `DIO2` drives the antenna switch (`SX126X_DIO2_AS_RF_SWITCH`), `DIO3` supplies the TCXO at **1.8 V**, and `TXEN` is unused (`RADIOLIB_NC`).

Optional L76K GNSS module (same stack): GPS RX 44, TX 43, standby 1.

**The vendor schematic does not obviously agree with that table.** `hardware/schematic.pdf` (`Wio-SX1262 for XIAO V1.0`, KiCad 8) carries the expected nets — `LORA_SPI_SCK`, `LORA_SPI_MISO`, `LORA_SPI_MOSI`, `LORA_SPI_NSS`, `LORA_RST`, `LORA_BUSY`, `LORA_DIO1`, `LORA_RF_SW1` — but the GPIO labels printed beside its 30-pin connector are GPIO14, 15, 16, 17, 18, 21, 47 and 48, not the 7/8/9 and 38–42 the Meshtastic variant uses. The PDF's text layer gives the labels without the pin each one attaches to, so the two cannot be reconciled from the text alone *(unverified)*. Before wiring anything by hand, read the schematic by eye; for a Meshtastic build the variant's numbers are the ones that are known to work.

## Meshtastic / PlatformIO

```ini
[env:seeed-xiao-s3]
extends = esp32s3_base
board = seeed-xiao-s3
board_build.partitions = default_8MB.csv
upload_protocol = esptool
upload_speed = 921600
build_flags = -D SEEED_XIAO_S3 -DBOARD_HAS_PSRAM
```

Meshtastic hardware model 81, slug `SEEED_XIAO_S3`, 8 MB partition scheme, and it requires DFU for flashing.

## Operational notes

- **Kit pins ≠ header-board pins.** The B2B kit uses CS 41 / RESET 42 / DIO1 39 / BUSY 40. The separately sold "Wio-SX1262 for XIAO" header board wires the radio to different pins (community reports CS 5, RESET 3, DIO1 2, BUSY 4 `(unverified)`), so the stock Meshtastic build will not talk to a self-wired pairing.
- **The nRF52840 version of the kit is a different connector**: Seeed notes the ESP32-S3 kit is B2B while the nRF52840 kit uses through-hole headers; the boards are not interchangeable.
- **The L76K GNSS add-on conflicts with the LoRa SPI** unless its RESET pin is overridden or physically removed — Meshtastic's variant warns about this in a comment.
- **TCXO voltage matters.** A RadioLib setup that leaves `DIO3` TCXO at the default instead of 1.8 V gives a radio that initialises but never receives.
- **Connect the U.FL antenna before transmitting.**

## Demo

[`examples/lora-ping-pong`](../../examples/lora-ping-pong/README.md) builds for this board: a ping/pong link test that reports RSSI and SNR in both directions. Untested on hardware.

## Applications

- **Meshtastic node.** The kit ships pre-flashed with Meshtastic firmware and is supported upstream as variant `seeed-xiao-s3`.
- **LoRaWAN sensor node or single-channel gateway.** Seeed documents both configurations; the gateway supports approximately 30 nodes depending on interval and payload.
- **Point-to-point link test.** See [`examples/lora-ping-pong`](../../examples/lora-ping-pong/README.md).
- **GNSS tracker.** The L76K module stacks on the same connector. Its RESET pin must be removed or overridden first; it conflicts with the LoRa SPI bus.

## Files

- `hardware/schematic.pdf`: Seeed's `Wio-SX1262 for XIAO V1.0` schematic (fetched 2026-09-22)
- `hardware/3d-model.step.gz`: the STEP model, gzipped
- `datasheets/wio-sx1262-module.pdf`, `datasheets/wio-sx1262-n-module.pdf`: the module datasheets for both variants
- `wiki/kit-introduction.md`, `wio-sx1262-module-introduction.md`: Seeed's product and module pages
- `wiki/Get_Started_meshtastic.md`, `LoRaWAN_Sensor_Node.md`, `Single_Channel_LoRaWAN_Gateway.md`: the three applications Seeed documents
- `reference/meshtastic-variant.h`, `meshtastic-platformio.ini`, `meshtastic-pins_arduino.h`: the upstream Meshtastic variant this entry's pin table comes from
