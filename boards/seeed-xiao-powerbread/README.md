# XIAO PowerBread (Seeed SKU 6318, open-source design by nicho810)

Breadboard power supply and power meter that takes a XIAO as its brain: regulated 5 V and 3.3 V rails, dual-channel INA3221 sensing, a 0.96" ST7735 LCD and a dial. Hardware v1.2.
Used by: no project found.

## Key specs

| | |
|---|---|
| Input | USB-C, through the XIAO |
| Outputs | 5 V and 3.3 V rails; **1.5 A max on 3.3 V** |
| Regulator | TPS54202 buck; MT9700 load switch on the output path |
| Sensing | INA3221 three-channel voltage/current monitor at I2C **0x40**, used as two channels |
| Display | 0.96" ST7735S LCD (ZJY096T-IG11 module) |
| Input device | one dial (analog), long-press switches channel in chart/stats modes |
| Host boards | XIAO RP2040, RP2350, ESP32-C3, ESP32-S3, ESP32-C6. **Not** SAMD21 or RA4M1 |
| Firmware | Arduino/PlatformIO, LVGL 8.3 + LovyanGFX, FreeRTOS; v3.0 adds a 100 Hz USB-serial streaming protocol and a browser console |

## Pinout (XIAO pad names, from `reference/boardConfig.h`)

| Signal | XIAO pad | RP2040 / RP2350 GPIO |
|---|---|---|
| Dial (ADC) | D2 | 28 |
| LCD SCLK | D8 | 2 |
| LCD MOSI | D10 | 3 |
| LCD DC | D9 | 4 |
| LCD RST | D3 | 29 (RP2040) / 5 (RP2350) |
| LCD CS | — | tied, not driven (`-1`) |
| I2C SDA | D4 | 6 |
| I2C SCL | D5 | 7 |

The ESP32-C3/S3/C6 builds use the same pads by name. Note the LCD RST GPIO differs between RP2040 (29) and RP2350 (5) even though both map to pad D3.

## Firmware build

```ini
[env:seeed_xiao_esp32s3]
platform = espressif32
board = seeed_xiao_esp32s3
framework = arduino
lib_deps =
    robtillaart/INA3221@^0.4.0
    lvgl/lvgl@^8.3.4
    lovyan03/LovyanGFX@^1.2.0
```

The RP2040/RP2350 environments use `maxgerhardt/platform-raspberrypi` with `board_build.core = earlephilhower`, boards `rpipico` / `rpipico2`, and add `-D USE_TINYUSB`. Each environment sets its own `-D SEEED_XIAO_*` flag, which is what selects the pin block above.

## Gotchas

- **v3.0 firmware is ESP32-only.** The project's README states the RP2040 / RP2350 ports have an unresolved FreeRTOS scheduling bug; those boards should stay on **v2.0.1** until the port lands.
- **The XIAO SAMD21 and RA4M1 are not supported** — no compatible firmware.
- **The LCD chip-select is not driven** (`pin_lcd_cs -1`), so the panel is permanently selected; another SPI device cannot share that bus.
- **I2C peripheral choice is board-specific**: the firmware picks `Wire` or `Wire1` inside `INA3221Sensor.cpp`, and the SPI host likewise in `LGFX_096_XPB.hpp`. Porting to another XIAO means touching both, not just the pin macros.
- **1.5 A is the 3.3 V rail's limit**, not a per-rail figure for 5 V; the 5 V rail passes through from USB.

## Files

- `hardware/schematic-v1.2.pdf`, `hardware/pcb-v1.2.pdf`
- `datasheets/ina3221.pdf`, `st7735s.pdf`, `lcd-module-zjy096t-ig11.pdf`, `tps54202.pdf`, `mt9700-power-switch.pdf`
- `reference/boardConfig.h`: the per-XIAO pin macros
- `reference/xpb-platformio.ini`: all five build environments
- `wiki/powerbread-repo-readme.md`, `wiki/sysConfig.md`: the project readme and its settings documentation
