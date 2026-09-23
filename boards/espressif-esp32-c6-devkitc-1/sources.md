# Sources (fetched 2026-09-23)

- User guide (v1.2) https://docs.espressif.com/projects/esp-dev-kits/en/latest/esp32c6/esp32-c6-devkitc-1/user_guide.html → `wiki/user-guide.md` (with images). Footnotes (RGB LED, strapping pins) read from the raw HTML because the conversion dropped them. The v1.1 guide (`user_guide_v1.1.html`) was not fetched.
- https://dl.espressif.com/dl/schematics/esp32-c6-devkitc-1-schematics_v1.2.pdf, `_v1.3.pdf`, `_v1.4.pdf` → `hardware/schematic-v1.{2,3,4}.pdf` (CP2102N, SGM2212-3.3, WS2812B read from the text layer)
- https://dl.espressif.com/dl/schematics/esp32-c6-devkitc-1-pcb-layout_v1.2.pdf → `hardware/pcb-layout-v1.2.pdf`
- https://dl.espressif.com/dl/schematics/esp32-c6-devkitc-1-dimensions_v1.2.pdf → `hardware/dimensions-v1.2.pdf` (the `.dxf` was not fetched)
- https://www.espressif.com/sites/default/files/documentation/esp32-c6-wroom-1_wroom-1u_datasheet_en.pdf → `datasheets/esp32-c6-wroom-1_wroom-1u_datasheet_en.pdf`
- https://github.com/pioarduino/platform-espressif32 @ `2959e98a2750832bca32fd2f849c0c274a4cdd63`: `boards/esp32-c6-devkitc-1.json` → `reference/platformio-board.json`. The upstream `platformio/platform-espressif32` @ `1152c8f69146ca0c20ab772264606b3cc61ec67c` version (espidf only) was read for comparison, not copied.
- https://github.com/espressif/arduino-esp32 @ `e518da106ae3d7a96870feb2fca7d9dabb2b2c66`: `variants/esp32c6/pins_arduino.h` → `reference/arduino-esp32-pins_arduino.h`
- Build test: `wollkind/pio-blink` `platformio.ini`, with `platform` pointed at https://github.com/pioarduino/platform-espressif32/releases/download/55.03.311/platform-espressif32.zip, `pio run -e esp32-c6` on 2026-09-23 → SUCCESS.
