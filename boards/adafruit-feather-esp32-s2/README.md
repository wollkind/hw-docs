# Adafruit Feather ESP32-S2 (PID 5000; BME280 version is PID 5303)

Feather-format ESP32-S2 with native USB, STEMMA QT and a LiPo charger. The same PCB is sold bare (5000) and with a BME280 fitted (5303). Chip: ESP32-S2 — no `chips/esp32-s2` entry yet.
Used by: `pio-bme280`, `pio-bme680`, `pio-feather` (all build a `featheresp32-s2` env alongside other targets). `MISSION.md` counts five such environments.

## Key specs

| | |
|---|---|
| Module | ESP32-S2 (single-core Xtensa LX7, 240 MHz, Wi-Fi only — no Bluetooth) |
| Memory | 4 MB flash (QIO, 80 MHz), **2 MB PSRAM** on PID 5000/5303 |
| USB | USB-C, native ESP32-S2 USB; UF2 bootloader (double-tap reset, `DOUBLE_TAP_PIN` GPIO34) |
| Power | USB-C or JST-PH LiPo; MBR540 + DMG3415U P-FET switchover, AP2112/RT9080 3.3 V LDO, **plus a second LDO** gated by GPIO7 |
| Charger | MCP73831, orange CHG LED |
| Fuel gauge | **LC709203F** on I2C `(address not read from the schematic here — unverified)` |
| Onboard | WS2812B NeoPixel (power-gated), red LED, reset and BOOT buttons, STEMMA QT |
| BME280 | fitted only on PID 5303; the footprint is on every board |

## Pinout

| Function | GPIO |
|---|---|
| I2C SDA / SCL (header + STEMMA QT) | 3 / 4 |
| **I2C / STEMMA power enable** | **7** |
| SPI SCK / MOSI / MISO | 36 / 35 / 37 |
| UART TX / RX | 39 / 38 |
| NeoPixel data / power | 33 / 21 |
| Red LED | 13 |
| BOOT button (D0) | 0 |
| A0–A5 | 18, 17, 16, 15, 14, 8 |
| D5, D6, D9–D12 | 5, 6, 9, 10, 11, 12 |

## PlatformIO — pick the right board id

The owner's projects use:

```ini
[env:featheresp32-s2]
platform = https://github.com/pioarduino/platform-espressif32/releases/download/stable/platform-espressif32.zip
board = featheresp32-s2
framework = arduino
```

**`featheresp32-s2` is the no-PSRAM profile.** Its board file sets `-DARDUINO_ADAFRUIT_FEATHER_ESP32S2_NOPSRAM` and points at product 4769. For a PID 5000/5303 board the right id is **`adafruit_feather_esp32s2`**, which sets `-DARDUINO_ADAFRUIT_FEATHER_ESP32S2 -DBOARD_HAS_PSRAM` and `memory_type = qio_qspi`. Building with the current id succeeds but leaves the 2 MB PSRAM unavailable. This is acceptable for the sensor sketches in these projects and incorrect for any application requiring a frame buffer.

Both profiles flash `tinyuf2.bin` at 0x2d0000 and use `use_1200bps_touch`, so the UF2 bootloader survives an Arduino upload.

## Operational notes

- **GPIO7 gates the STEMMA QT port and the second LDO.** Drive it high before scanning I2C; after deep sleep it comes back low. The ESP32-S3 Feathers use the same arrangement.
- **No Bluetooth.** The ESP32-S2 is Wi-Fi only — code ported from an ESP32/S3 that opens a BLE service will not compile.
- **NeoPixel power is on GPIO21**; the pixel stays dark until it is high.
- **Single core.** Anything assuming `xTaskCreatePinnedToCore(..., 1)` needs revisiting.
- **The BME280 is not fitted on PID 5000**, though its footprint is on the board — an I2C scan that finds nothing at the BME280 address means a bare 5000, not a fault. The owner's BME280/BME680 projects use external breakouts anyway.

## Applications

- **Wi-Fi sensor bridge.** STEMMA QT sensors to MQTT or HTTP. GPIO7 removes power from the sensor rail between samples, which lowers average current on battery.
- **USB HID device.** Native USB permits keyboard, mouse or MIDI enumeration. Header GPIO reads the switches.
- **Unsuitable for:** Bluetooth work of any kind. The ESP32-S2 has no radio for it.

## Files

- `hardware/eagle-revc.sch`, `hardware/eagle-revc.brd`: Adafruit's Rev C design
- `hardware/pinout.pdf`: Adafruit's pinout diagram
- `reference/platformio-board.json`: the `featheresp32-s2` board definition the projects currently build against
- `reference/cpy-pins.c`, `cpy-mpconfigboard.h`, `cpy-mpconfigboard.mk`: the CircuitPython board definition (pin names, flash/PSRAM sizes)
