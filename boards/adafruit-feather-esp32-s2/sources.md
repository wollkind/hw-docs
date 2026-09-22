# Sources (fetched 2026-09-21)

- Product pages https://www.adafruit.com/product/5000 and /5303, and the Learn guide: not fetched — adafruit.com and cdn-learn.adafruit.com are blocked by the sandbox proxy.
- https://github.com/adafruit/Adafruit-ESP32-S2-Feather-PCB @ `4a6263861580257d42a889a1518133441d25f35d`: `Adafruit Feather ESP32-S2 Rev C.{sch,brd}` → `hardware/eagle-revc.*`, `Adafruit Feather ESP32-S2 Pinout.pdf` → `hardware/pinout.pdf`. Part list (LC709203F, MCP73831, two LDOs, BME280 footprint, WS2812B) read from the schematic XML.
- https://github.com/platformio/platform-espressif32, branch `develop`: `boards/featheresp32-s2.json` → `reference/platformio-board.json`; `boards/adafruit_feather_esp32s2.json` read for the comparison in `README.md` (not copied).
- https://github.com/adafruit/circuitpython, branch `main`, `ports/espressif/boards/adafruit_feather_esp32s2/{pins.c,mpconfigboard.h,mpconfigboard.mk}` → `reference/cpy-*`.
- Owner's projects (shallow clones): `wollkind/pio-bme280`, `wollkind/pio-bme680`, `wollkind/pio-feather` — all three build `board = featheresp32-s2`.
- Not verified: the LC709203F I2C address (schematic nets not traced for it), and which of PID 5000 / 5303 the owner actually has.
- Missing: the ESP32-S2 datasheet (espressif.com blocked), so no `chips/esp32-s2` entry.
