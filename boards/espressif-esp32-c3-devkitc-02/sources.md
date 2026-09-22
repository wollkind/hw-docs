# Sources (fetched 2026-09-22)

- https://docs.espressif.com/projects/esp-dev-kits/en/latest/esp32c3/esp32-c3-devkitc-02/user_guide.html → `wiki/user-guide.md`
- https://dl.espressif.com/dl/schematics/SCH_ESP32-C3-DEVKITC-02_V1_1_20210126A.pdf → `hardware/schematic-v1.1.pdf`
- https://dl.espressif.com/dl/schematics/DXF_ESP32-C3-DevKitC-02_V1_1_20210121AA.pdf → `hardware/dimensions-v1.1.pdf`
- https://dl.espressif.com/dl/schematics/PCB_ESP32-C3-DevKitC-02_V1_1_20210121AA.pdf → `hardware/pcb-layout-v1.1.pdf`
- https://www.espressif.com/sites/default/files/documentation/esp32-c3-wroom-02_datasheet_en.pdf → `hardware/esp32-c3-wroom-02_datasheet_en.pdf`
- https://raw.githubusercontent.com/pioarduino/platform-espressif32/develop/boards/esp32-c3-devkitc-02.json → `reference/platformio-board.json`. `pioarduino/platform-espressif32` `develop` @ `ed2878c14f86b9bff852bc0644e639e64798ab57`.

Not fetched: the DXF source of the dimensions drawing.

Project files: `wollkind/pio-blink` `platformio.ini` (`[env:esp32-c3]`, including its `-D LED_BUILTIN=8`).

The ESP32-C3 chip datasheet, TRM and errata are in `chips/esp32-c3/`.
