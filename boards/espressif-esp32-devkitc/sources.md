# Sources (fetched 2026-09-22)

- https://docs.espressif.com/projects/esp-dev-kits/en/latest/esp32/esp32-devkitc/user_guide.html → `wiki/user-guide.md` (V4; the V2 guide is linked from it and was not fetched)
- https://dl.espressif.com/dl/schematics/esp32_devkitc_v4_sch.pdf → `hardware/schematic-v4.pdf`
- https://dl.espressif.com/dl/schematics/esp32_devkitc_v4_pcb_layout.pdf → `hardware/pcb-layout-v4.pdf`
- https://dl.espressif.com/dl/schematics/esp32_devkitc_v4_dimensions.pdf → `hardware/dimensions-v4.pdf`
- https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32e_esp32-wroom-32ue_datasheet_en.pdf → `hardware/esp32-wroom-32e_datasheet_en.pdf`
- https://raw.githubusercontent.com/platformio/platform-espressif32/develop/boards/esp32dev.json → `reference/platformio-esp32dev.json`

Not fetched: the datasheets for the other module options (WROOM-32, -32D/-32U, -32DA, WROVER-E/-IE, SOLO-1), all linked from the user guide, and the DXF source of the dimensions drawing.

**Identification caveat:** `pio-ir-decode`, `pio-num1-2` and `pio-feather` build `board = esp32dev`, which is a generic ESP32 profile. Nothing in those projects names the physical board, so this entry documents Espressif's reference kit. If the owner's board turns out to be a DOIT/NodeMCU-32S style clone, the pin *functions* still hold (they are the module's) but the board-level details — LED, buttons, power options, the C15 note — do not.

The ESP32 chip datasheet, technical reference and errata are in `chips/esp32/`.
