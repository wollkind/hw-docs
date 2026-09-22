# hw-docs mission + work queue

**Read this first when resuming.** It and `.claude/skills/hw-docs/SKILL.md` together are self-contained: a Claude Code session in a cloud sandbox (repo only) has everything it needs.

## Mission

Build a local, git-tracked reference library of every board, chip and part the owner (GitHub `wollkind`) has, so a spec never has to be looked up again. Each entry holds:

- the vendor's docs converted to markdown
- the files: schematics, datasheets, dimensions, 3D models, small firmware
- a **distilled README**: specs, pinout, a working config, operational notes, applications

Done means: every item in the queue below has an entry, it's in the index in `README.md`, and it's committed.

`examples/` holds cross-board demonstrations. `examples/lora-ping-pong` builds for both LoRa boards; its protocol header is compile-checked, the sketch is not, because the PlatformIO registry was unreachable when it was written.

## Environment

- Repo: `wollkind/hw-docs` (private). The local checkout is `~/Documents/hw-docs`.
- Fetch tools (in `tools/`) are Python scripts with inline deps:
  - With uv: `uv run tools/fetch_page.py …`
  - Without uv: `pip install beautifulsoup4 html5lib markdownify requests openpyxl pypdf`, then `python tools/fetch_page.py …`
- The owner's PlatformIO projects are separate private repos, `wollkind/pio-<name>`, plus `wollkind/infopanel64` and `wollkind/info-orbs`. Locally they're in `~/Documents/PlatformIO/Projects/<name>`. In a sandbox, use `gh repo clone` or `gh api` to grep them for "Used by" and for lessons learned. Their `README.md`/`CLAUDE.md` often record hardware facts established by testing.
- Style for the owner: terse reports, no padding. Don't ask about mechanical decisions. No idioms in repository text.
- **Network access** in a cloud session is set by the environment's access level, not by anything in this repo. Levels are None, Trusted, Full and Custom, edited at claude.ai/code in the environment selector (hover the environment, settings icon). At **Trusted**, every vendor host used by this library is refused at the proxy and only GitHub, web search and package registries work. At **Full**, any domain is reachable. A change applies to new sessions only.
- **The 2026-09-22 session ran at Full**: wemos.cc, adafruit.com, cdn-learn.adafruit.com, learn.adafruit.com, espressif.com and documentation.espressif.com all answered. The "Missing source" issues below are therefore refetchable now, and the three entries filed that day take their facts from vendor pages rather than GitHub mirrors. Note that the **GitHub API** stays scoped to attached repositories even at Full — `api.github.com` returns 403 for a repo that `add_repo` has not attached, so use `raw.githubusercontent.com` (unrestricted) and `git ls-remote` for vendor repos and their commit SHAs.

## Workflow per item

Follow **`.claude/skills/hw-docs/SKILL.md`**. It's the `hw-docs` skill, which Claude Code loads automatically in this repo (`/hw-docs <item>`). It covers identifying the item, fetching, distilling the README, `sources.md`, and filing the entry. The one rule that matters most: every fact must come from a fetched source or a project file, and anything else is marked `(unverified)`.

## Queue

The 14 numbered items from 2026-09-21 are all filed (see Done). Item 8 is filed as a **provisional** entry only — the reseller board could not be identified; see Open issues.

Next, the **bulk pass:**

Every `board =` id across the owner's PlatformIO projects, and the projects that build it. The map below was read from each repo's `platformio.ini` on 2026-09-22 and is complete for the 36 repos attached that day; **filed** means the hardware has an entry here.

