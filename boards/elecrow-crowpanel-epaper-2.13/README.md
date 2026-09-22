# Elecrow CrowPanel ESP32 E-Paper HMI 2.13" (122×250)

ESP32-S3 board with a bonded 2.13" black/white e-paper panel and four buttons. Bought without the acrylic case. Chip: [../../chips/esp32-s3](../../chips/esp32-s3/README.md).
Used by: **`pio-crowpanel2`** (OpenWeatherMap display; Elecrow's bit-banged `EPD`/`spi` driver copied into `src/`).

## Key specs (Elecrow's repo readme)

| | |
|---|---|
| MCU | ESP32-S3, up to 240 MHz |
| Flash / PSRAM | 8 MB / 8 MB |
| Panel | 2.13" AM EPD, 122 (H) × 250 (V), black/white, pixel pitch 0.227 × 0.226 mm |
| Driver | **SSD1680Z or JD79661** — two panel sources, 3-/4-wire SPI |
| Active area | 31.2 × 63.19 mm |
| Panel voltage | 2.2–3.7 V |
| Refresh | partial (default) and full |
| Interfaces | UART0, battery connector, GPIO header (no SD slot on this model) |
| Buttons | dial switch, MENU, BACK, RESET, BOOT |
| Temperature | operating 0–50 °C, storage −25–70 °C |

## Pinout

E-paper (Elecrow's `spi.h`, the repo readme, and the owner's `pio-crowpanel2` all agree):

| Signal | GPIO |
|---|---|
| SCK | 12 |
| MOSI | 11 |
| RES | 10 |
| DC | 13 |
| CS | 14 |
| BUSY | 9 |
| **Panel power enable** | **7** (drive HIGH first) |

Buttons: HOME/MENU 2, EXIT/BACK 1, PREV 6, NEXT 4 — same numbers as the 4.2" model.

**Note the 4.2" board uses different display pins** (RES 47, DC 46, CS 45, BUSY 48). Only SCK 12 / MOSI 11 and the GPIO7 power gate are shared.

## PlatformIO (as used in `pio-crowpanel2`)

```ini
[env:esp32-s3-devkitc1-n8r8]
platform = https://github.com/pioarduino/platform-espressif32/releases/download/stable/platform-espressif32.zip
board = esp32-s3-devkitc1-n8r8
framework = arduino
monitor_speed = 115200
```

That project drives the panel with Elecrow's `EPD.cpp` / `EPD_Init.cpp` / `spi.cpp` copied in, not an Arduino library.

## Operational notes

- **GPIO7 gates panel power** — set it HIGH in `setup()` before `EPD_GPIOInit()`, exactly as `pio-crowpanel2` does.
- **Two different driver ICs ship under the same product.** SSD1680Z and JD79661 need different init sequences; Elecrow's bundled `EPD_Init.cpp` is written against the SSD1680 command set (its comments cite the SSD1680 datasheet for 0x12, 0x10, 0x22, 0x20, 0x26, 0x3C). A panel that stays blank with working SPI is the first sign of a JD79661 build `(unverified — no JD79661 board seen here)`.
- **Orientation is a compile-time switch**: `USE_HORIZONTIAL` in `EPD_Init.h`, 0/2 give 250×122 and 1/3 give 122×250. The buffer size changes with it.
- **No SD slot** on this model, unlike the 4.2".
- **Partial refresh is the normal mode**; run a full refresh occasionally to clear ghosting.

## Applications

- **Periodic data display.** Weather, calendar or sensor values on a slow refresh cycle. This is what `pio-crowpanel2` does with the OpenWeatherMap API.
- **Desk or asset label.** Text written once, retained with power removed, updated over Wi-Fi when required.
- **Unsuitable for:** anything needing local file storage. This model has no SD slot; the 4.2" model does.

## Files

- `hardware/schematic.pdf`, `hardware/eagle.sch`, `hardware/eagle.brd`
- `hardware/3d-model.rar`: Elecrow's 3D assembly (RAR, as shipped)
- `datasheets/ssd1680.pdf`: the SSD1680 driver datasheet
- `reference/spi.h`, `EPD_Init.h`: pin and geometry headers
- `reference/2.13_key.ino`, `2.13_partial_refresh.ino`: the button and refresh examples
- `wiki/elecrow-repo-readme.md`: Elecrow's product readme
