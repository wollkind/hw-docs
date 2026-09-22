# Sources (fetched 2026-09-21)

- Product page: https://www.seeedstudio.com/Seeed-Studio-XIAO-nRF54LM20A-Sense-p-6840.html — **not fetched** (seeedstudio.com is blocked by the sandbox egress proxy).
- Wiki pages, taken from their source repo instead of https://wiki.seeedstudio.com/xiao_nrf54lm20a_getting_started/ (blocked): GitHub https://github.com/Seeed-Studio/wiki-documents @ `87c89463a3c36a1e0f70d6ebd00b60e667dfd1de`, branch `docusaurus-version`, `sites/en/docs/Sensor/SeeedStudio_XIAO/SeeedStudio_XIAO_nRF54LM20A-Sense/*` → `wiki/` (11 pages, unmodified MDX).
- GitHub https://github.com/Seeed-Studio/platform-seeedboards @ `6a313a19f06994909627250a5e082e637bd34ff6`:
  - `boards/seeed-xiao-nrf54lm20a.json` → `reference/`
  - `examples/zephyr-tapwake/zephyr/boards/xiao_nrf54lm20a_nrf54lm20a_cpuapp.overlay` → `reference/tapwake-imu.overlay`
  - `examples/zephyr-npm1300-register-read/zephyr/boards/xiao_nrf54lm20a_nrf54lm20a_cpuapp.overlay` → `reference/npm1300.overlay`
  - `misc/svd/nrf54lm20a.svd` → `../../chips/nrf54lm20a/reference/nrf54lm20a.svd.gz` (gzipped, 4.4 MB raw)
- Missing: schematic, KiCad project and the Nordic datasheet. Seeed hosts them at
  - https://files.seeedstudio.com/wiki/XIAO_nRF54LM20A/getting_start/RES/XIAO_nRF54LM20A_Schematic.pdf
  - https://files.seeedstudio.com/wiki/XIAO_nRF54LM20A/getting_start/RES/XIAO_nRF54LM20A_V1.0_SCH&PCB_260508.zip
  - https://files.seeedstudio.com/wiki/XIAO_nRF54LM20A/getting_start/RES/nRF54LM20A_nRF54LM20B_Datasheet_v1.0.pdf
  `files.seeedstudio.com` is blocked by the proxy, so all three need a browser download.
- Missing: LSM6DS3TR-C datasheet (https://www.st.com/resource/en/datasheet/lsm6ds3tr-c.pdf, st.com not tried/blocked) and any MSM261DGT006 datasheet.
- Pin facts cross-checked between the wiki pin map, the wiki's own Zephyr overlays, and the board-DTS notes quoted in the low-power page. The A7/SDA = P1.03 collision is Seeed's, and is unresolved.