| `board =` | Projects | Entry |
|---|---|---|
| `seeed_xiao_esp32c6` | pio-solar, pio-soil1, pio-strip-com (`strip`), pio-xiao-hdc-wifi, pio-leddrive, pio-music1, pio-baseboard2, pio-inmp, pio-feather | filed |
| `featheresp32-s2` | pio-bme280, pio-bme680, pio-feather, pio-blink, pio-mlab | filed (see Open issues: wrong profile) |
| `feather32u4` | pio-radio, pio-radio1, pio-epapertest, pio-epdv4 | filed |
| `adafruit_matrix_portal_m4` | pio-sandpanel | filed |
| `d1_mini` | pio-d1mini, pio-d12, pio-bme280, pio-bme680, pio-feather, pio-blink | filed |
| `huzzah` | pio-huzzah, pio-radio | filed |
| `adafruit_qualia_s3_rgb666` | pio-piotest, pio-blink, pio-feather | filed |
| `esp32-s3-devkitc-1` | infopanel64 (really the Waveshare RGB Matrix, filed), pio-strip-com `display` (really the SmartPanle SC05_X, filed) | filed (the kit itself) |
| `esp32-s3-devkitc1-n16r8` | pio-rlcd (really the Waveshare ESP32-S3-RLCD-4.2, filed) | filed (the kit itself) |
| `esp32-s3-devkitc1-n8r8` | pio-crowpanel2 (really the Elecrow CrowPanel 2.13, filed) | filed (the kit itself) |
| `esp32dev` | pio-ir-decode, pio-num1-2, pio-feather | **outstanding** |
| `uno` | pio-lcd2, pio-feather | **outstanding** |
| `leonardo` | pio-lcd, pio-radio2 (see Open issues) | **outstanding** |
| `metro` | pio-bme280 | **outstanding** |
| `pico` | pio-feather | **outstanding** |
| `rpipico2` | pio-pico3 (framework = micropython) | **outstanding** |
| `rpipico2w` | pio-feather | **outstanding** |
| `rymcu-esp32-s3-devkitc-1` | pio-feather | **outstanding** |
| `adafruit_feather_esp32s3` | pio-blink | **outstanding** |
| `adafruit_feather_esp32s2` | pio-bme280 | **outstanding** |
| `esp32-c3-devkitc-02` | pio-blink | filed |
| `esp32-c6-devkitc-1` | pio-blink | filed |
| `esp32-c5-devkitc1-n4` | pio-seafive (two MCUs, `mcu_a` and `mcu_b`) | **outstanding — new, not in the earlier list** |
| `blackpill_f103c8` | pio-feather | **outstanding** |

Reading any of this in a sandbox needs `add_repo` per repository first (the GitHub API refuses unattached repos), then either a clone or `api.github.com/repos/wollkind/<repo>/contents/<path>` with `Accept: application/vnd.github.raw`.

Repos with no `platformio.ini` to read: `pio-mpy1` (MicroPython, no ini), `pio-workspace`, `pio-infopanel64` and `pio-info-orbs` (all three empty). `wollkind/info-orbs` is a public fork and was not attached.

Still to do beyond the board ids:

- Parts from `lib_deps`: BME280, BME680, LIS3DH, CCS811, DHT, MAX1704X, INA228, HDC302x, TSC2007, MPL115A2, TEMT6000, LM35, INMP441 mic, ILI9341 FeatherWing, ST7789 240×240, SSD1306, e-paper panels, ADS1115, FT6206.
- Generic IDs hide real vendor hardware — read each project's README/comments and source before trusting the id.
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
| `boards/wemos-d1-mini`, `chips/esp8266` | bulk pass: the six `d1_mini` environments. Vendor V4.0.0 + V3.1.0 pages, V4 schematic, Espressif datasheet v7.1 (NRND) |
| `boards/adafruit-feather-huzzah-esp8266` | bulk pass: `pio-huzzah`, `pio-radio`. Learn guide + Rev G EAGLE. The `huzzah` board id names PID 2471, the breakout; the Feather is the board in hand |
| `boards/adafruit-qualia-esp32-s3-rgb666` | bulk pass: `pio-piotest`, `pio-blink`, `pio-feather`. PCA9554A map, RGB-666 pin table, EAGLE design |
| `chips/esp32-c6` | datasheet v1.5, TRM and errata; closes the old "blocked host" issue |
| `boards/espressif-esp32-c6-devkitc-1` | bulk pass: `pio-blink`. Both header tables, schematic v1.4, module datasheet |
| `boards/espressif-esp32-c3-devkitc-02`, `chips/esp32-c3` | bulk pass: `pio-blink`. Guide, schematic, module datasheet; chip datasheet v2.4, TRM, errata |
| `boards/espressif-esp32-s3-devkitc-1` | bulk pass: the kit behind three board ids that four projects use as build profiles |
| `boards/smartpanle-sc05x-zx2d80ce02s` | bulk pass: `pio-strip-com` `display`. Pin map from the vendor library; **vendor datasheet still missing** |

## Open issues

### Found in the bulk pass (project problems, not documentation gaps)

