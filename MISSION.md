# hw-docs mission + work queue

**Read this first when resuming.** It and `.claude/skills/hw-docs/SKILL.md` together are self-contained: a Claude Code session in a cloud sandbox (repo only) has everything it needs.

## Mission

Build a local, git-tracked reference library of every board, chip and part the owner (GitHub `wollkind`) has, so a spec never has to be looked up again. Each entry holds:

- the vendor's docs converted to markdown
- the files: schematics, datasheets, dimensions, 3D models, small firmware
- a **distilled README**: specs, pinout, a working config, operational notes, applications

Done means: every item in the queue below has an entry, it's in the index in `README.md`, and it's committed.

## Environment

- Repo: `wollkind/hw-docs` (private). The local checkout is `~/Documents/hw-docs`.
- Fetch tools (in `tools/`) are Python scripts with inline deps:
  - With uv: `uv run tools/fetch_page.py …`
  - Without uv: `pip install beautifulsoup4 html5lib markdownify requests openpyxl pypdf`, then `python tools/fetch_page.py …`
- The owner's PlatformIO projects are separate private repos, `wollkind/pio-<name>`, plus `wollkind/infopanel64` and `wollkind/info-orbs`. Locally they're in `~/Documents/PlatformIO/Projects/<name>`. In a sandbox, use `gh repo clone` or `gh api` to grep them for "Used by" and for lessons learned. Their `README.md`/`CLAUDE.md` often record hardware facts established by testing.
- Style for the owner: terse reports, no padding. Don't ask about mechanical decisions.

## Workflow per item

Follow **`.claude/skills/hw-docs/SKILL.md`**. It's the `hw-docs` skill, which Claude Code loads automatically in this repo (`/hw-docs <item>`). It covers identifying the item, fetching, distilling the README, `sources.md`, and filing the entry. The one rule that matters most: every fact must come from a fetched source or a project file, and anything else is marked `(unverified)`.

## Queue

The 14 numbered items from 2026-09-21 are all filed (see Done). Item 8 is filed as a **provisional** entry only — the reseller board could not be identified; see Open issues.

Next, the **bulk pass:**

- Document every board used across the owner's PlatformIO projects. Distinct `board =` IDs: seeed_xiao_esp32c6 ×9, d1_mini ×6, featheresp32-s2 ×5, feather32u4 ×4, esp32dev ×3, esp32-s3-devkitc-1 ×3, adafruit_qualia_s3_rgb666 ×3, uno, leonardo, huzzah, adafruit_matrix_portal_m4 (done), rymcu-esp32-s3-devkitc-1, rpipico2w, rpipico2, pico, metro, esp32-s3-devkitc1-n8r8/-n16r8, esp32-c6-devkitc-1, esp32-c3-devkitc-02, blackpill_f103c8, adafruit_feather_esp32s3, adafruit_feather_esp32s2.
- Generic IDs often hide the real vendor hardware (e.g. `infopanel64` is `esp32-s3-devkitc-1` but really the Waveshare RGB Matrix). Read each project's README/comments.
- Parts from `lib_deps`: BME280, BME680, LIS3DH, CCS811, DHT, MAX1704X, INA228, INMP441 mic, ST7789 240×240, e-paper panels and so on.
- Local-only vendor downloads that are **not** in any repo: `Documents/PlatformIO/E-Paper_code` (Waveshare e-paper demo, 164 MB) and `Documents/PlatformIO/ESP32-C6-Touch-LCD-1.47-Demo` (56 MB). The ESP32-C6-Touch-LCD-1.47 is owned hardware and should get an entry.

## Done

