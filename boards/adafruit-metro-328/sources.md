# Sources (fetched 2026-09-22)

- `adafruit/Adafruit-METRO-328-PCB` @ `1d635d70533c446c925ec77240370cfee4fba7ad`:
  - `Metro THM+LDO Rev C - CP2104.pdf` → `hardware/schematic-revc-cp2104.pdf`
  - `Metro THM+LDO Rev C - CP2104.sch` / `.brd` → `hardware/eagle-revc-cp2104.sch` / `.brd`
  - `Adafruit Metro 328P Pinout.pdf` → `hardware/pinout.pdf`
  - `README.md` → `reference/pcb-repo-readme.md` — Adafruit's board description, which is where every figure in the specs table comes from
- https://raw.githubusercontent.com/platformio/platform-atmelavr/develop/boards/metro.json → `reference/platformio-metro.json`. `platformio/platform-atmelavr` `develop` @ `5da4930a978700ecc9bffcf56c5fbeb930c25611`.
- https://www.adafruit.com/product/2466 — the product page; used only to find the PCB repository.

**No Learn guide.** Adafruit has no `learn.adafruit.com` guide for the METRO 328 (the slugs `adafruit-metro-328`, `adafruit-metro-328-arduino-compatible` and `metro-328` all 404); the product page links its Arduino lessons instead. The PCB repository is the documentation.

Not copied: the Metro Mini designs in the same repository (Rev A, Rev B, and V2 with STEMMA QT) and the earlier `Metro THM+LDO Rev B` files.

Project files: `wollkind/pio-bme280` `platformio.ini` (`[env:metro]`).
