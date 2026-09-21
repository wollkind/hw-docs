# Sources (fetched 2026-09-21)

- Amazon listing https://www.amazon.com/dp/B0G43FCHFX and the Elecrow wiki page https://www.elecrow.com/wiki/CrowPanel_ESP32_E-paper_4.2-inch_HMI_Display.html: **not fetched** — amazon.com and elecrow.com are blocked by the sandbox egress proxy. Identified through the vendor's GitHub repo, which mirrors the wiki's downloads.
- https://github.com/Elecrow-RD/CrowPanel-ESP32-4.2-E-paper-HMI-Display-with-400-300 @ `cb6d6b41249051890456d3a311d22925c8f26ebe`:
  - `Eagle_SCH&PCB/CrowPanel-ESP32-Display-4.2E-Inch/CrowPanel ESP32 Display-4.2(E) Inch.{pdf,sch,brd}` → `hardware/`
  - `Datasheet/SSD1683_Datasheet.pdf` → `datasheets/ssd1683.pdf`
  - `Datasheet/esp32-s3-wroom-1_wroom-1u_datasheet_en.pdf` → `../../chips/esp32-s3/esp32-s3-wroom-1_datasheet_en.pdf`
  - `3D file/CrowPanel ESP32 4.2” E-paper HMI Display.stp` → `hardware/3d-model.stp.gz`
  - `example/arduino/Examples/4.2_{PWR,key,TF,GPIO}/*.ino` and `4.2_PWR/{EPD_SPI.h,EPD.h}` → `reference/`
  - `readme.md` → `wiki/elecrow-repo-readme.md`
- Not copied: `factory_firmware/` (31 MB), `factory_sourecode/` (6.1 MB), the bundled `EPD` Arduino library and the BLE/WiFi demo sketches, product photos.
- `wollkind/pio-crowpanel2` (cloned) was checked for "Used by": it is the 2.13" board (122×250, `EPD_W/EPD_H` and the workspace file name), so it is credited to that entry instead.
