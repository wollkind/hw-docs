# Sources (fetched 2026-09-21)

- Amazon listing https://www.amazon.com/dp/B0FX4PZZMQ and the Elecrow wiki: not fetched — both hosts are blocked by the sandbox egress proxy.
- https://github.com/Elecrow-RD/CrowPanel-ESP32-2.13-E-paper-HMI-Display-with-122-250 @ `adf27048da2482b4ba4aa3514a6cd085ea4cb9b5`:
  - `Eagle_SCH&PCB/CrowPanel_ESP32_Display-2.13(E)_Inch.pdf` → `hardware/schematic.pdf`; `CrowPanel ESP32 Display-2.13(E) Inch(1).{sch,brd}` → `hardware/`
  - `Datasheet/SSD1680_Datasheet (1).pdf` → `datasheets/ssd1680.pdf`
  - `3D file/00-2-13_view_asm.rar` → `hardware/3d-model.rar`
  - `example/arduino/Example Code/2.13_key/{2.13_key.ino,spi.h,EPD_Init.h}` and `2.13_partial_refresh/2.13_partial_refresh.ino` → `reference/`
  - `readme.md` → `wiki/elecrow-repo-readme.md`
- Not copied: `Datasheet/EK79029DS-JD79661_Datasheet.pdf` (19 MB — the alternate driver IC; fetch it from the repo if a board turns out to carry the JD79661), `Datasheet/esp32-s3_datasheet.pdf` (already in `chips/esp32-s3`), `factory_firmware/`, `factory_soucecode/`, the `arduino-v1.2` firmware tree and the bundled `EPD` library.
- `wollkind/pio-crowpanel2` @ HEAD of `main` (shallow clone): confirmed it targets this board — `EPD_Init.h` has 122×250, `src/spi.h` has the pin set above, `main.cpp` drives GPIO7 for panel power, and the workspace file is named for the 2.13" repo.
