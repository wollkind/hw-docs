# Sources (fetched 2026-09-21)

- Product page: https://lilygo.cc/products/lora3 — **not fetched**: lilygo.cc and wiki.lilygo.cc are blocked by the sandbox egress proxy. Identified as "T3 LoRa32 V1.6.1" from the vendor repo's own product link and a web search.
- GitHub https://github.com/Xinyuan-LilyGO/LilyGo-LoRa-Series @ `5e2da3f519a25e91b9b14c3071e36a568bbd949d` (shallow clone):
  - `docs/en/t3_v161_sx1276/t3_v161_sx1276_hw.md` → `wiki/t3-lora32-v1.6.1-hardware.md` (image link repointed to `img/`)
  - `docs/en/t3_v161_sx1276/images/LoRa-IPEX.png` → `wiki/img/`
  - `schematic/T3_V1.6.1.pdf` → `hardware/schematic-v1.6.1.pdf`
  - `dimensions/T3_V1.62.dwg` → `hardware/dimensions-v1.6.dwg`
  - `dimensions/T3_V1.6_3D.7z` → `hardware/3d-model-v1.6.7z`
  - `examples/SD/SD_Test/utilities.h` → `reference/utilities.h` (identical pin block in every example)
  - `platformio.ini` → `reference/lilygo-platformio.ini`
- Not copied: `firmware/lora-v1.6.1-{433,868,915}mhz-{sender,reciver}-*.bin` and `lora-v1.6.1-868mhz-paxcounter-*.bin` (vendor demo binaries, 0.4–1.4 MB each), `dimensions/T3-V2.1-1.6*.7z`, the whole `lib/` tree of bundled Arduino libraries.
- Resolved 2026-09-22: the ESP32-PICO-D4 datasheet is in `chips/esp32/`, fetched once espressif.com became reachable.
- Resolved 2026-09-22: the SX1276/77/78/79 datasheet is in `parts/sx127x-lora-transceiver/` (Semtech's Rev 4 document, taken from Adafruit's copy because semtech.com serves its documents through a JavaScript post-back; see that entry's `sources.md`).
- Owner's projects checked for "Used by": `wollkind/pio-radio`, `wollkind/pio-radio1`, `wollkind/pio-radio2` (all `feather32u4`/`leonardo` with RadioHead; no LilyGO board). Other `pio-*` repos were not searched.
