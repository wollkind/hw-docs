# Waveshare 1.69" LCD Module (240×280, ST7789V2)

A 1.69" IPS SPI display with rounded corners. Waveshare makes it, and Seeed resells it as SKU 5755 ("1.69inch LCD Display Module").
Used by: none yet. (`mlab` and `num1-2` use 240×240 ST7789 panels, not this one.)

## Key specs

| | |
|---|---|
| Controller | ST7789V2 (RAM is 240×320; the panel uses 240×280 of it) |
| Resolution | 240 (H) × 280 (V), RGB444/565/666 (262K colours) |
| Interface | 4-wire SPI, write-only (no MISO) |
| Supply / logic | 3.3 V **or** 5 V. Supply and logic must be the same voltage |
| Connector | GH1.25 8-pin |
| Active area | 27.97 × 32.63 mm, pitch 0.11655 mm, corner radius R5 |
| Module size | 31.5 × 39.0 mm |

## Pinout (8-pin) and wiring

| Pin | Function | XIAO (Seeed lib default) | Arduino UNO | Raspberry Pi BCM (header pin) | STM32 |
|---|---|---|---|---|---|
| VCC | 3.3/5 V | 3V3 | 5V | 3.3V | 3.3V |
| GND | | GND | GND | GND | GND |
| DIN | MOSI | D10 | D11 | MOSI (19) | PA7 |
| CLK | SCK | D8 | D13 | SCLK (23) | PA5 |
| CS | chip select, active low | D1 | D10 | CE0 (24) | PB6 |
| DC | 0 = command, 1 = data | D3 | D7 | 25 (22) | PA8 |
| RST | reset, active low | D0 | D8 | 27 (13) | PA9 |
| BL | backlight (PWM) | D6 | D9 | 18 (12) | PC7 |

The pin assignments come from `wiki/waveshare-wiki.md` (UNO, Pi, STM32) and `wiki/seeed-wiki.md` / `reference/xiao-lib-st7789v2.h` (XIAO).

## Libraries

- **Adafruit ST7735 and ST7789:** `Adafruit_ST7789 tft(CS, DC, RST); tft.init(240, 280);`. For any size other than 240×240 or 135×240, the library centres the window in controller RAM, which gives a row offset of (320−280)/2 = 20. That's the offset this panel needs (from `Adafruit_ST7789.cpp` @ 62112b9).
- **Seeed XIAO library:** [limengdu/XIAO_ST7789V2_LCD_Display](https://github.com/limengdu/XIAO_ST7789V2_LCD_Display), adapted from Waveshare's demo. Its README is in `reference/xiao-lib-README.md`.
- **TFT_eSPI:** set `ST7789_DRIVER`, `TFT_WIDTH 240`, `TFT_HEIGHT 280` (unverified).

## Operational notes

- **Rounded corners:** the corners clip about R5 mm of the image, so keep UI clear of them.
- **Supply and logic voltage must match.** With a 5 V supply, the MCU has to drive 5 V logic. Use 3.3 V with ESP32, XIAO or RP2040 boards.
- **Offset:** the panel sits 20 rows into the controller's 320-row RAM. A driver set up for 240×320 or 240×240 draws shifted and wraps garbage at the edge.

## Applications

- **Compact status display.** 240×280 with rounded corners in a 31.5 × 39.0 mm module, suitable for handheld enclosures.
- **Dual-voltage wiring.** The module accepts 3.3 V or 5 V, provided supply and logic use the same voltage. This permits direct connection to 5 V logic without a level shifter.
- **Constraint:** the interface is write-only with no MISO line, so the controller state cannot be read back.

## Files

- `wiki/waveshare-wiki.md`, `wiki/seeed-wiki.md` (+ `img/`)
- `hardware/schematic.pdf`, `hardware/dimensions-2d.pdf`, `hardware/3d-model.step`
- `datasheets/st7789v2.pdf`
- `reference/`: XIAO library header and README
