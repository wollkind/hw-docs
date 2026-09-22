# Adafruit ESP32-S3 Feather (PID 5477 with PSRAM, PID 5323 without)

Feather-format ESP32-S3 with native USB-C, a LiPo charger, a fuel gauge on I2C and a STEMMA QT port. Chip: [`chips/esp32-s3`](../../chips/esp32-s3/README.md).
Used by: `pio-blink` (`[env:feather32-s3]`, `board = adafruit_feather_esp32s3`).

## Which board is which

Two boards share this Learn guide, and PlatformIO has an id for each:

| PID | Board file name | Flash | PSRAM | Board id |
|---|---|---|---|---|
| 5477 | Adafruit Feather ESP32-S3 2MB PSRAM | 4 MB | **2 MB** | `adafruit_feather_esp32s3` |
| 5323 | Adafruit Feather ESP32-S3 No PSRAM | **8 MB** | none | `adafruit_feather_esp32s3_nopsram` |

`pio-blink` builds the first. The Learn guide's module description ("8 MB flash and no PSRAM") describes the 5323. Confirm which is in hand before choosing, exactly as with the ESP32-S2 Feathers: the flash sizes differ, so the partition table differs too.

The same guide family covers the TFT and Reverse TFT Feathers, which have their own board ids (`adafruit_feather_esp32s3_tft`, `adafruit_feather_esp32s3_reversetft`); the Reverse TFT has [its own entry](../adafruit-esp32-s3-reverse-tft-feather/README.md).

## Key specs

| | |
|---|---|
| Module | ESP32-S3, dual core at 240 MHz, Wi-Fi and **Bluetooth LE only** — no Bluetooth Classic |
| USB | USB-C into the S3's native USB; `ARDUINO_USB_CDC_ON_BOOT=1`, UF2 bootloader (`tinyuf2-partitions-4MB.csv` on the 5477) |
| Battery | JST 2-PH for a 250 mAh or larger 3.7/4.2 V LiPo, with charging from USB and a yellow CHG LED. With no battery fitted the CHG LED may blink rapidly — expected |
| Fuel gauge | **MAX17048 at I2C 0x36** on boards made after 8 February 2023; **LC709203F at 0x0B** before that. The back silk says "MAX17048 Monitor" on the newer revision |
| BME280 | **Footprint only** — the sensor is not fitted. When populated it sits at I2C 0x77 |
| Regulator | 3.3 V, 500 mA peak; `EN` pulled up, ground it to shut the regulator off |
| Analogue | six analogue pins. **A0–A4 are on ADC2, A5 on ADC1.** No DAC on the ESP32-S3, so no true analogue output |
| I2C | STEMMA QT (JST SH 4-pin) shared with the header pins, 5 kΩ pull-ups |

## Pinout

From `variants/adafruit_feather_esp32s3/pins_arduino.h` in arduino-esp32.

| Function | GPIO |
|---|---|
| SDA / SCL | 3 / 4 |
| **I2C and STEMMA power enable** (`PIN_I2C_POWER`) | **7** |
| SCK / MOSI / MISO / SS | 36 / 35 / 37 / 42 |
| TX / RX | 39 / 38 |
| NeoPixel data | 33 |
| **NeoPixel power** (`NEOPIXEL_POWER`) | **21** |
| Red LED (`LED_BUILTIN`, silk "#13") | 13 |
| A0–A5 | 18, 17, 16, 15, 14, 8 |
| A6–A14 | 3, 4, 5, 6, 9, 10, 11, 12, 13 |
| Touch T3–T14 | 3, 4, 5, 6, 8, 9, 10, 11, 12, 13, 14 |

Adafruit's own note on the logic pins: "No pins are shared, and no pins are 'special' bootstrapping pins", and almost every signal can be multiplexed onto any pin — the SPI pins above are the high-speed peripheral, and using others costs speed.

## PlatformIO config

`pio-blink` builds it as:

```ini
[env:feather32-s3]
board = adafruit_feather_esp32s3
framework = arduino
```

The board file supplies `mcu esp32s3`, 240 MHz, `flash_mode qio` at 80 MHz, `flash_size 4MB`, `-DBOARD_HAS_PSRAM`, `-DARDUINO_USB_CDC_ON_BOOT=1`, `tinyuf2-partitions-4MB.csv`, upload at 460800 with `use_1200bps_touch`. For the 8 MB board swap in `adafruit_feather_esp32s3_nopsram`, which drops `BOARD_HAS_PSRAM` and moves to an 8 MB partition table.

## Operational notes

- **GPIO7 gates the STEMMA QT port and the I2C pull-ups.** Drive it high before scanning I2C — and driving it low is the documented way to cut power to the port for low-power sleep. Arduino and CircuitPython raise it automatically, but a stale board package may not.
- **GPIO21 powers the NeoPixel.** The pixel stays dark until it is high.
- **The fuel gauge changed mid-life.** Code written against the LC709203F (0x0B) does not talk to a MAX17048 (0x36) and vice versa. There is **no analogue battery-voltage pin** on this Feather — the gauge is the only way to read the cell.
- **The BME280 is a footprint, not a sensor.** An I2C scan finding nothing at 0x77 means an unpopulated board, not a fault. Adafruit also warns that a fitted BME280 sits close enough to the module to read warm after long runs.
- **No DAC.** Ported ESP32 code that writes `dacWrite` will not compile.
- **No Bluetooth Classic**, only BLE.

## Applications

- **Battery-powered Wi-Fi/BLE sensor node.** LiPo jack, charger, I2C fuel gauge and a STEMMA QT port, with GPIO7 cutting the sensor rail between samples.
- **USB device work** over the S3's native USB — HID, MIDI, CDC or mass storage.
- **FeatherWing host** for the usual stack, with the SPI and I2C pins where FeatherWings expect them.
- **Unsuitable for:** analogue output (no DAC), Bluetooth Classic, and any design that needs a battery-voltage ADC pin rather than an I2C gauge.

## Files

- `wiki/pinouts.md`, `wiki/downloads.md`: the Learn guide pages, with images
- `hardware/pinout.pdf`: Adafruit's PrettyPins diagram
- `hardware/eagle-8mb-nopsram.sch`, `.brd`: Adafruit's design for the 8 MB no-PSRAM board (the repository carries no separate file for the 2 MB PSRAM build)
- `reference/pins_arduino.h`: the arduino-esp32 variant — the authority for the pin table
- `reference/platformio-board.json`, `reference/platformio-nopsram.json`: the two board definitions
