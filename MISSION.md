# hw-docs mission + work queue

**Read this first when resuming.** It is self-contained: a Claude Code session in a cloud sandbox (repo only, no local machine, no `~/.claude/skills`) has everything it needs here.

## Mission

Build a local, git-tracked reference library of every board, chip and part the owner (GitHub `wollkind`) has, so a spec never has to be looked up again. Each entry holds:

- the vendor's docs converted to markdown
- the files: schematics, datasheets, dimensions, 3D models, small firmware
- a **distilled README**: specs, pinout, a working config, gotchas

Done means: every item in the queue below has an entry, it's in the index in `README.md`, and it's committed and pushed.

## Environment

- Repo: `wollkind/hw-docs` (private). The local checkout is `~/Documents/hw-docs`.
- Fetch tools (in `tools/`) are Python scripts with inline deps:
  - With uv: `uv run tools/fetch_page.py …`
  - Without uv: `pip install beautifulsoup4 html5lib markdownify requests openpyxl pypdf`, then `python tools/fetch_page.py …`
- The owner's PlatformIO projects are separate private repos, `wollkind/pio-<name>`, plus `wollkind/infopanel64` and `wollkind/info-orbs`. Locally they're in `~/Documents/PlatformIO/Projects/<name>`. In a sandbox, use `gh repo clone` or `gh api` to grep them for "Used by" and for lessons learned. Their `README.md`/`CLAUDE.md` often hold hard-won hardware facts.
- Style for the owner: terse reports, no padding. Don't ask about mechanical decisions.

## Workflow per item (this is the `hw-docs` skill)

### 0. Already there?

Check `boards/`, `chips/`, `parts/` and the index. If the entry exists, refresh it rather than duplicating it.

### 1. Identify exactly

- Pin down vendor, model, **revision** and SKU. Amazon links are resellers, so find the real maker and its wiki (Amazon pages can be read with WebFetch).
- If there are variants (flash/PSRAM, V1/V2, chip), record all of them and how to tell them apart. Don't guess.
- Pick the folder (lowercase-hyphenated names):
  - `boards/<vendor>-<model>` for dev boards, modules, carriers and dev kits with displays
  - `chips/<family>` for MCUs/SoCs, stored once and shared
  - `parts/<part>` for sensors, bare displays, power modules, ICs

### 2. Fetch

```sh
uv run tools/fetch_page.py <url> <entry>/wiki/<page>.md    # page → markdown + images in wiki/img/, prints JSON of file/page links
uv run tools/fetch_file.py <url> <entry>/hardware/schematic.pdf   # refuses HTML posing as PDF/ZIP; FAILED on 4xx
```