| Entry | Notes |
|---|---|
| `boards/waveshare-esp32-s3-rgb-matrix` | used by infopanel64 |
| `boards/seengreat-rgb-matrix-adapter-e` | V1.x/V2.x pin maps |
| `boards/seeed-xiao-esp32s3` | S3 / Sense / Plus. The Plus pin map comes from the arduino-esp32 variant |
| `boards/seeed-xiao-1.14in-display-esp32s3` | |
| `boards/seeed-xiao-nrf52840-sense` | |
| `boards/adafruit-matrix-portal-m4` | used by sandpanel |
| `parts/waveshare-1.69in-lcd-module` | Seeed SKU 5755 |
| `chips/esp32-s3`, `chips/nrf52840`, `chips/atsamd51` | |
| `boards/adafruit-feather-esp32-s2` | bulk pass: used by pio-bme280, pio-bme680, pio-feather |
| `boards/adafruit-feather-32u4-rfm69` | bulk pass: used by pio-radio, pio-radio1, pio-radio2 (915 MHz RFM69) |
| `boards/seeed-xiao-esp32c6` | bulk pass: used by pio-solar, pio-soil1, pio-strip-com, pio-xiao-hdc-wifi |
| `boards/aitrip-esp32-s3-2.8in-touch-lcd` | **provisional** — reseller board not identified, no pin map |
| `boards/seeed-xiao-log` | no Seeed wiki; schematics V1–V3 and MicroPython from the potblitd repo |
| `boards/seeed-xiao-powerbread` | no Seeed wiki; schematic, datasheets and firmware from the nicho810 repo |
| `boards/seeed-wio-sx1262-xiao-esp32s3` | pins from the Meshtastic variant; Seeed schematic/datasheet still missing |
| `boards/seeed-xiao-expansion-board` | wiki page only; schematic and part datasheets still missing |
| `boards/waveshare-esp32-s3-rlcd-4.2` | used by `pio-rlcd`; pins from the vendor repo, schematic still missing |
| `boards/elecrow-crowpanel-epaper-2.13` | used by `pio-crowpanel2`; vendor repo schematic + examples |
| `boards/elecrow-crowpanel-epaper-4.2` | vendor GitHub repo: schematic, SSD1683 datasheet, STEP, examples |
| `boards/adafruit-esp32-s3-reverse-tft-feather` | PID 5691; EAGLE + pinout PDFs + all three board definitions |
| `boards/adafruit-feather-rp2040-scorpio` | PID 5650; EAGLE schematic + CircuitPython/arduino-pico pin maps |
| `parts/sk-120-buck-boost` | XY-SK120; vendor Modbus PDFs via a community GitHub repo; electrical specs still unsourced |
| `parts/gc9a01-1.28in-round-lcd` | GC9A01A datasheet + TFT_eSPI/Adafruit init; module pin labels unverified |
| `boards/seeed-xiao-nrf54lm20a-sense`, `chips/nrf54lm20a` | wiki source from GitHub; schematic and Nordic datasheet still missing |
| `boards/lilygo-t3-lora32-v1.6.1` | T3 LoRa32 V1.6.1, SX1276/SX1278; sources from the LilyGO GitHub repo |

## Open issues

- **Found in the bulk pass:** the projects that target `board = featheresp32-s2` are building the **no-PSRAM** profile (`-DARDUINO_ADAFRUIT_FEATHER_ESP32S2_NOPSRAM`). If the hardware is a PID 5000/5303 Feather, `board = adafruit_feather_esp32s2` is the profile that enables its 2 MB PSRAM.
- **Found in the bulk pass:** `pio-radio2` builds with `board = leonardo` in an env named `feather32u4`; the hardware is a Feather 32u4 RFM69. Harmless but wrong profile.
- **Found in the bulk pass:** `pio-strip-com`'s `display` env is `board = esp32-s3-devkitc-1` but is really a **SmartPanle PanelLan `BOARD_SC05_X`** (320×240 IPS + touch, 16 MB flash, OPI PSRAM, `smartpanle/PanelLan` library). It needs its own entry. That project also pins `platform = file://C:/Users/steve/pio-esp32-55.03.311`, a local fork that will not resolve on another machine.
- **Missing source:** no `chips/esp32-c6` entry — the Espressif datasheet is only on blocked hosts.
- **Blocked — item 8:** the AITRIP 2.8" ESP32-S3 touch module has no identifiable vendor design. Amazon is blocked from the sandbox and the listing text (ST7789P3 + FT6336U + ESP32-S3-R2 + RS485) matches several white-label sellers, none with documentation. Needs a photo of the board silkscreen to get a model code; the entry records what is known and deliberately records no pin map.

- **Sandbox egress:** vendor sites (lilygo.cc, wiki.seeedstudio.com, docs.waveshare.com, adafruit.com, espressif.com, semtech.com) are blocked by the proxy. GitHub (including raw and clones of public vendor repos) and web search work, so vendor GitHub repos are the way in.
- **Missing source:** ESP32-S3-RLCD-4.2 schematic, dimensions and the ST7305 datasheet — only on the blocked Waveshare wiki.
- **Missing source:** no `chips/rp2040` entry — datasheets.raspberrypi.com is blocked by the proxy. Adafruit Learn guides are unreachable too (adafruit.com, cdn-learn.adafruit.com), so Adafruit entries rest on the PCB repos and board definitions.
- **Missing source:** XY-SK120 electrical specs and front-panel manual. The user guides live on telemetry2u.com / manuals.plus / done.land, all blocked by the proxy; and which variant (SK120/SK120X/SK120D) the owner has is unconfirmed.
- **Unverified:** the GC9A01 module's pin labels and pin order (7- vs 8-pin build) — needs a photo of the owner's board.
- **Missing source:** XIAO nRF54LM20A Sense schematic, KiCad project and the Nordic nRF54LM20A datasheet: all three live on `files.seeedstudio.com`, which the proxy blocks. Need a browser download.
- **Missing source:** no `chips/esp32` entry for the ESP32-PICO-D4 on the T3 LoRa32, and no SX1276/SX1278 datasheet: espressif.com and semtech.com are unreachable.
- **Missing source:** the nRF52840 PS in `chips/nrf52840` is v1.5 (Seeed's copy). The current Nordic PS needs a browser download.
- **Missing source:** there's no separate XIAO ESP32-S3 Sense schematic. Seeed's URL serves the v1.4 base file.
- **Unverified:** the XIAO nRF52840 Sense IMU address 0x6A is unconfirmed against the schematic.
- **Tool limitation:** `fetch_page.py` gets server-rendered HTML only. JS-only pages (some store pages) come back nearly empty, so use the vendor wiki instead.
