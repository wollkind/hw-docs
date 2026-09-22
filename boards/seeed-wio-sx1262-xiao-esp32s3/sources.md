# Sources (fetched 2026-09-21)

- Product page https://www.seeedstudio.com/Wio-SX1262-with-XIAO-ESP32S3-p-5982.html and wiki https://wiki.seeedstudio.com/wio_sx1262_with_xiao_esp32s3_kit/: not fetched (hosts blocked by the sandbox proxy).
- Wiki source: https://github.com/Seeed-Studio/wiki-documents @ `87c89463a3c36a1e0f70d6ebd00b60e667dfd1de`, branch `docusaurus-version`:
  - `sites/en/docs/Network/LoRa_Wio_Series/Wio_SX1262/Wio_SX1262_with_XIAO_ESP32S3_Kit/{Introduction,Get_Started_meshtastic,LoRaWAN_Sensor_Node,Single_Channel_LoRaWAN_Gateway}.md` → `wiki/`
  - `sites/en/docs/Network/LoRa_Wio_Series/Wio_SX1262/Introduction.md` → `wiki/wio-sx1262-module-introduction.md`
- https://github.com/meshtastic/firmware @ `bf2ef8f2d63b8c2f1831ceccaf91b1d5ab7def6c`: `variants/esp32s3/seeed_xiao_s3/{variant.h,platformio.ini,pins_arduino.h}` → `reference/`. The pin table and radio settings in `README.md` come from this variant; Seeed's own pin map is only published as an image on the blocked `files.seeedstudio.com`.
- Missing, all on `files.seeedstudio.com`:
  - `products/SenseCAP/Wio_SX1262/Wio-SX1262_Module_Datasheet.pdf`
  - `products/SenseCAP/Wio_SX1262/Wio-SX1262-N_Module_Datasheet.pdf`
  - `products/SenseCAP/Wio_SX1262/Schematic_Diagram_Wio-SX1262_for_XIAO.pdf`
  - `products/SenseCAP/Wio_SX1262/Wio-SX1262_for_XIAO_3D_file.step`
- The header-board (non-kit) pin numbers mentioned as a gotcha come from community reports in meshtastic/firmware issues, not from a vendor document, and are marked unverified.
