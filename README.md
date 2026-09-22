# hw-docs

Local reference library for boards, chips and parts I own or use. Everything needed to work on the hardware lives here, so nothing has to be looked up again.

```
boards/<vendor>-<board>/   a dev board or module (Waveshare, Adafruit, Seeed…)
chips/<chip>/              an MCU/SoC family: datasheet, TRM, errata (shared by boards)
parts/<part>/              sensors, displays, drivers, panels, ICs
tools/                     fetchers (run with uv; no setup needed)
examples/                  small cross-board demos that exercise entries in the library
```

Each entry has:

- `README.md`: the distilled page. Key specs, pinout, a working PlatformIO config, operational notes, applications, and which projects use it. Read this first.
- `sources.md`: every URL, the fetch date and the vendor repo commit.
- `wiki/`: vendor pages converted to markdown, with images.
- `hardware/`: schematic, dimensions and 3D files. `datasheets/`: PDFs.
- `reference/`, `examples/`: vendor pin headers and demo code worth keeping.

## Index

| Entry | What |
|---|---|
| [boards/waveshare-esp32-s3-rgb-matrix](boards/waveshare-esp32-s3-rgb-matrix/README.md) | ESP32-S3 N32R16 HUB75 driver, mics/IMU/RTC onboard |
| [boards/seengreat-rgb-matrix-adapter-e](boards/seengreat-rgb-matrix-adapter-e/README.md) | HUB75 carrier for ESP32-S3-DevKitC-1 / ESP32-DevKitC |
| [boards/seeed-xiao-esp32c6](boards/seeed-xiao-esp32c6/README.md) | XIAO ESP32-C6: Wi-Fi 6, BLE, Zigbee/Thread |
| [boards/seeed-xiao-esp32s3](boards/seeed-xiao-esp32s3/README.md) | XIAO ESP32-S3 / Sense / Plus |
| [boards/seeed-wio-sx1262-xiao-esp32s3](boards/seeed-wio-sx1262-xiao-esp32s3/README.md) | XIAO ESP32-S3 + Wio-SX1262 LoRa kit (Meshtastic) |
| [boards/seeed-xiao-1.14in-display-esp32s3](boards/seeed-xiao-1.14in-display-esp32s3/README.md) | XIAO ESP32-S3 Plus + 1.14" ST7789, IMU, mic, buttons |
| [boards/seeed-xiao-nrf52840-sense](boards/seeed-xiao-nrf52840-sense/README.md) | XIAO nRF52840 Sense (IMU, PDM mic) |
| [boards/waveshare-esp32-s3-rlcd-4.2](boards/waveshare-esp32-s3-rlcd-4.2/README.md) | ESP32-S3 + 4.2" 300×400 reflective ST7305 LCD, audio, RTC (used by pio-rlcd) |
| [boards/elecrow-crowpanel-epaper-2.13](boards/elecrow-crowpanel-epaper-2.13/README.md) | ESP32-S3 + 2.13" 122×250 e-paper HMI (used by pio-crowpanel2) |
| [boards/elecrow-crowpanel-epaper-4.2](boards/elecrow-crowpanel-epaper-4.2/README.md) | ESP32-S3 + 4.2" 400×300 SSD1683 e-paper HMI |
| [boards/aitrip-esp32-s3-2.8in-touch-lcd](boards/aitrip-esp32-s3-2.8in-touch-lcd/README.md) | 2.8" 240×320 ESP32-S3 touch module (provisional: board not identified) |
| [boards/adafruit-esp32-s3-reverse-tft-feather](boards/adafruit-esp32-s3-reverse-tft-feather/README.md) | ESP32-S3 Feather, rear 240×135 ST7789, 3 buttons |
| [boards/adafruit-feather-esp32-s2](boards/adafruit-feather-esp32-s2/README.md) | ESP32-S2 Feather (PID 5000/5303), STEMMA QT |
| [boards/adafruit-feather-32u4-rfm69](boards/adafruit-feather-32u4-rfm69/README.md) | ATmega32U4 Feather + RFM69HCW 915 MHz (used by pio-radio*) |
| [boards/adafruit-feather-rp2040-scorpio](boards/adafruit-feather-rp2040-scorpio/README.md) | RP2040 Feather, 8× level-shifted NeoPixel outputs |
| [boards/seeed-xiao-log](boards/seeed-xiao-log/README.md) | XIAO Logger HAT: SHT40, BH1750, PCF8563, battery sense |
| [boards/seeed-xiao-powerbread](boards/seeed-xiao-powerbread/README.md) | Breadboard PSU + INA3221 meter, XIAO-hosted |
| [boards/seeed-xiao-expansion-board](boards/seeed-xiao-expansion-board/README.md) | XIAO carrier: OLED, PCF8563 RTC, microSD, Grove, LiPo |
| [boards/seeed-xiao-nrf54lm20a-sense](boards/seeed-xiao-nrf54lm20a-sense/README.md) | XIAO nRF54LM20A Sense (BLE 6.0, nPM1300, IMU, PDM mic) |
| [boards/adafruit-matrix-portal-m4](boards/adafruit-matrix-portal-m4/README.md) | SAMD51 + ESP32 HUB75 controller, LIS3DH |
| [boards/lilygo-t3-lora32-v1.6.1](boards/lilygo-t3-lora32-v1.6.1/README.md) | ESP32-PICO-D4 + SX1276/SX1278 LoRa, SSD1306 OLED, microSD |
| [boards/wemos-d1-mini](boards/wemos-d1-mini/README.md) | LOLIN D1 mini: ESP8266EX, 4 MB flash, CH340C, LOLIN I2C port |
| [boards/adafruit-feather-huzzah-esp8266](boards/adafruit-feather-huzzah-esp8266/README.md) | ESP8266 Feather, CP2104, LiPo charger (used by pio-huzzah) |
| [parts/waveshare-1.69in-lcd-module](parts/waveshare-1.69in-lcd-module/README.md) | 1.69" 240×280 ST7789V2 SPI LCD (Seeed SKU 5755) |
| [parts/gc9a01-1.28in-round-lcd](parts/gc9a01-1.28in-round-lcd/README.md) | 1.28" 240×240 round GC9A01A SPI LCD module |
| [parts/sk-120-buck-boost](parts/sk-120-buck-boost/README.md) | XY-SK120 120 W buck-boost, CC/CV, Modbus RTU over TTL |
| [chips/esp32-s3](chips/esp32-s3/README.md) | Espressif ESP32-S3 |
| [chips/esp8266](chips/esp8266/README.md) | Espressif ESP8266EX (NRND) |
| [chips/nrf54lm20a](chips/nrf54lm20a/README.md) | Nordic nRF54LM20A |
| [chips/nrf52840](chips/nrf52840/README.md) | Nordic nRF52840 |
| [chips/atsamd51](chips/atsamd51/README.md) | Microchip ATSAMD51 |

Demos: [examples/lora-ping-pong](examples/lora-ping-pong/README.md) — SX1276 ↔ SX1262 link test with a documented packet format.

Work queue and resume instructions: [MISSION.md](MISSION.md).

## Adding hardware

In Claude Code: `/hw-docs <part or board name or URL>`. By hand:

```sh
uv run tools/fetch_page.py URL boards/x/wiki/overview.md   # page → markdown + images, lists links
uv run tools/fetch_file.py URL boards/x/hardware/schematic.pdf   # refuses HTML posing as PDF
```
