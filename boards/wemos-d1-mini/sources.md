# Sources (fetched 2026-09-23)

- https://www.wemos.cc/en/latest/d1/d1_mini.html (V4.0.0, current) → `wiki/d1-mini.md` (with images)
- https://www.wemos.cc/en/latest/d1/d1_mini_3.1.0.html → `wiki/d1-mini-v3.1.0.md` (carries the pin table the V4 page shows only as an image)
- https://www.wemos.cc/en/latest/_static/files/sch_d1_mini_v4.0.0.pdf → `hardware/schematic-v4.0.0.pdf` (KiCad; ME6211C33, CH340C, UMH3N, R12/R13 220k/100k, JP1 + 470 Ω, LOLIN I2C connector read from it)
- https://www.wemos.cc/en/latest/_static/files/dim_d1_mini_v4.0.0.pdf → `hardware/dimensions-v4.0.0.pdf`
- https://www.wemos.cc/en/latest/_static/files/sch_d1_mini_v3.0.0.pdf → `hardware/schematic-v3.0.0.pdf` (image-only PDF, read visually: ME6211, CH340C, W25Q32FVSS, 0.5 A fuse, B5819W, SJ1 deep-sleep jumper, 220k/100k divider)
- https://github.com/platformio/platform-espressif8266 @ `668c2a2e4f16bd83b6c812f1ee0605c62b3ce2d2`: `boards/d1_mini.json` → `reference/platformio-board.json`
- https://github.com/esp8266/Arduino @ `1475ed7d49fef5c5167061ac76abb6eced9abda5`: `variants/d1_mini/pins_arduino.h` → `reference/esp8266-pins_arduino.h`
- Build test: `wollkind/pio-blink` `platformio.ini`, `pio run -e d1-mini` on 2026-09-23 (espressif8266 4.2.1, framework-arduinoespressif8266 3.30102.0) → SUCCESS.
- Not fetched: certification PDFs (CE/RoHS/DoC), CH340 driver page, WEMOS tutorials. V2.x and V3.1.0-specific schematics are not published separately.
- Not read: `wollkind/pio-d1mini` (not attached to this session).
