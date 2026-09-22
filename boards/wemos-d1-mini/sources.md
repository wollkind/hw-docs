# Sources (fetched 2026-09-22)

Vendor pages:

- https://www.wemos.cc/en/latest/d1/d1_mini.html → `wiki/d1-mini.md` (V4.0.0, current)
- https://www.wemos.cc/en/latest/d1/d1_mini_3.1.0.html → `wiki/d1-mini-v3.1.0.md` (carries the pin table; the V4 page replaced it with an image)

Files:

- https://www.wemos.cc/en/latest/_static/files/sch_d1_mini_v4.0.0.pdf → `hardware/schematic-v4.0.0.pdf`
- https://www.wemos.cc/en/latest/_static/files/dim_d1_mini_v4.0.0.pdf → `hardware/dimensions-v4.0.0.pdf`
- https://www.wemos.cc/en/latest/_static/files/sch_d1_mini_v3.0.0.pdf → `hardware/schematic-v3.0.0.pdf`. **Image-only PDF** — no extractable text, so nothing in this entry is sourced from it.

Board definitions:

- https://raw.githubusercontent.com/platformio/platform-espressif8266/develop/boards/d1_mini.json → `reference/platformio-d1_mini.json`. `platformio/platform-espressif8266` `develop` @ `668c2a2e4f16bd83b6c812f1ee0605c62b3ce2d2`.
- https://raw.githubusercontent.com/esp8266/Arduino/1475ed7d49fef5c5167061ac76abb6eced9abda5/variants/d1_mini/pins_arduino.h → `reference/pins_arduino.h`. `esp8266/Arduino` `master` @ `1475ed7d49fef5c5167061ac76abb6eced9abda5`.
- https://raw.githubusercontent.com/esp8266/Arduino/1475ed7d49fef5c5167061ac76abb6eced9abda5/tools/sdk/ld/eagle.flash.4m1m.ld → `reference/eagle.flash.4m1m.ld`, same commit.

Project files (for "Used by" and the operational notes):

- `wollkind/pio-d1mini`, `pio-d12`, `pio-bme280`, `pio-bme680`, `pio-feather`, `pio-blink`: `platformio.ini`; `pio-d12/src/main.cpp` for the GPIO5 note.

Not fetched:

- The V4.0.0 certification PDFs (CE/EMC, RoHS, EU DoC). Compliance paperwork, no engineering content.
- The AliExpress "Buy it" link on both vendor pages.
