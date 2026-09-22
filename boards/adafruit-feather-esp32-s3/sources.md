# Sources (fetched 2026-09-22)

Vendor pages (Adafruit Learn, guide "Adafruit ESP32-S3 Feather"):

- https://learn.adafruit.com/adafruit-esp32-s3-feather/pinouts → `wiki/pinouts.md`
- https://learn.adafruit.com/adafruit-esp32-s3-feather/downloads → `wiki/downloads.md`
- https://www.adafruit.com/product/5477 — used only to find the guide URL.

Hardware:

- `adafruit/Adafruit-Feather-ESP32-S3-PCB` @ `2c95ed51a500d929fd6d8f519b895f0c4daeb982`: `Adafruit ESP32-S3 8MB No PSRAM.sch`/`.brd` → `hardware/eagle-8mb-nopsram.sch`/`.brd`, and `Adafruit Feather ESP32-S3 Pinout.pdf` → `hardware/pinout.pdf`. The repository holds **only** the 8 MB no-PSRAM design; there is no separate file for the PID 5477 board.

Board definitions:

- https://raw.githubusercontent.com/espressif/arduino-esp32/e518da106ae3d7a96870feb2fca7d9dabb2b2c66/variants/adafruit_feather_esp32s3/pins_arduino.h → `reference/pins_arduino.h`
- https://raw.githubusercontent.com/pioarduino/platform-espressif32/develop/boards/adafruit_feather_esp32s3.json → `reference/platformio-board.json`
- https://raw.githubusercontent.com/pioarduino/platform-espressif32/develop/boards/adafruit_feather_esp32s3_nopsram.json → `reference/platformio-nopsram.json`

Project files: `wollkind/pio-blink` `platformio.ini` (`[env:feather32-s3]`).

Not fetched: the repository's `factory-reset/` firmware, and Adafruit's rehosted ESP32-S3 datasheet and TRM — the Espressif originals are in `chips/esp32-s3/`.