- Crawl the product's own sub-pages (overview, pinout, resources, FAQ, Arduino/IDF setup). Skip generic tutorials.
- Get these if they exist:
  - schematic
  - dimensions (DXF/PDF)
  - datasheet for the board and for each distinct onboard IC (`datasheets/`)
  - STEP model (zip it if it's big)
  - KiCad/Eagle files
  - factory firmware under 5 MB (`firmware/`)
- Chips: use the manufacturer's URL (espressif.com, microchip.com, st.com, raspberrypi.com). Nordic's docs site returns 403 to scripts, so use a vendor copy and note it.
- GitHub: record the repo and the commit SHA (`gh api repos/O/R/commits/HEAD --jq .sha`). Copy only small useful files (pin headers, BSP config, `sdkconfig.defaults`, variant files), taken from `raw.githubusercontent.com/O/R/<sha>/...`. Never fork, and never vendor whole repos.
- Unzip vendor zips, including nested ones. Rename files to short lowercase names and keep the originals in `sources.md`.
- Skip files over 20 MB unless they're irreplaceable. Log skips in `sources.md`.

### 3. Distill `<entry>/README.md`

Use `boards/waveshare-esp32-s3-rgb-matrix/README.md` as the model:

1. **Title and one line:** what it is, a link to its chip entry, and "Used by" projects.
2. **Key specs** table: MCU, memory, radio, USB type, power, onboard ICs with I2C addresses.
3. **Pinout** tables: cite the source file for each. Board revisions get separate columns. Where sources conflict, show both.
4. **PlatformIO/Arduino config:** say "verified in <project>" only if a project actually uses it. Otherwise "from vendor docs, untested".
5. **Gotchas:** FAQ items, strapping/flash/PSRAM pin conflicts (cross-check the chip datasheet), UARTs that are taken, power limits, and project lessons.
6. **Files** list.

Also write `sources.md`: every URL, the fetch date, SHAs, and anything skipped or failed.

**Every fact must come from a fetched source or a project file. Mark anything else `(unverified)`. A wrong pin number costs more than a missing one.**

### 4. File it

- Add a row to the index table in `README.md`.
- Link the board from its chip README.
- Make one commit per entry and push.
- Report tersely: the path, what was fetched, what's missing, and open questions.

## Queue (as of 2026-09-21)

Identified products are marked ✔. Work top to bottom.

| # | Item as given | Identified as | Likely folder | Notes |
|---|---|---|---|---|
| 1 | https://lilygo.cc/products/lora3 | LilyGO LoRa32 (T3) (unverified). Check the page for the exact version (V1.6.1 / T3S3?) and radio (SX1276/SX1262, band) | `boards/lilygo-…` | LilyGO GitHub has the schematics and pin maps |
| 2 | Seeed Studio XIAO nRF54LM20A Sense | name only. Search wiki.seeedstudio.com | `boards/seeed-xiao-nrf54lm20a-sense` + `chips/nrf54lm20` | new Nordic part. Zephyr/NCS, not Arduino |
| 3 | HiLetgo 1.28" TFT, GC9A01 240×240 round, 3.3 V 4-wire SPI (round PCB) | generic GC9A01 round module | `parts/gc9a01-1.28in-round-lcd` | no vendor wiki. Get the GC9A01 datasheet, module pin labels and library init (TFT_eSPI / Adafruit_GC9A01A) |
| 4 | https://www.amazon.com/dp/B0D9H3Z637 | ✔ SK-120 120 W buck-boost converter, CC/CV, 6–36 V in → 0–36 V out, colour display | `parts/sk-120-buck-boost` | find the manufacturer manual. Some units have a Modbus/TTL port |
| 5 | https://www.adafruit.com/product/5650 | not yet looked up | | Adafruit: learn guide + GitHub PCB repo |
| 6 | https://www.adafruit.com/product/5691 | not yet looked up | | as above |
| 7 | https://www.amazon.com/dp/B0G43FCHFX | ✔ Elecrow CrowPanel ESP32 E-Paper HMI 4.2" (400×300, B/W, SPI) | `boards/elecrow-crowpanel-epaper-4.2` | Elecrow wiki. The owner has a project `pio-crowpanel2` (check which CrowPanel it targets) |
| 8 | https://www.amazon.com/dp/B0GGF7C46X | ✔ AITRIP 2.8" ESP32-S3 touch module, 240×320 IPS, capacitive | `boards/…` | reseller: identify the real board (likely a "CYD"-style ESP32-S3 2.8" clone) from photos/pinout before naming the folder |
| 9 | https://www.amazon.com/dp/B0FX4PZZMQ | ✔ Elecrow CrowPanel ESP32 E-Paper HMI 2.13" (122×250, B/W, SPI), without case | `boards/elecrow-crowpanel-epaper-2.13` | Elecrow wiki |
| 10 | https://www.amazon.com/dp/B0GF23YC3Y | ✔ Waveshare ESP32-S3-RLCD-4.2 (4.2" reflective LCD, 300×400) | `boards/waveshare-esp32-s3-rlcd-4.2` | wiki at https://docs.waveshare.com/ESP32-S3-RLCD-4.2. The owner has a project `pio-rlcd` |
| 11 | https://www.seeedstudio.com/XIAO-PowerBread-p-6318.html | XIAO PowerBread | `boards/seeed-xiao-powerbread` | Seeed wiki |
| 12 | https://www.seeedstudio.com/Seeeduino-XIAO-Expansion-board-p-4746.html | XIAO Expansion Board | `boards/seeed-xiao-expansion-board` | Seeed wiki |
| 13 | https://www.seeedstudio.com/XIAO-LOG-p-6341.html | XIAO LOG | `boards/seeed-xiao-log` | Seeed wiki |
| 14 | https://www.seeedstudio.com/Wio-SX1262-with-XIAO-ESP32S3-p-5982.html | Wio-SX1262 + XIAO ESP32-S3 kit | `boards/seeed-wio-sx1262-xiao-esp32s3` | fits the XIAO B2B connector. Link to `boards/seeed-xiao-esp32s3` |

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

## Open issues

- **Push to GitHub has been failing** from the owner's machine: "Connection reset by peer" / `pack-objects died of signal 15` on a large pack. As of this writing, local `main` is ahead of `origin/main` by several commits. If you're in a sandbox and these entries are missing, they're only on the local disk. Try `git push` again; if the big pack keeps failing, push one commit at a time (`git push origin <sha>:refs/heads/main`), or try HTTPS instead of SSH.
- **Missing source:** the nRF52840 PS in `chips/nrf52840` is v1.5 (Seeed's copy). The current Nordic PS needs a browser download.
- **Missing source:** there's no separate XIAO ESP32-S3 Sense schematic. Seeed's URL serves the v1.4 base file.
- **Unverified:** the XIAO nRF52840 Sense IMU address 0x6A is unconfirmed against the schematic.
- **Tool limitation:** `fetch_page.py` gets server-rendered HTML only. JS-only pages (some store pages) come back nearly empty, so use the vendor wiki instead.