- The projects that target `board = featheresp32-s2` are building the **no-PSRAM** profile (`-DARDUINO_ADAFRUIT_FEATHER_ESP32S2_NOPSRAM`). If the hardware is a PID 5000/5303 Feather, `board = adafruit_feather_esp32s2` is the profile that enables its 2 MB PSRAM. `pio-bme280` already has an `adafruit_feather_esp32s2` env beside its `featheresp32-s2` one.
- `pio-radio2` builds with `board = leonardo` in an env named `feather32u4`; the hardware is a Feather 32u4 RFM69. Harmless but wrong profile.
- `pio-inmp`'s only env is named `featheresp32-s2` but builds `board = seeed_xiao_esp32c6`. The env name is wrong, not the board id.
- `pio-d12` drives `GPIO5` as a "done" output while the same sketch uses `Wire`, whose default SCL on the `d1_mini` variant is GPIO5. Recorded in `boards/wemos-d1-mini/README.md`.
- `pio-blink`'s `qualia` env defines `-D LED_BUILTIN=18`, and GPIO18 is the Qualia's SCL. Harmless with nothing on I2C, wrong with a STEMMA device attached.
- `pio-pico3` declares `framework = micropython` for `board = rpipico2`, and that board file lists only `arduino`, `picosdk` and `mbed-ce` on the platform's current `develop`. Check it still builds.
- **`platform = file://C:/Users/steve/pio-esp32-55.03.311`** is pinned by `pio-strip-com`, `pio-blink`, `pio-mlab` and `pio-inmp`. That local fork resolves on the owner's machine only.

### Hardware still undocumented

- **`pio-seafive` builds `board = esp32-c5-devkitc1-n4`** for two MCUs (`mcu_a`, `mcu_b`) with GPS and an SSD1306. Neither the board nor `chips/esp32-c5` has an entry.
- The board ids still marked **outstanding** in the table above: `esp32dev`, `uno`, `leonardo`, `metro`, `rymcu-esp32-s3-devkitc-1`, `adafruit_feather_esp32s3`, `adafruit_feather_esp32s2`, `blackpill_f103c8`.
- Parts from `lib_deps` — see the list under the bulk pass.
- The **ESP32-C6-Touch-LCD-1.47**, owned hardware whose vendor demo is only in a local folder.

### Still missing after the 2026-09-22 refetch

- **SmartPanle SC05_X vendor datasheet.** en.wireless-tag.com renders its catalogue in JavaScript, so the product page for the WT32S3-28S PRO could not be crawled; its datasheet link would be on the `img0*.71360.com` CDN under a hashed path. A browser can get it. The same entry records a flash/PSRAM disagreement (library says 8 MB + QSPI, the project flashes 16 MB + OPI) that `esptool.py flash_id` would settle.
- **Semtech's SX1276 errata note and application notes.** semtech.com serves documents through a Salesforce JavaScript post-back that `curl` cannot follow. The datasheet itself is filed, from Adafruit's copy of Semtech's Rev 4 document.
- **Nordic's current nRF52840 product specification.** docs.nordicsemi.com, infocenter.nordicsemi.com and docs-be.nordicsemi.com all answer 403 to scripted requests, browser user agent included. `chips/nrf52840/` holds Seeed's v1.5 copy.
- **LSM6DS3TR-C datasheet from ST.** st.com drops the connection mid-transfer (`HTTP/2 stream not closed cleanly`). Seeed's copy is in `boards/seeed-xiao-nrf52840-sense/datasheets/`.
- **An XY-SK120 manufacturer specification sheet** with ripple, efficiency and tolerances, and confirmation of which variant (SK120/SK120X/SK120D) the owner has. The user manual and a community write-up are now filed.
- **Waveshare's `www.waveshare.com`** answers 403 to scripted requests (wiki and product pages alike). `docs.waveshare.com` and `files.waveshare.com` serve normally — use those.
- **Seeed's XIAO ESP32-S3 Sense schematic PDF** link still serves the plain-S3 v1.4 file. This is a vendor error, confirmed with the host reachable. The `SCH&PCB` zip does contain the Sense design and is filed.
- **The Wio-SX1262 schematic's GPIO labels** do not match the Meshtastic variant's pin numbers, and the PDF's text layer cannot settle it — read it by eye.
- **AITRIP 2.8" ESP32-S3 touch module (queue item 8):** still no identifiable vendor design. The listing text (ST7789P3 + FT6336U + ESP32-S3-R2 + RS485) matches several white-label sellers, none with documentation. Needs a photo of the board silkscreen.
- **The GC9A01 module's pin labels and pin order** (7- vs 8-pin build) — needs a photo of the owner's board.

### Tooling and environment

- **`fetch_page.py` gets server-rendered HTML only.** JS-only pages (store pages, some catalogues) come back nearly empty; use the vendor's documentation site instead.
- **`fetch_file.py` refuses HTML posing as a PDF**, which is what a JavaScript download gate returns. When it refuses, the file needs a browser.
- **PlatformIO builds need \*.platformio.org**, which the Trusted access level refuses. That is why `examples/lora-ping-pong` is unbuilt; at Full it should be buildable.
- **The GitHub API stays scoped to attached repositories** whatever the access level. Use `raw.githubusercontent.com` and `git ls-remote` for vendor repositories, and `add_repo` before reading one of the owner's.
