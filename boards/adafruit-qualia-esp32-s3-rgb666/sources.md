# Sources (fetched 2026-09-23)

- Product page https://www.adafruit.com/product/5800 (title only read).
- Learn guide https://learn.adafruit.com/adafruit-qualia-esp32-s3-for-rgb666-displays: `overview`, `pinouts`, `downloads`, `arduino-library-installation`, `arduino-rainbow-demo`, `backlight-settings`, `determining-timings`, `deep-sleep` → `wiki/*.md` (with images; the downloads page carries the schematic and fab-print PNGs). The FAQ page was fetched and dropped (generic CircuitPython FAQ).
- https://github.com/adafruit/Adafruit-Qualia-S3-RGB666-PCB @ `789d986f34e7949f0477ffd4a9567d1a4c07b310`: `Adafruit Qualia S3 RGB666.sch` → `hardware/eagle.sch`, `… .brd` → `hardware/eagle.brd`. Part list (AP2112K-3.3, TPS61169, PCA9554, ESP32-S3-WROOM, 40-pin FPC, 3VON power LED only) read from the schematic XML. Not copied: `factory-reset/` images, `assets/5800.jpg`.
- https://github.com/platformio/platform-espressif32 @ `1152c8f69146ca0c20ab772264606b3cc61ec67c`: `boards/adafruit_qualia_s3_rgb666.json` → `reference/platformio-board.json`.
- https://github.com/espressif/arduino-esp32 @ `e518da106ae3d7a96870feb2fca7d9dabb2b2c66`: `variants/adafruit_qualia_s3_rgb666/pins_arduino.h` → `reference/arduino-esp32-pins_arduino.h`.
- Owner's project: `wollkind/pio-blink` `platformio.ini`.
- Not fetched: 3D models (https://github.com/adafruit/Adafruit_CAD_Parts/tree/main/5800%20Qualia%20ESP32-S3), Fritzing part, ST7701 / NV3052C panel-driver datasheets (cdn-shop.adafruit.com links on the downloads page), TPS61169 and PCA9554A datasheets (ti.com).
- Unresolved: expander part name differs between schematic (PCA9554), Learn pinouts (PCA9554A) and Learn deep-sleep page (TCA9534); all three pages agree on address 0x3F.
