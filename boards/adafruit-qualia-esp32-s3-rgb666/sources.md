# Sources (fetched 2026-09-22)

Vendor pages (Adafruit Learn, guide "Adafruit Qualia ESP32-S3 for RGB-666 Displays"):

- https://learn.adafruit.com/adafruit-qualia-esp32-s3-for-rgb666-displays/overview → `wiki/overview.md`
- https://learn.adafruit.com/adafruit-qualia-esp32-s3-for-rgb666-displays/pinouts → `wiki/pinouts.md`
- https://learn.adafruit.com/adafruit-qualia-esp32-s3-for-rgb666-displays/downloads → `wiki/downloads.md`
- https://www.adafruit.com/product/5800 — used only to find the guide URL.

Hardware:

- `adafruit/Adafruit-Qualia-S3-RGB666-PCB` @ `789d986f34e7949f0477ffd4a9567d1a4c07b310`: `Adafruit Qualia S3 RGB666.sch`/`.brd` → `hardware/eagle.sch`/`.brd`. The repo's `factory-reset/` firmware was not copied.

Board definitions:

- https://raw.githubusercontent.com/espressif/arduino-esp32/master/variants/adafruit_qualia_s3_rgb666/pins_arduino.h → `reference/pins_arduino.h`. `espressif/arduino-esp32` `master` @ `e518da106ae3d7a96870feb2fca7d9dabb2b2c66`.
- https://raw.githubusercontent.com/pioarduino/platform-espressif32/develop/boards/adafruit_qualia_s3_rgb666.json → `reference/platformio-board.json`. This is the pioarduino platform the projects build with, not the upstream platformio one.

Project files:

- `wollkind/pio-piotest`: `platformio.ini` and `src/main.cpp` (panel selection, expander address, touch controller).
- `wollkind/pio-blink`, `wollkind/pio-feather`: `platformio.ini` (`[env:qualia]`; the `LED_BUILTIN=18` note comes from pio-blink).

Not fetched:

- The ST7701 and NV3052C panel-controller datasheets linked from the Downloads page — they belong to the display, not this board, and the owner's panel is a TL040WVS03.
- Adafruit's rehosted ESP32-S3 datasheet and TRM; the Espressif originals are in `chips/esp32-s3/`.
- 3D models and the Fritzing part.
