# Sources (fetched 2026-09-21, extended 2026-09-22)

- Product (Pre-Soldered): https://www.seeedstudio.com/Seeed-Studio-XIAO-nRF52840-Sense-Pre-Soldered-p-6330.html
- Wiki: https://wiki.seeedstudio.com/XIAO_BLE/ → `wiki/getting-started.md`
- Base `https://files.seeedstudio.com/wiki/XIAO-BLE/`:
  - `Seeed_Studio_XIAO_nRF52840_PDF.pdf` → `hardware/sense-schematic.pdf`
  - `Seeed-Studio-XIAO-nRF52840V1.1-KiCad-Project-260105.zip` → `hardware/sense-kicad-v1.1.zip`
  - `XIAO-nRF52840-Senese-pinout_sheet.xlsx` → `hardware/sense-pinout.xlsx`
  - `XIAO-nRF52840-Sense-DXF.zip`, `Bottom-pad-positioning.zip`, `seeed-studio-xiao-nrf52840-3d-model.zip` → `hardware/`
  - `Res/260828_XIAO_nRF52840.pdf` → `hardware/non-sense-schematic.pdf`
  - `BQ25101.pdf`, `ST_LSM6DS3TR_Datasheet.pdf`, `mic_WMM7035DTTJ0_Datasheet.pdf.pdf`, `Seeed_XIAO_BLE_nRF52840_BLE_Communication_Distance_Test_Report.pdf` → `datasheets/`
  - `Seeed_XIAO_nRF52840_Sense_bootloader-0.6.1_s140_7.3.0.hex` → `firmware/`
  - `nRF52840_PS_v1.5.pdf` → `../../chips/nrf52840/nrf52840-product-spec-v1.5.pdf`
- https://files.seeedstudio.com/wiki/github_weiruanexample/Flash_P25Q16H-UXH-IR_Datasheet.pdf → `datasheets/flash-p25q16h.pdf`
- https://github.com/Seeed-Studio/Adafruit_nRF52_Arduino @ `667f05fdaafd01a05d8027d7dbbf1f4e0b137047`: `variants/Seeed_XIAO_nRF52840_Sense/variant.{h,cpp}` → `reference/`
- Not copied: the Plus-variant KiCad/schematics, the XIAO KiCad libraries, the non-Sense KiCad
- https://github.com/Seeed-Studio/Seeed_Arduino_LSM6DS3 @ `4ceed57ef83bfa6213659fc4377612af6e38002f`: the XIAO examples (`Pedometer`, `FreeFallDetect`, `IMU_Classifier`) all construct `LSM6DS3(I2C_MODE, 0x6A)` while the library's own default is 0x6B. Together with the datasheet's SA0 table this settles the IMU address at 0x6A.
- Failed: Nordic's current nRF52840 PS. `docs.nordicsemi.com`, `infocenter.nordicsemi.com` and `docs-be.nordicsemi.com` all answer **403** to a scripted request, with a browser user agent too; re-checked 2026-09-22 at the Full access level. `chips/nrf52840/` therefore still holds Seeed's copy of v1.5. A browser download is the only route.
