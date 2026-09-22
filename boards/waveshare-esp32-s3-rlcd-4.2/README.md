# Waveshare ESP32-S3-RLCD-4.2

AIoT board with a 4.2" **reflective** LCD (no backlight), an audio front end, RTC, temperature/humidity sensor, microSD and an 18650 holder. Chip: [../../chips/esp32-s3](../../chips/esp32-s3/README.md).
Used by: **`pio-rlcd`** (U8g2 + a hand-written `ST7305_U8g2` driver, LVGL 9.3 and SensorLib in `lib_deps`).

## Key specs (Waveshare's repo readme)

| | |
|---|---|
| Module | ESP32-S3-WROOM-1-N16R8, dual Xtensa LX7 @ 240 MHz |
| Flash / PSRAM | 16 MB / 8 MB |
| Wireless | 2.4 GHz Wi-Fi, Bluetooth 5 LE |
| Display | 4.2" reflective LCD, 300 × 400, ST7305 controller, SPI, no backlight |
| Audio out | ES8311 codec at I2C **0x18**, PA enable on GPIO46 |
| Audio in | ES7210 at I2C **0x40**, dual-mic array |
| RTC | PCF85063 at I2C **0x51** |
| Sensor | SHTC3 temperature/humidity at I2C **0x70** |
| Storage | microSD (SDMMC, 1-bit) |
| Power | USB Type-C, 18650 holder; battery on ADC1 channel 3 through a ÷3 divider |

## Pinout

Display (Waveshare's `user_config.h`; identical in the owner's `pio-rlcd` except that it does not use TE):

| Signal | GPIO |
|---|---|
| SCK | 11 |
| MOSI | 12 |
| DC | 5 |
| CS | 40 |
| RST | 41 |
| TE | 6 |

I2C bus, shared by the codecs, RTC and SHTC3: **SDA 13, SCL 14**.

> Waveshare's examples construct the bus as `I2cMasterBus I2cbus(14, 13, 0)`, which reads like SDA 14 / SCL 13 — but the constructor is `(scl_pin, sda_pin, i2c_port)`, so it agrees with `user_config.h`. The owner's `pio-rlcd` copies the same call.

Audio (I2S, from `codec-board_cfg.h`, board entry `S3_RLCD_4_2`):

| Signal | GPIO |
|---|---|
| MCLK / BCLK / WS | 16 / 9 / 45 |
| DIN (mics) / DOUT (speaker) | 10 / 8 |
| Speaker PA enable | 46 |

microSD over SDMMC, 1-bit (defaults in `sdcard_bsp.h`): CLK 38, CMD 21, D0 39.

Battery: ADC1 channel 3 — GPIO4 on the ESP32-S3 `(unverified — the pin/channel mapping is not cross-checked against the datasheet, and the schematic's text layer gives net names such as `BAT_ADC` and `VBAT` without the pin they land on)`. Waveshare's code multiplies the calibrated reading by 3.

The schematic also carries four key nets (`Key1`–`Key4`) and a `PA_CTRL` speaker-amplifier enable, none of which Waveshare's example headers name. Read the GPIO off `hardware/schematic.pdf` before using them.

## PlatformIO (as used in `pio-rlcd`)

```ini
[env:esp32dev]
platform = https://github.com/pioarduino/platform-espressif32/releases/download/stable/platform-espressif32.zip
board = esp32-s3-devkitc1-n16r8
framework = arduino
lib_deps =
    lvgl/lvgl@9.3.0
    olikraus/U8g2@^2.36.18
    lewisxhe/SensorLib@^0.4.1
```

Waveshare ships Arduino, ESP-IDF, ESPHome and XiaoZhi examples plus prebuilt firmware; there is no vendor PlatformIO board file, hence the generic N16R8 devkit target.

## Operational notes

- **Width and height swap between examples.** Waveshare's own `user_config.h` files disagree: the SHTC3 and audio examples set 400 × 300, the SD and ADC ones 300 × 400. The panel is 300 (H) × 400 (V); which way round the constants go depends on the rotation the sketch uses. `pio-rlcd` uses 400 × 300.
- **Reflective panel, no backlight** — nothing to PWM, and contrast depends on ambient light.
- **ST7305 is not a common Arduino target.** The owner wrote `ST7305_U8g2` for `pio-rlcd`; Waveshare's own examples use their bundled driver. There is no mainstream library to fall back on.
- **The codec, RTC and sensor all share one I2C bus** at 13/14; a bus hang takes out audio, time and temperature together.
- **PA on GPIO46 must be driven** for speaker output; ES8311 alone produces silence.

## Applications

- **Always-on desk display.** The reflective panel requires no backlight, so static content costs almost nothing to retain. PCF85063 holds time; the 18650 holder supplies extended runtime.
- **Voice-controlled display terminal.** ES7210 dual microphones in, ES8311 and speaker out, with the display as the response surface. `pio-rlcd` already drives the ST7305 through U8g2.
- **Environmental readout.** The onboard SHTC3 at 0x70 requires no external sensor.
- **Constraint:** contrast depends on ambient light. This board is unsuitable for dark environments.

## Files

- `hardware/schematic.pdf`: Waveshare's schematic (fetched 2026-09-22, once docs.waveshare.com became reachable)
- `hardware/3d-model.rar`: the structure and dimensions archive, left packed
- `datasheets/st7305-v0.2.pdf`: the reflective LCD controller, Sitronix ST7305 V0.2
- `datasheets/es8311.pdf`, `datasheets/shtc3.pdf`, `datasheets/pcf85063atl.pdf`: the audio codec, humidity/temperature sensor and RTC
- `reference/user_config.h`: Waveshare's display and I2C pin header
- `reference/codec-board_cfg.h`: the `S3_RLCD_4_2` audio board entry (I2S pins, codecs, PA)
- `reference/sdcard_bsp.h`: SDMMC pin defaults
- `reference/adc_bsp.cpp`: battery measurement (ADC1 ch 3, ÷3 scaling, level thresholds)
- `wiki/waveshare-repo-readme.md`: Waveshare's repo readme (specs, repo layout)
