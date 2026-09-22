# Sources (fetched 2026-09-22)

- https://docs.espressif.com/projects/esp-dev-kits/en/latest/esp32c5/esp32-c5-devkitc-1/user_guide.html → `wiki/user-guide.md` (v1.2; the v1.1 guide is linked from it and was not fetched)
- https://dl.espressif.com/dl/schematics/SCH_ESP32-C5-DevkitC-1_V1.2_20250211.pdf → `hardware/schematic-v1.2.pdf`
- https://dl.espressif.com/dl/schematics/PCB_ESP32-C5-DevKitC-1_V1.2_20250211.pdf → `hardware/pcb-layout-v1.2.pdf`
- https://dl.espressif.com/dl/schematics/Dimension_esp32-c5-devkitc-1_v1.2_20250509.pdf → `hardware/dimensions-v1.2.pdf`
- https://www.espressif.com/sites/default/files/documentation/esp32-c5-wroom-1_wroom-1u_datasheet_en.pdf → `hardware/esp32-c5-wroom-1_datasheet_en.pdf`

Not fetched: the DXF source of the dimensions drawing, and the v1.1 user guide.

**No PlatformIO board file is copied here.** `pio-seafive` builds `board = esp32-c5-devkitc1-n4` from the pioarduino `stable` release zip rather than a git checkout, and that id is not in the platform's `develop` branch under the name the documentation uses; the project's `platformio.ini` is the record of what it builds.

Project files: `wollkind/pio-seafive` `platformio.ini` (`[env]`, `[env:mcu_a]`, `[env:mcu_b]`, `[env:mcu_b_debug]`).

The ESP32-C5 chip datasheet, TRM and errata are in `chips/esp32-c5/`.
