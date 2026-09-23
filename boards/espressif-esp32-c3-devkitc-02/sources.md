# Sources (fetched 2026-09-23)

- User guide https://docs.espressif.com/projects/esp-dev-kits/en/latest/esp32c3/esp32-c3-devkitc-02/user_guide.html → `wiki/user-guide.md` (with images). The footnotes (strapping pins GPIO2/8/9) were lost in conversion and were read from the raw HTML.
- https://dl.espressif.com/dl/schematics/SCH_ESP32-C3-DEVKITC-02_V1_1_20210126A.pdf → `hardware/schematic-v1.1.pdf` (CP2102N, SGM2212-3.3, SK68XXMINI-HS read from its text layer)
- https://dl.espressif.com/dl/schematics/PCB_ESP32-C3-DevKitC-02_V1_1_20210121AA.pdf → `hardware/pcb-layout-v1.1.pdf`
- https://dl.espressif.com/dl/schematics/DXF_ESP32-C3-DevKitC-02_V1_1_20210121AA.pdf → `hardware/dimensions-v1.1.pdf` (the `.dxf` source was not fetched)
- https://www.espressif.com/sites/default/files/documentation/esp32-c3-wroom-02_datasheet_en.pdf → `datasheets/esp32-c3-wroom-02_datasheet_en.pdf`
- https://github.com/platformio/platform-espressif32 @ `1152c8f69146ca0c20ab772264606b3cc61ec67c`: `boards/esp32-c3-devkitc-02.json` → `reference/platformio-board.json`
- https://github.com/espressif/arduino-esp32 @ `e518da106ae3d7a96870feb2fca7d9dabb2b2c66`: `variants/esp32c3/pins_arduino.h` → `reference/arduino-esp32-pins_arduino.h`. The same header at tag `3.3.1` was also checked.
- Build test: `wollkind/pio-blink` `platformio.ini`, with `platform` pointed at https://github.com/pioarduino/platform-espressif32/releases/download/55.03.311/platform-espressif32.zip (framework-arduinoespressif32 3.3.11), `pio run -e esp32-c3` on 2026-09-23 → compile error described in `README.md`.
