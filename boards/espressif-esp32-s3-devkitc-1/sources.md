# Sources (fetched 2026-09-22)

- https://docs.espressif.com/projects/esp-dev-kits/en/latest/esp32s3/esp32-s3-devkitc-1/user_guide_v1.1.html → `wiki/user-guide-v1.1.md`. The `.../user_guide.html` URL used by the other dev-kit guides 404s for this board; the index page links the versioned guide instead.
- https://dl.espressif.com/dl/schematics/SCH_ESP32-S3-DevKitC-1_V1.1_20221130.pdf → `hardware/schematic-v1.1.pdf`
- https://dl.espressif.com/dl/schematics/PCB_ESP32-S3-DevKitC-1_V1.1_20220429.pdf → `hardware/pcb-layout-v1.1.pdf`
- https://dl.espressif.com/dl/schematics/esp_idf/DXF_ESP32-S3-DevKitC-1_V1.1_20220429.pdf → `hardware/dimensions-v1.1.pdf`
- https://www.espressif.com/sites/default/files/documentation/esp32-s3-wroom-2_datasheet_en.pdf → `hardware/esp32-s3-wroom-2_datasheet_en.pdf`
- https://raw.githubusercontent.com/pioarduino/platform-espressif32/develop/boards/{esp32-s3-devkitc-1,esp32-s3-devkitc1-n8r8,esp32-s3-devkitc1-n16r8}.json → `reference/`. `pioarduino/platform-espressif32` `develop` @ `ed2878c14f86b9bff852bc0644e639e64798ab57`. There is no `esp32-s3-devkitc1-n32r8v` board file in that platform.

Not fetched:

- The v1.0 user guide (linked from the v1.1 page; its only substantive difference is the RGB LED pin, recorded here).
- `https://documentation.espressif.com/ESP32-S3-DevKitC-1_Reference_Design.zip` — the reference design archive; not needed to use the board.
- The DXF source of the dimensions drawing.

Project files: `wollkind/infopanel64`, `pio-strip-com`, `pio-rlcd`, `pio-crowpanel2` `platformio.ini` — the four places these board ids are used as profiles for other hardware.
