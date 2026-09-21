# Elecrow CrowPanel ESP32 E-Paper HMI 4.2" (400×300)

ESP32-S3 board with a bonded 4.2" black/white e-paper panel, four front buttons, a microSD slot and a battery connector. Chip: [../../chips/esp32-s3](../../chips/esp32-s3/README.md).
Used by: none. The owner's `pio-crowpanel2` targets the **2.13"** CrowPanel, not this one — see [../elecrow-crowpanel-epaper-2.13](../elecrow-crowpanel-epaper-2.13/README.md).

## Key specs (Elecrow's repo readme, hardware V1.0)

| | |
|---|---|
| MCU | ESP32-S3-WROOM-1-N8R8, up to 240 MHz |
| Flash / PSRAM | 8 MB / 8 MB |
| Panel | 4.2" AM EPD, 400 (H) × 300 (V), black/white, pixel pitch 0.212 mm |
| Driver | SSD1683, 3-/4-wire SPI |
| Active area | 84.8 × 63.6 mm |
| Panel voltage | 2.2–3.7 V |
| Refresh | full and partial |
| Interfaces | UART0, battery connector, GPIO header, microSD slot |
| Buttons | rotary switch, MENU, EXIT, RESET, BOOT |
| Temperature | operating 0–50 °C, storage −25–70 °C |

## Pinout

E-paper (from Elecrow's `EPD_SPI.h` and the repo readme — they agree):

| Signal | GPIO |
|---|---|
| SCK | 12 |
| MOSI | 11 |
| RES | 47 |
| DC | 46 |
| CS | 45 |
| BUSY | 48 |
| **Panel power enable** | **7** (drive HIGH before any display call) |

microSD, on a second SPI bus (`HSPI`):

| Signal | GPIO |
|---|---|
| SCK / MISO / MOSI / CS | 39 / 13 / 40 / 10 |
| Card power enable | 42 |

Buttons and LED:

| Function | GPIO |
|---|---|
| HOME / MENU | 2 |
| EXIT | 1 |
| PREV | 6 |
| NEXT | 4 |
| Power indicator LED | 41 |

Free GPIO brought out on the header, per Elecrow's GPIO example: 3, 8, 9, 14, 15, 16, 17, 18, 19, 20, 21, 38.

## Toolchain

Elecrow ships Arduino examples using their bundled `EPD` library (v1.0.0, SSD1683). No PlatformIO config is provided; the natural equivalent is the ESP32-S3 N8R8 devkit target:

```ini
platform = espressif32
board = esp32-s3-devkitc1-n8r8
framework = arduino
monitor_speed = 115200
```

`(untested for this board — that is the line the owner uses in `pio-crowpanel2` for the 2.13" model.)`

## Gotchas

- **GPIO7 gates panel power.** Without `pinMode(7, OUTPUT); digitalWrite(7, HIGH);` the display stays blank and the SPI writes go nowhere. Every Elecrow example starts with it.
- **The SD card has its own power gate on GPIO42**, held low at boot. Enable it and wait ~10 ms before `SD.begin()`.
- **The SD bus is separate from the panel bus** (SCK 39 / MISO 13 / MOSI 40 / CS 10 on HSPI); do not reuse the EPD pins for it.
- **Elecrow's header carries a second, commented-out pin set** (`RES 21, DC 9, CS 10`) for a different CrowPanel model. Uncommenting the wrong block gives a dead panel — the numbers above are the ones marked "项目板子" (this board).
- **Partial refresh is the default mode**; full refresh is slower and flashes, but is needed periodically to clear ghosting.
- **GPIO41 is only the power indicator LED**, not a rail.

## Files

- `hardware/schematic.pdf`, `hardware/eagle.sch`, `hardware/eagle.brd`: Elecrow's EagleCAD design and its PDF print
- `hardware/3d-model.stp.gz`: the enclosure/board STEP model (gzipped, 7.9 MB raw)
- `datasheets/ssd1683.pdf`: the e-paper driver datasheet
- `reference/EPD_SPI.h`, `EPD.h`: Elecrow's pin and panel-geometry headers
- `reference/4.2_PWR.ino`, `4.2_key.ino`, `4.2_TF.ino`, `4.2_GPIO.ino`: the examples the pin numbers above come from
- `wiki/elecrow-repo-readme.md`: Elecrow's own product readme (specs, folder layout, pin list)
