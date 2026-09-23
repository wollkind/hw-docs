# Adafruit Qualia ESP32-S3 for TTL RGB-666 Displays (PID 5800)

ESP32-S3 dev board that drives 40-pin RGB-666 TTL ("dot clock") TFT panels directly from the S3's LCD peripheral, with a PSRAM frame buffer, a constant-current backlight driver and an I2C I/O expander for panel init. **No display included.** Chip: [../../chips/esp32-s3](../../chips/esp32-s3/README.md).
Used by: none confirmed. `pio-blink` had a `qualia` env and dropped it on 2026-09-23 because the board has no user LED. `MISSION.md` counts three environments with this board id across the owner's projects.

## Key specs

| | |
|---|---|
| Module | ESP32-S3-WROOM (schematic U3), **16 MB flash, 8 MB octal PSRAM** |
| USB | USB-C to native ESP32-S3 USB; no USB-serial bridge. VID:PID 0x239A:0x8147 |
| Power | USB-C 5 V; AP2112K-3.3 LDO (U2). No LiPo charger or battery connector |
| Display connector | 40-pin FPC (J1), "secondary standard" RGB-666 pin order; metal contacts face the board, pin 1 furthest from the JST connector. Wired as RGB 5-6-5 + HSYNC/VSYNC/DE/PCLK, plus the touch overlay's I2C |
| Backlight | TPS61169 boost constant-current driver, up to 30 V forward voltage; 25 mA default, +25/+50/+100 mA front jumpers (additive, max 200 mA); PWM jumper lets A1 drive the backlight |
| I/O expander | PCA9554 (Learn guide: PCA9554A; deep-sleep page: TCA9534) on I2C, **0x3F** default, 0x3B–0x3F via rear jumpers. Carries panel SPI init lines, panel reset, backlight enable and the UP/DOWN buttons |
| Other | STEMMA QT (I2C, pulled up to 3.3 V), 3-pin JST "A0" connector (5 V default, jumper for 3 V), reset / BOOT0 / UP / DN buttons, TX0 debug pad, IM0/IM1 panel-mode jumpers |
| LEDs | **power LED only ("3VON").** No user-controllable LED or NeoPixel |

## Pinout

Source: `reference/arduino-esp32-pins_arduino.h`; SPI/A0/A1 cross-checked against the Learn guide's Pinouts page.

**Panel (RGB 5-6-5 on the 6-6-6 connector):**

| Signal | GPIO |
|---|---|
| R1–R5 | 11, 10, 9, 46, 3 |
| G0–G5 | 48, 47, 21, 14, 13, 12 |
| B1–B5 | 40, 39, 38, 0, 45 |
| PCLK / DE / HSYNC / VSYNC | 1 / 2 / 41 / 42 |

**PCA9554 expander pins (`PCA_*` constants):**

| Pin | Function |
|---|---|
| 0 / 1 / 7 | panel SPI SCK / CS / MOSI (software SPI for the init sequence) |
| 2 | panel reset |
| 3 | touch interrupt (`PCA_CPT_IRQ`) |
| 4 | backlight enable |
| 5 / 6 | UP / DOWN buttons (pulled up by the expander, active low) |

**Header / connectors:**

| Function | GPIO |
|---|---|
| I2C SDA / SCL (STEMMA QT, touch, expander) | 8 / 18 |
| SPI SCK / MISO / MOSI / CS (CS has 10 kΩ pull-up) | 5 / 6 / 7 / 15 |
| A0 (JST + header) / A1 (header, optional backlight PWM) | 17 / 16 |
| UART TX / RX (`Serial1`) — same pins as A1 / A0 | 16 / 17 |

Several panel lines are ESP32-S3 strapping pins: GPIO0 (B4), GPIO3 (R5), GPIO45 (B5), GPIO46 (R4), per `chips/esp32-s3`.

## PlatformIO

As formerly built in `pio-blink` (`[env]` there points `platform` at a local pioarduino copy, `file://C:/Users/steve/pio-esp32-55.03.311`):

```ini
[env:qualia]
board = adafruit_qualia_s3_rgb666
build_flags =
        ${env.build_flags}
        -D LED_BUILTIN=18
```

From the board definition (`reference/platformio-board.json`): `-DARDUINO_QUALIA_S3_RGB666 -DBOARD_HAS_PSRAM -DARDUINO_USB_CDC_ON_BOOT=1`, `memory_type = qio_opi`, `partitions-16MB-tinyuf2.csv`, TinyUF2 flashed at 0x410000, `use_1200bps_touch`, upload 460800.

**`-D LED_BUILTIN=18` in `pio-blink` toggles GPIO18, which is I2C SCL** (per the variant header). The board has no user LED, so the blink sketch produces no visible output unless something is attached to SCL; it also fights any I2C device on the bus. It compiles: **built successfully** on 2026-09-23 against the public pioarduino 55.03.311 release (Arduino core 3.3.11).

Arduino display stack per Adafruit: "GFX Library for Arduino" (moononournation/Arduino_GFX) with `Arduino_XCA9554SWSPI` (expander at 0x3F) + `Arduino_ESP32RGBPanel` + `Arduino_RGB_Display`; touch via `Adafruit_FT6206` (FocalTech, often 0x48) or `Adafruit_CST8XX` (CST826 at 0x15 on the 2.1" round). See `wiki/arduino-rainbow-demo.md`.

## Operational notes

- **Only 40-pin RGB-666 panels.** Adafruit warns that other 40-pin pinouts put power on different pins and can damage the display. Compare against the TL021WVC02 spec linked in the overview before connecting a third-party panel.
- **Backlight current is set by jumpers, not software.** Default 25 mA is safe for every Adafruit panel; per-panel maximums are in `wiki/backlight-settings.md` (e.g. 2.8" round 100 mA, 4" 720×720 50 mA).
- **Panels need init over the expander's software SPI.** Timings (porches, sync widths, pixel clock) must be supplied per panel; see `wiki/determining-timings.md`.
- **Deep sleep (< 1 mA per Adafruit)** needs a set order: send panel Sleep In (0x10), stop the dot clock, reconfigure the expander's backlight pin as an output and drive all outputs low, then sleep. Out of order, the backlight stays on at 170–200 mA. Sleep current cannot be measured while a USB host is connected.
- **Almost every GPIO is used by the panel.** The free I/O is the SPI header (5/6/7/15), A0/A1 (17/16) and I2C.
- **TX/RX and A1/A0 share GPIO16/17.**

## Applications

- **Large touch dashboard** (480×480 to 720×720 or 320×960 bar): Wi-Fi data rendered from the PSRAM frame buffer at about 30 FPS, touch overlay on the shared I2C bus.
- **Media playback demo:** SPI header + A0/A1 carry an SD card (1-bit SDIO) and an I2S amplifier, per Adafruit's A/V demo.
- **Rotary/round gauge display** on the 2.1"/2.8" round panels with UP/DN buttons read through the expander.
- Unsuitable for battery projects without an external charger (none on board), or for projects needing many free GPIO.

## Files

- `hardware/eagle.sch`, `hardware/eagle.brd`: Adafruit EagleCAD design
- `reference/platformio-board.json`: `adafruit_qualia_s3_rgb666` board definition
- `reference/arduino-esp32-pins_arduino.h`: Arduino core variant header (panel, expander and header pins)
- `wiki/`: Learn guide pages (overview, pinouts, downloads incl. schematic/fab-print images, Arduino library + rainbow demo, backlight settings, timings, deep sleep)
