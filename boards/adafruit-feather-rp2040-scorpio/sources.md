# Sources (fetched 2026-09-21)

- Product page https://www.adafruit.com/product/5650 and the Learn guide: **not fetched** — adafruit.com and cdn-learn.adafruit.com are blocked by the sandbox egress proxy. Product identified by web search; description text confirmed from the PCB repo's own README.
- https://github.com/adafruit/Adafruit-Feather-RP2040-SCORPIO-PCB @ `e724d4d8524af681a166bce0f3d29dee50b44cb1`: `Adafruit Feather RP2040 Scorpio.sch` → `hardware/eagle.sch`, `… .brd` → `hardware/eagle.brd`. Part values, net connections (74AHCT245 A1–A8 = GPIO16–23, `/OE` to GND, VCC from SJ1, T/R from SJ2; MCP73831 PROG through R8 = 5.1 kΩ) were read out of the schematic XML.
- https://github.com/adafruit/circuitpython, branch `main`, `ports/raspberrypi/boards/adafruit_feather_rp2040_scorpio/{pins.c,mpconfigboard.h,mpconfigboard.mk}` → `reference/cpy-*` (fetched via raw; no SHA recorded, api.github.com is blocked).
- https://github.com/earlephilhower/arduino-pico, branch `master`, `variants/adafruit_feather_scorpio/pins_arduino.h` → `reference/arduino-pico-pins_arduino.h`; board id read from `boards.txt`.
- Not copied: `assets/5650.jpg` from the PCB repo, and the 3D model in https://github.com/adafruit/Adafruit_CAD_Parts (`5650 Feather RP2040 Scorpio`).
- Missing: the Adafruit Learn guide (pinout page, power notes, jumper defaults) and the RP2040 datasheet — datasheets.raspberrypi.com and www.raspberrypi.com are blocked by the proxy (checked), so there is no `chips/rp2040` entry. Also missing: MCP73831 and 74AHCT245 datasheets.
