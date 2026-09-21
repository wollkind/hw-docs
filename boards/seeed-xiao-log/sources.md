# Sources (fetched 2026-09-21)

- Seeed product page https://www.seeedstudio.com/XIAO-LOG-p-6341.html: not fetched (host blocked by the sandbox proxy). There is **no Seeed wiki page** for this product — like the PowerBread it is a Co-create design documented in its own repository.
- https://github.com/potblitd/XIAO-log @ `65fb9697902753aef448fe4177f8c38bb4357db3`:
  - `hardware/V3/{XIAO-HAT-3 schematics.PDF,XIAO-HAT-3 layout.PDF,2024-09 XIAO-HAT-3.zip}` → `hardware/` (renamed)
  - `hardware/V2/XIAO-log^2-2 Schematics.pdf`, `hardware/V1/XIAO-log^2 schematics.pdf` → `hardware/`
  - `code/{xiaohat.py,set_rtc.py,esphome-xiaohat.yaml}` → `reference/`
  - `README.md` → `wiki/xiao-log-repo-readme.md`
- Not copied: the Altium `.PcbDoc`/`.SchDoc` sources for V1 and V2, the `archive/` tree, product images.
- I2C addresses (SHT40 0x44, BH1750 0x23, PCF8563 0x51) come from `code/xiaohat.py`; the V3 schematic confirms the parts, the D10 power gate, the 32.768 kHz crystal and the 100 k/100 k battery divider.
- Missing: datasheets for SHT40, BH1750FVI and PCF8563 — not in the repo, and sensirion.com / rohm.com / nxp.com were not reachable in this sandbox's earlier vendor-domain checks.
