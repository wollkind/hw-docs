# Adafruit ESP32-S3 Reverse TFT Feather (PID 5691)

Feather with an ESP32-S3-MINI-1 and a 1.14" 240×135 IPS TFT mounted on the **back**, alongside three user buttons — made for panel mounting. Chip: [../../chips/esp32-s3](../../chips/esp32-s3/README.md).
Used by: no project found.

## Key specs

| | |
|---|---|
| Module | ESP32-S3-MINI-1, dual-core 240 MHz, 512 KB SRAM, BLE only (no Bluetooth Classic) |
| Flash / PSRAM | 4 MB flash, 2 MB PSRAM (`qio_qspi`, 80 MHz) |
| Display | 1.14" 240×135 IPS, ST7789, on the SPI bus; control pins are not on the headers |
| Buttons | D0 (= BOOT0), D1, D2, plus reset |
| Fuel gauge | MAX17048 on I2C (address 0x36 `(unverified — datasheet not fetched)`) |
| Power | USB-C or JST-PH LiPo; MBR540 + DMG3415U P-FET switchover; main 3.3 V LDO plus a **second, GPIO-gated LDO** |
| Charger | MCP73831T-2ACI/OT, orange CHG LED |
| Extras | STEMMA QT / Qwiic I2C, status NeoPixel with its own power pin, red LED |
| Deep sleep | ~100 µA with everything off per Adafruit; 40–50 µA from the LiPo connector |
| USB ids | 0x239A:0x8123 / 0x0123 / 0x8124 |

**Unpopulated footprint:** the schematic carries a BME280 (U4) wired to the switched sensor rail with CSB and SDO tied high — so I2C 0x77 if a board has it fitted. Adafruit's feature list for 5691 does not mention it, so assume it is not placed `(unverified)`.

## Pinout

| Function | GPIO |
|---|---|
| TFT CS / DC / RESET / BACKLIGHT | 42 / 40 / 41 / 45 |
| TFT + STEMMA QT + sensor-rail power enable (`TFT_I2C_POWER`) | **7** |
| SPI SCK / MOSI / MISO | 36 / 35 / 37 |
| I2C SDA / SCL | 3 / 4 |
| UART TX / RX | 39 / 38 |
| NeoPixel data / power | 33 / 21 |
| Red LED | 13 |
| Buttons D0 (BOOT0) / D1 / D2 | 0 / 1 / 2 |
| A0–A5 | 18, 17, 16, 15, 14, 8 |
| D5, D6, D9–D12 | 5, 6, 9, 10, 11, 12 |

Button polarity, read off the schematic: **D1 (GPIO1) and D2 (GPIO2) switch to 3.3 V — they are active HIGH and need a pull-down.** D0 (GPIO0) is the usual BOOT0 button to ground, active low with the module's pull-up.

## PlatformIO (vendor board definition, untested here)

```ini
[env:reversetft]
platform = espressif32
board = adafruit_feather_esp32s3_reversetft
framework = arduino
board_build.partitions = partitions-4MB-tinyuf2.csv
build_flags =
    -DARDUINO_ADAFRUIT_FEATHER_ESP32S3_REVTFT
    -DARDUINO_USB_CDC_ON_BOOT=1
    -DBOARD_HAS_PSRAM
upload_speed = 460800
```

The board JSON also sets `use_1200bps_touch` and flashes `tinyuf2.bin` at 0x2d0000, so the UF2 bootloader survives an Arduino upload. CircuitPython names the same pins `board.TFT_CS`, `board.TFT_I2C_POWER`, `board.NEOPIXEL_POWER`, `board.D1`, …

## Gotchas

- **GPIO7 gates the TFT, the STEMMA QT port and the sensor rail.** Drive it high (and wait a moment) before talking to anything on I2C or the display; after a deep sleep it comes back low. This is the usual "my STEMMA sensor disappeared" cause on this board.
- **D1/D2 are active high.** Code copied from other Feathers that uses `INPUT_PULLUP` and tests for LOW will never see a press.
- **D0 doubles as BOOT0**: holding it at reset enters the ROM bootloader, so it is a poor choice for a "hold at power-on" feature.
- **The display's CS/DC/RESET/backlight pins are not on the headers** — GPIO40/41/42/45 are consumed by the TFT even if the display is unused.
- **NeoPixel power is switched on GPIO21**; the pixel stays dark until that pin is high.
- **Backlight is PWM-able on GPIO45** through a BSS138, which is also an ESP32-S3 strapping pin `(unverified — no ESP32-S3 datasheet check done here)`.

## Files

- `hardware/eagle.sch`, `hardware/eagle.brd`: Adafruit's EagleCAD source
- `hardware/pinout.pdf`, `hardware/pinout-display-side.pdf`: Adafruit's PrettyPins pinout diagrams, both sides
- `reference/platformio-board.json`: the PlatformIO board definition
- `reference/arduino-esp32-pins_arduino.h`: the Arduino core variant header
- `reference/cpy-pins.c`, `cpy-mpconfigboard.h`, `cpy-mpconfigboard.mk`, `cpy-sdkconfig`: the CircuitPython board definition
