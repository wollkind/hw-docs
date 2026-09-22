# Sources (fetched 2026-09-21)

- Product page https://www.waveshare.com/esp32-s3-rlcd-4.2.htm and the wiki https://docs.waveshare.com/ESP32-S3-RLCD-4.2: **not fetched** — waveshare.com and docs.waveshare.com are blocked by the sandbox egress proxy. The wiki is where the schematic, dimensions and the ST7305/ES8311/PCF85063/SHTC3 datasheets live.
- https://github.com/waveshareteam/ESP32-S3-RLCD-4.2 @ `eb1f63427d735a22b9c30e22fa63ebddae1834d3`:
  - `02_Example/ESP-IDF/05_I2C_SHTC3/main/user_config.h` → `reference/user_config.h`
  - `02_Example/Arduino/07_Audio_Test/src/ExternLib/codec_board/board_cfg.h` → `reference/codec-board_cfg.h`
  - `02_Example/Arduino/06_SD_Card/sdcard_bsp.h` → `reference/sdcard_bsp.h`
  - `02_Example/Arduino/03_ADC_Test/adc_bsp.cpp` → `reference/adc_bsp.cpp`
  - `README.md` → `wiki/waveshare-repo-readme.md`
  - I2C addresses read from `02_Example/Arduino/04_I2C_PCF85063/{04_I2C_PCF85063.ino,i2c_equipment.h}`, `05_I2C_SHTC3/i2c_equipment.h` and `07_Audio_Test/codec_bsp.h`.
- Not copied: `01_Arduino_Libraries/` (416 MB), the rest of `02_Example/` (194 MB), `03_Firmware/` (16 MB).
- `wollkind/pio-rlcd` (shallow clone): `platformio.ini` and `src/main.cpp` gave the working build config and confirmed the display pin set; `src/i2c_bsp.h` settled the `(scl, sda, port)` argument order.
- Missing: schematic, dimensions and the ST7305 datasheet — all behind the blocked Waveshare wiki. No `parts/st7305` entry as a result.
