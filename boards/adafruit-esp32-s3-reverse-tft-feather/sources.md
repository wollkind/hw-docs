# Sources (fetched 2026-09-21)

- Product page https://www.adafruit.com/product/5691 and the Learn guide: **not fetched** — adafruit.com and cdn-learn.adafruit.com are blocked by the sandbox proxy. Feature text quoted in `README.md` comes from the PCB repo's own README.
- https://github.com/adafruit/Adafruit-ESP32-S3-Reverse-TFT-Feather-PCB @ `633459d74623227a18f7c4b1594db0840ba5592d`:
  - `Adafruit ESP32-S3 Reverse TFT Feather.sch` → `hardware/eagle.sch`; `… .brd` → `hardware/eagle.brd`
  - `Adafruit_ESP32-S3_Reverse_TFT_Feather_Pinout.pdf` → `hardware/pinout.pdf`
  - `PrettyPins … Display-Side Pinout.pdf` → `hardware/pinout-display-side.pdf`
  - Button polarity, the GPIO7 power gate, the NeoPixel power pin and the BME280/MAX17048 footprints were read out of the schematic XML nets.
- https://github.com/platformio/platform-espressif32, branch `develop`, `boards/adafruit_feather_esp32s3_reversetft.json` → `reference/platformio-board.json`
- https://github.com/espressif/arduino-esp32, branch `master`, `variants/adafruit_feather_esp32s3_reversetft/pins_arduino.h` → `reference/arduino-esp32-pins_arduino.h`
- https://github.com/adafruit/circuitpython, branch `main`, `ports/espressif/boards/adafruit_feather_esp32s3_reverse_tft/{pins.c,mpconfigboard.h,mpconfigboard.mk,sdkconfig}` → `reference/cpy-*`
  (all three fetched via raw; no SHAs recorded because api.github.com is blocked)
- Not copied: the `.svg` versions of both pinout diagrams, `assets/5691-02.jpg`, the factory-reset UF2 notes.
- Missing: the Adafruit Learn guide, and datasheets for MAX17048, MCP73831 and ST7789 on this board (the ST7789 is covered indirectly by `parts/waveshare-1.69in-lcd-module`).
