# Sources (fetched 2026-09-22)

Vendor pages (Adafruit Learn, guide "Adafruit Feather HUZZAH ESP8266"):

- https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/overview → `wiki/overview.md`
- https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/pinouts → `wiki/pinouts.md`
- https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/downloads → `wiki/downloads.md`

Files:

- https://cdn-learn.adafruit.com/assets/assets/000/046/211/original/Huzzah_ESP8266_Pinout_v1.2.pdf → `hardware/pinout-v1.2.pdf`
- http://www.adafruit.com/datasheets/cp2104.pdf → `hardware/cp2104-datasheet.pdf`
- `adafruit/Adafruit-Feather-ESP8266-HUZZAH-PCB` @ `957300988eee7d15d71649fd4e2cb023a6584acb`: `Adafruit ESP8266 Feather rev G.sch`/`.brd` → `hardware/eagle-revg.sch`/`.brd`. The repo also holds the earlier plain and Rev E files, not copied.

Board definitions:

- https://raw.githubusercontent.com/platformio/platform-espressif8266/668c2a2e4f16bd83b6c812f1ee0605c62b3ce2d2/boards/huzzah.json → `reference/platformio-huzzah.json`
- https://raw.githubusercontent.com/esp8266/Arduino/1475ed7d49fef5c5167061ac76abb6eced9abda5/variants/adafruit/pins_arduino.h → `reference/pins_arduino.h`

Project files:

- `wollkind/pio-huzzah`: `platformio.ini`, `src/main.cpp` (the FeatherWing pin block that identifies the board as a Feather rather than the 2471 breakout).
- `wollkind/pio-radio`: `platformio.ini` (`[env:huzzah]` beside the `feather32u4` env).

Not fetched:

- The AP2112 regulator datasheet (diodes.com), the ESP-12 FCC and CE test reports, and Adafruit's rehosted ESP8266 specification sheet — the current Espressif datasheet is in `chips/esp8266/`.
- 3D models (`Adafruit_CAD_Parts`) and the Fritzing object.
