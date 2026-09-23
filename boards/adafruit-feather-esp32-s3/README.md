# Adafruit ESP32-S3 Feather (PID 5477 4 MB flash + 2 MB PSRAM; PID 5323 / 5885 8 MB flash, no PSRAM)

Feather-format ESP32-S3-MINI-1 board with native USB-C, STEMMA QT, LiPo charger and an I2C fuel gauge. One PCB design covers three products; they differ only in the module variant (and 5885 adds a w.FL antenna connector). Chip: [../../chips/esp32-s3](../../chips/esp32-s3/README.md).
Used by: `pio-blink` (env `feather32-s3`, `board = adafruit_feather_esp32s3`). `MISSION.md` lists `adafruit_feather_esp32s3` among the outstanding board ids.

## Variants

| PID | Flash | PSRAM | Antenna | PlatformIO board |
|---|---|---|---|---|
| 5477 | 4 MB | 2 MB | PCB | `adafruit_feather_esp32s3` ("Adafruit Feather ESP32-S3 2MB PSRAM") |
| 5323 | 8 MB | none | PCB | `adafruit_feather_esp32s3_nopsram` |
| 5885 | 8 MB | none | w.FL (antenna not included) | `adafruit_feather_esp32s3_nopsram` `(unverified — no board file names 5885)` |

**Fuel gauge revision:** boards bought after 2023-02-08 have a **MAX17048** (I2C 0x36) and the back silk reads "MAX17048 Monitor" in the upper-left corner. Earlier boards have an **LC709203F** (I2C 0x0B) and lack that silk. Only one of the two is fitted. The schematic in the PCB repo is the LC709203F revision.

## Key specs

| | |
|---|---|
| Module | ESP32-S3-MINI-1 (see Variants), dual-core LX7 240 MHz, 512 KB SRAM, Wi-Fi + BLE (no Bluetooth Classic) |
| USB | USB-C to native ESP32-S3 USB; no USB-serial bridge. VID:PID 0x239A:0x811B (Arduino) |
| Power | USB-C or JST-PH 2-pin LiPo; MBR540 Schottky + DMG3415U P-FET switchover; AP2112/RT9080 3.3 V LDO (500 mA peak) plus a **second LDO (U5) for the I2C/STEMMA rail**, gated by GPIO7 |
| Charger | MCP73831T-2ACI/OT, yellow CHG LED (flickers with no battery attached — normal) |
| Fuel gauge | MAX17048 @ 0x36 or LC709203F @ 0x0B (see above). No ADC pin reads battery voltage |
| BME280 | **footprint only, not fitted**; if populated it would sit at 0x77 on the switched rail |
| Onboard | WS2812B/SK6805-1515 NeoPixel (power-switched), red LED on GPIO13, reset + BOOT (GPIO0) buttons, STEMMA QT (5 kΩ pull-ups on SDA/SCL) |
| Deep sleep | ~100 µA from the LiPo with NeoPixel and I2C power off (Adafruit figure) |

## Pinout

Source: `reference/arduino-esp32-pins_arduino.h`, cross-checked against the Learn guide's Pinouts page.

| Function | GPIO |
|---|---|
| I2C SDA / SCL (header + STEMMA QT) | 3 / 4 |
| **I2C / STEMMA power enable (`PIN_I2C_POWER`, `TFT_I2C_POWER`)** | **7** |
| SPI SCK / MOSI / MISO / SS | 36 / 35 / 37 / 42 |
| UART TX / RX (`Serial1`) | 39 / 38 |
| NeoPixel data / power (`PIN_NEOPIXEL`, `NEOPIXEL_POWER`) | 33 / 21 |
| Red LED (`LED_BUILTIN`) | 13 |
| BOOT button | 0 |
| A0–A5 | 18, 17, 16, 15, 14, 8 (A0–A4 on ADC2, A5 on ADC1) |
| D5, D6, D9–D12 | 5, 6, 9, 10, 11, 12 (D5/D6/D9/D10 on ADC1; D11–D13 on ADC2) |
| Debug TX pad ("DB") | UART0 TXD — GPIO43 per `chips/esp32-s3` `(pad-to-GPIO net not traced in the schematic)` |

