# Sources (fetched 2026-09-22)

- https://docs.espressif.com/projects/esp-dev-kits/en/latest/esp32c6/esp32-c6-devkitc-1/user_guide.html → `wiki/user-guide.md` (v1.2; the v1.1 guide is linked from it and was not fetched)
- https://dl.espressif.com/dl/schematics/esp32-c6-devkitc-1-schematics_v1.4.pdf → `hardware/schematics_v1.4.pdf`
- https://dl.espressif.com/dl/schematics/esp32-c6-devkitc-1-dimensions_v1.2.pdf → `hardware/dimensions_v1.2.pdf`
- https://dl.espressif.com/dl/schematics/esp32-c6-devkitc-1-pcb-layout_v1.2.pdf → `hardware/pcb-layout_v1.2.pdf`
- https://www.espressif.com/sites/default/files/documentation/esp32-c6-wroom-1_wroom-1u_datasheet_en.pdf → `hardware/esp32-c6-wroom-1_datasheet_en.pdf`
- https://raw.githubusercontent.com/pioarduino/platform-espressif32/develop/boards/esp32-c6-devkitc-1.json → `reference/platformio-board.json`. `pioarduino/platform-espressif32` `develop` @ `ed2878c14f86b9bff852bc0644e639e64798ab57`.

Older schematics, not fetched (applicable to earlier boards):

- https://dl.espressif.com/dl/schematics/esp32-c6-devkitc-1-schematics_v1.3.pdf — boards from PW-2023-07-0440
- https://dl.espressif.com/dl/schematics/esp32-c6-devkitc-1-schematics_v1.2.pdf — boards before PW-2023-07-0440
- https://dl.espressif.com/dl/schematics/esp32-c6-devkitc-1-dimensions_v1.2.dxf — DXF source of the dimensions PDF

Project files: `wollkind/pio-blink` `platformio.ini` (`[env:esp32-c6]`).

The ESP32-C6 chip datasheet and TRM are in `chips/esp32-c6/`, not duplicated here.
