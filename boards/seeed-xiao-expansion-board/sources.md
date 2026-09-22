# Sources (fetched 2026-09-21)

- Product page https://www.seeedstudio.com/Seeeduino-XIAO-Expansion-board-p-4746.html and wiki https://wiki.seeedstudio.com/Seeeduino-XIAO-Expansion-Board/: not fetched (both hosts blocked by the sandbox proxy).
- Wiki source: https://github.com/Seeed-Studio/wiki-documents @ `87c89463a3c36a1e0f70d6ebd00b60e667dfd1de`, branch `docusaurus-version`, `sites/en/docs/Sensor/SeeedStudio_XIAO/SeeedStudio_XIAO_Expansion_board/Seeeduino-XIAO-Expansion-Board.md` → `wiki/`.
- Missing — every hardware document for this board is on the blocked `files.seeedstudio.com`:
  - schematic PDF: `.../Seeeduino%20XIAO%20Expansion%20board_v1.0_SCH_200824.pdf`
  - Eagle `.sch` and `.brd`: `.../Seeeduino%20XIAO%20Expansion%20board_v1.0_200824.{sch,brd}`
  - part datasheets: `ETA1038.pdf`, `ETA3410.pdf`, `ETA6003.pdf`, `PCF8563T.pdf`
  All are listed under "Resources" in the wiki page and need a browser download.
- The OLED I2C address is not stated anywhere in the wiki text; 0x3C is inferred from the U8g2 constructor the examples use and is marked unverified.