No DAC on the ESP32-S3.

## PlatformIO

As built in `pio-blink` (the `[env]` block there points `platform` at a local pioarduino copy, `file://C:/Users/steve/pio-esp32-55.03.311`):

```ini
[env:feather32-s3]
board = adafruit_feather_esp32s3
framework = arduino
```

From the board definition (`reference/platformio-board.json`): `-DARDUINO_ADAFRUIT_FEATHER_ESP32S3 -DBOARD_HAS_PSRAM -DARDUINO_USB_CDC_ON_BOOT=1`, `partitions-4MB-tinyuf2.csv`, QIO flash at 80 MHz, `use_1200bps_touch`, upload 460800. **This profile assumes PID 5477 (4 MB + PSRAM).** On a 5323/5885 use `adafruit_feather_esp32s3_nopsram` (8 MB, `partitions-8MB-tinyuf2.csv`, no `BOARD_HAS_PSRAM`); building a 5323 with the 5477 profile leaves 4 MB of flash unused and sets `BOARD_HAS_PSRAM` on a board without PSRAM `(consequence of a PSRAM-less boot with that flag not tested here)`.

**Verified: builds** on 2026-09-23 against the public pioarduino 55.03.311 release (Arduino core 3.3.11). Upload not tested.

## Operational notes

- **GPIO7 must be high for STEMMA QT, the I2C pull-ups and the (optional) BME280.** Arduino and CircuitPython set it automatically; Adafruit's guide says to drive it manually if an older ESP32 core is in use. Driving it low cuts power to the connector and pull-ups for low-power sleep.
- **NeoPixel power is on GPIO21.** The pixel stays dark until it is high; Arduino sets it automatically on current cores.
- **`Serial` is USB CDC**, not the TX/RX header pins. The "DB" pad carries the ROM/IDF log (UART0), not `Serial.print()` output.
- **Entering the bootloaders:** double-tap reset while the NeoPixel is purple → UF2 (TinyUF2); hold BOOT and tap reset → ROM bootloader for `esptool`.
- **CircuitPython 10 on the 4 MB board needs TinyUF2 ≥ 0.31.0** (Adafruit's overview page).
- Adafruit states none of the header pins are strapping pins; the strapping pins (0, 3, 45, 46 per `chips/esp32-s3`) are GPIO0 = BOOT button and GPIO3 = SDA. `(GPIO3 as JTAG-source strap on SDA not checked against the datasheet here)`

## Applications

- **Battery IoT sensor node.** STEMMA QT sensor + Wi-Fi + deep sleep; GPIO7 removes power from the sensor rail between samples, and the MAX17048 reports state of charge without an ADC divider.
- **USB HID / MIDI device.** Native USB enumerates as keyboard, mouse, MIDI or mass storage; header GPIO reads switches.
- **BLE peripheral** (BLE only). Unsuitable for Bluetooth Classic audio or SPP.
- PID 5323/5885 (no PSRAM) are unsuitable for large frame buffers or camera work; PID 5477 has 2 MB PSRAM for those.

## Files

- `hardware/eagle.sch`, `hardware/eagle.brd`: Adafruit's EagleCAD design (repo file name "Adafruit ESP32-S3 8MB No PSRAM", LC709203F revision; shared by all three PIDs)
- `hardware/pinout.pdf`: Adafruit PrettyPins diagram
- `reference/platformio-board.json`: `adafruit_feather_esp32s3` board definition
- `reference/arduino-esp32-pins_arduino.h`: Arduino core variant header
- `wiki/`: Learn guide pages (overview, pinouts, power management, downloads) with images
