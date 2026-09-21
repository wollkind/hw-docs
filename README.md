# hw-docs

Local reference library for boards, chips and parts I own or use. Everything needed to work on the hardware lives here, so nothing has to be looked up again.

```
boards/<vendor>-<board>/   a dev board or module (Waveshare, Adafruit, Seeed…)
chips/<chip>/              an MCU/SoC family: datasheet, TRM, errata (shared by boards)
parts/<part>/              sensors, displays, drivers, panels, ICs
tools/                     fetchers (run with uv; no setup needed)
```

Each entry has:

- `README.md`: the distilled page. Key specs, pinout, a working PlatformIO config, gotchas, and which projects use it. Read this first.
- `sources.md`: every URL, the fetch date and the vendor repo commit.
- `wiki/`: vendor pages converted to markdown, with images.
- `hardware/`: schematic, dimensions and 3D files. `datasheets/`: PDFs.
- `reference/`, `examples/`: vendor pin headers and demo code worth keeping.

## Index

| Entry | What |
|---|---|
| [boards/waveshare-esp32-s3-rgb-matrix](boards/waveshare-esp32-s3-rgb-matrix/README.md) | ESP32-S3 N32R16 HUB75 driver, mics/IMU/RTC onboard |
| [boards/seengreat-rgb-matrix-adapter-e](boards/seengreat-rgb-matrix-adapter-e/README.md) | HUB75 carrier for ESP32-S3-DevKitC-1 / ESP32-DevKitC |
| [chips/esp32-s3](chips/esp32-s3/README.md) | Espressif ESP32-S3 |

## Adding hardware

In Claude Code: `/hw-docs <part or board name or URL>`. By hand:

```sh
uv run tools/fetch_page.py URL boards/x/wiki/overview.md   # page → markdown + images, lists links
uv run tools/fetch_file.py URL boards/x/hardware/schematic.pdf   # refuses HTML posing as PDF
```
