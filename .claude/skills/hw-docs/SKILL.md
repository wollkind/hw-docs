---
name: hw-docs
description: Fetch and file the technical docs for a board, MCU, chip or part (datasheets, schematics, pinouts, vendor wiki, example code) into the local hw-docs library, writing a distilled README. Use when the user names hardware to "add to the library", "get the docs for", "document", or pastes a vendor wiki/product URL for something they own; also use to look up specs of hardware already in the library before searching the web.
argument-hint: <part / board name or vendor URL>
---

# hw-docs: build the hardware reference library

The library is this repo, `wollkind/hw-docs`. Locally it's checked out at `~/Documents/hw-docs`; in a cloud sandbox it's the working directory. Its `README.md` explains the layout and holds the index, and `MISSION.md` holds the work queue and open issues. Read both before starting.

Tools run with `uv` and need no setup. Without uv, run `pip install beautifulsoup4 html5lib markdownify requests openpyxl pypdf` once, then use `python tools/…`.

The owner's projects are needed for "Used by" and project lessons. Locally they're in `~/Documents/PlatformIO/Projects/<name>`. In a sandbox, they're private GitHub repos `wollkind/pio-<name>`, plus `wollkind/infopanel64` and `wollkind/info-orbs`: use `gh repo list wollkind` and `gh api repos/wollkind/<repo>/contents/<path>`.

## 0. Already there?

Check `boards/`, `chips/`, `parts/` and the README index first. If an entry exists, refresh it (re-fetch pages, compare the vendor repo commit in `sources.md`) rather than duplicating it.

## 1. Identify the hardware exactly

- Resolve the input to the exact product: vendor, model, **revision** and SKU. Use WebSearch if only a name was given.
- Prefer the vendor's own wiki or product page. Aggregator pages only as a fallback.
- If several variants exist (flash/PSRAM size, board rev V1/V2, chip variant), don't guess. Record all of them and note how to tell them apart (silkscreen, part-number suffix).
- Pick the folder:
  - `boards/<vendor>-<model>`: dev boards, modules and carriers
  - `chips/<family>`: MCUs/SoCs. Shared by boards and stored once.
  - `parts/<part>`: sensors, displays, panels, ICs
  - Names are lowercase-hyphenated, e.g. `boards/adafruit-matrix-portal-m4`, `parts/bme680`.

## 2. Fetch

```sh
uv run tools/fetch_page.py <url> <entry>/wiki/<page>.md    # markdown + images in <entry>/wiki/img/
uv run tools/fetch_file.py <url> <entry>/hardware/schematic.pdf
```

- `fetch_page.py` prints JSON listing the page's `files` and `pages` links. Use it to crawl the product's own sub-pages: overview, pinout, resources, FAQ, Arduino/IDF/MicroPython setup. Skip generic tutorials shared across many products.
- Get these files if they exist:
  - schematic
  - dimensions/mechanical drawing
  - datasheet for the board and for each **distinct onboard IC** (put these under `datasheets/`, or link to `parts/`/`chips/` if they're already there)
  - 3D/STEP model
  - factory firmware if small (<5 MB)
- `fetch_file.py` refuses HTML that poses as a PDF or ZIP. When it refuses, find the real link. Don't keep the file.
- For the chip, use the manufacturer's own URLs (e.g. espressif.com, st.com, microchip.com, raspberrypi.com), not vendor-rehosted copies. Get the datasheet, reference manual/TRM and errata. If `chips/<family>` doesn't exist yet, create it.
- Vendor GitHub repos: record the repo URL and the commit SHA from `gh api repos/O/R/commits/HEAD --jq .sha`. Copy only the useful small files: pin-definition headers, BSP config, `sdkconfig.defaults`, board definitions, the README. Take them from `raw.githubusercontent.com/O/R/<sha>/...` so the copy matches the recorded commit. Don't vendor whole repos or libraries, and don't fork them.
- Vendor zips: unzip into place (including nested zips). Rename files to short lowercase names and keep the original name in `sources.md`. Keep STEP models zipped.
- Skip anything over 20 MB unless it's the only copy of something important. Note what was skipped in `sources.md`.

## 3. Distill: `<entry>/README.md` (the valuable part)

Follow the shape of `boards/waveshare-esp32-s3-rgb-matrix/README.md`:

1. **Title and one line** saying what it is. Link to its chip entry. List "Used by" projects: search the owner's projects (see above) for the board ID and name.
2. **Key specs** table: MCU, flash/PSRAM, radio, USB type (native or bridge chip), power inputs and limits, onboard ICs with their I2C addresses.
3. **Pinout** tables for every bus and onboard peripheral. Take the pins from the schematic, vendor headers or the wiki's own tables, and cite the source file. When sources disagree, show both and say which is authoritative. Board revisions get separate columns.
4. **PlatformIO config** that works: `board =`, memory type, partitions, build flags. Mark it "verified in <project>" only if a project actually uses it. Otherwise say "from vendor docs, untested".
5. **Operational notes:** vendor FAQ items, strapping/flash/PSRAM pin conflicts (cross-check against the chip datasheet), UART pins that are already assigned, power limits, and findings from the user's own projects (their `README.md`/`CLAUDE.md` often record fixes established by testing).
6. **Applications:** two to four concrete uses the board's own hardware supports, each naming the onboard peripheral it depends on, plus any use the board is unsuitable for. No speculation about parts the board does not have.
7. **Files:** what's in the folder.

Put every URL, the fetch date (today), repo SHAs and anything skipped in `<entry>/sources.md`.

Every fact must come from a fetched source or the user's project files. Mark anything else `(unverified)`. Don't fill gaps from memory: a wrong pin number costs more than a missing one.

## 4. File it

- Add a row to the index table in the repo's `README.md`. If a chip entry was created or used, add the board link to the chip README's "Boards" line.
- Commit in the repo, e.g. `git add -A && git commit -m "Add <entry>"`. Don't push; the owner handles pushes.
- Update `MISSION.md`: move the item from Queue to Done, and log anything missing under Open issues.
- Report tersely: the entry path, what was fetched, what couldn't be found or was skipped, and any open question (such as which board revision the user has).

## Bulk mode ("do all my boards")

- List the distinct `board =` values across the owner's projects' `platformio.ini` files. `MISSION.md` already lists them.
- Generic IDs (`esp32-s3-devkitc-1`, `esp32dev`) often stand in for real vendor hardware, so read the project README/comments to find the actual board.
- Also collect the parts from `lib_deps` and the project names (sensors, displays).
- Process each one as above, one commit per entry.
