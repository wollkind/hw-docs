# Sources (fetched 2026-09-23)

- Product pages (titles only read): https://www.adafruit.com/product/5477 ("4MB Flash 2MB PSRAM"), https://www.adafruit.com/product/5323 ("8MB Flash No PSRAM").
- Learn guide https://learn.adafruit.com/adafruit-esp32-s3-feather: `overview`, `pinouts`, `power-management`, `downloads` → `wiki/*.md` (with images). The downloads page is shared with the ESP32-S2 Feather.
- https://github.com/adafruit/Adafruit-Feather-ESP32-S3-PCB @ `2c95ed51a500d929fd6d8f519b895f0c4daeb982`:
  - `Adafruit ESP32-S3 8MB No PSRAM.sch` → `hardware/eagle.sch`; `… .brd` → `hardware/eagle.brd`
  - `Adafruit Feather ESP32-S3 Pinout.pdf` → `hardware/pinout.pdf`
  - Part list (MCP73831, two AP2112/RT9080 LDOs, MBR540, DMG3415U, LC709203F, WS2812B/SK6805-1515, BME280 footprint) read from the schematic XML.
  - Not copied: `factory-reset/` (bootloader 0.18.2 and factory-reset images for both variants), `assets/5323.jpg`.
- https://github.com/platformio/platform-espressif32 @ `1152c8f69146ca0c20ab772264606b3cc61ec67c`: `boards/adafruit_feather_esp32s3.json` → `reference/platformio-board.json`; `boards/adafruit_feather_esp32s3_nopsram.json` read for the variant table (not copied).
- https://github.com/espressif/arduino-esp32 @ `e518da106ae3d7a96870feb2fca7d9dabb2b2c66`: `variants/adafruit_feather_esp32s3/pins_arduino.h` → `reference/arduino-esp32-pins_arduino.h`.
- Owner's project: `wollkind/pio-blink` `platformio.ini`.
- Missing: a schematic for the MAX17048 revision; datasheets for MAX17048, LC709203F, MCP73831; the ESP32-S3-MINI-1 module datasheet.
