# Sources (fetched 2026-09-21, extended 2026-09-22)

- Product page https://www.seeedstudio.com/Seeeduino-XIAO-Expansion-board-p-4746.html and wiki https://wiki.seeedstudio.com/Seeeduino-XIAO-Expansion-Board/: not fetched (both hosts blocked by the sandbox proxy).
- Wiki source: https://github.com/Seeed-Studio/wiki-documents @ `87c89463a3c36a1e0f70d6ebd00b60e667dfd1de`, branch `docusaurus-version`, `sites/en/docs/Sensor/SeeedStudio_XIAO/SeeedStudio_XIAO_Expansion_board/Seeeduino-XIAO-Expansion-Board.md` → `wiki/`.
- Fetched 2026-09-22 from `https://files.seeedstudio.com/wiki/Seeeduino-XIAO-Expansion-Board/document/`:
  - `Seeeduino XIAO Expansion board_v1.0_SCH_200824.pdf` → `hardware/schematic-v1.0.pdf`
  - `Seeeduino XIAO Expansion board_v1.0_200824.sch` / `.brd` → `hardware/eagle-v1.0.sch` / `.brd`
  - `ETA1038.pdf`, `ETA3410.pdf`, `ETA6003.pdf`, `PCF8563T.pdf` → `datasheets/`
- Not fetched: `.../lib.zip`, the wiki's bundled Arduino libraries.
- The OLED I2C address question is **settled from the schematic**: it prints "The I2C slave address is 0x78" (0x3C as 7-bit), with 0x7a/0x3D as the strap alternative, against the `IIC_ADDR` net. The PCF8563's addresses are printed there too (write 0xA2, read 0xA3 — 0x51 7-bit).
