# Sources (fetched 2026-09-21, extended 2026-09-22)

- Wiki: https://wiki.seeedstudio.com/xiao_esp32s3_getting_started/ → `wiki/getting-started.md`
- Base `https://files.seeedstudio.com/wiki/SeeedStudio-XIAO-ESP32S3/`:
  - `res/XIAO_ESP32S3_Plus_V1.1_SCH_260115.pdf` → `hardware/plus-schematic-v1.1.pdf`
  - `res/XIAO_ESP32S3_Plus_V1.1_KiCad_260115.zip` → `hardware/plus-kicad-v1.1.zip`
  - `res/Seeed_Studio_XIAO_ESP32S3_Plus_Pinout.xlsx` → `hardware/plus-pinout.xlsx`
  - `res/TOP.dxf`, `res/BOTTOM.dxf` → `hardware/plus-top.dxf`, `plus-bottom.dxf`
  - `new-res/202003751_XIAO ESP32S3_v1.4_SCH_260226.pdf.pdf` → `hardware/xiao-esp32s3-schematic-v1.4.pdf`
  - `new-res/202003753_XIAO ESP32S3 Sense_v1.5_SCH_260226.pdf.pdf`: the server returns a byte-identical copy of the plain-S3 v1.4 PDF (same sha256). **Re-checked 2026-09-22 with the file host reachable and the result is the same, so this is Seeed's mistake, not a fetch problem.**
  - `new-res/202003753_XIAO ESP32S3 Sense_v1.5_SCH&PCB_260226.zip` → `hardware/sense-v1.5-sch-pcb.zip` (fetched 2026-09-22). This archive **does** hold the Sense design: `03 XIAO ESP32-S3-Sense.kicad_sch` carries the camera, PDM and LED nets that the entry's Sense pin table now comes from, along with the PCB and a block diagram.
  - `res/XIAO_ESP32S3_Sense_Pinout.xlsx` → `hardware/sense-pinout.xlsx`
  - `res/XIAO_ESP32S3_v1.1_Dimensioning.dxf` → `hardware/dimensions-v1.1.dxf`
- arduino-esp32 @ `96b3d0ef8de2b6a90d36fd84f06d4acbfea091dd`: `variants/XIAO_ESP32S3_Plus/pins_arduino.h`, `variants/XIAO_ESP32S3/pins_arduino.h` → `reference/`
- PlatformIO board JSON: `seeed_xiao_esp32_s3_plus.json` from pioarduino platform-espressif32 55.03.311 (local copy)
- Not copied: 3D models (Plus: GrabCAD login only; S3/Sense: `res/seeed-studio-xiao-esp32s3*-3d_model.zip`), camera datasheets, factory firmware, KiCad footprint libraries, and the S3/Sense SCH&PCB zips
