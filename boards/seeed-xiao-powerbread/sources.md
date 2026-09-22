# Sources (fetched 2026-09-21)

- Seeed product page https://www.seeedstudio.com/XIAO-PowerBread-p-6318.html: not fetched (host blocked by the sandbox proxy). There is **no Seeed wiki page** for this product — it is a Co-create design, documented in its own repository.
- https://github.com/nicho810/XIAO-PowerBread @ `3afe24ab210a4351a6de0cc3e82156717b43c6d2`:
  - `PCB/v1.2/{Schematic_v1.2.pdf,PCB_v1.2.pdf}` → `hardware/`
  - `Datasheet/INA3221/ina3221.pdf`, `Datasheet/LCD/ST7735S芯片手册.pdf`, `Datasheet/LCD/ZJY096T-IG11.pdf`, `Datasheet/tps54202.pdf`, `Datasheet/MT9700_C89855_PowerSwitch.PDF` → `datasheets/` (renamed to ASCII)
  - `Firmware/XPB-Firmware-PlatformIO/lib/boardConfig/boardConfig.h`, `platformio.ini` → `reference/`
  - `README.md` → `wiki/powerbread-repo-readme.md`; `Docs/sysConfig.md` → `wiki/`
- Not copied: `Firmware/Release firmware/` and the archived Arduino firmware zip, `Datasheet/INA3221/ina3221 design reference from 3rd party.pdf`, `Datasheet/Seeed-Studio-XIAO-RP2040-v1.3.pdf` (XIAO RP2040 schematic — belongs with a XIAO RP2040 entry, which does not exist yet), `Docs/Images` and `Docs/Videos`.
- The INA3221 address 0x40 is the default in the project's `INA3221Sensor` constructor; the schematic PDF was not parsed to confirm the address strap.
