# Seengreat RGB Matrix Adapter Board (E)

Carrier board: an ESP32-S3-DevKitC-1 **or** an ESP32-DevKitC V4 plugs in, and the board drives a HUB75 panel. It has no MCU of its own. Chip docs: [../../chips/esp32-s3](../../chips/esp32-s3/README.md).

## Key specs

| | |
|---|---|
| Size | 70 × 60 mm, M2.5 mounting holes |
| Power in | USB-C 5 V/4 A (power only, no data) **or** DC-044 barrel 5 V/8 A |
| Power out | 2 × VH-4P (3.96 mm) panel-power connectors, 5 V/4 A each |
| Panel | HUB75 |
| Library | ESP32-HUB75-MatrixPanel-I2S-DMA (mrcodetastic) |

## Pinout: which board revision?

Check the silkscreen. V1.x and V2.x route HUB75 to different GPIOs.

ESP32-S3-DevKitC-1:

| Signal | V1.x | V2.x | | Signal | V1.x | V2.x |
|---|---|---|---|---|---|---|
| R1 | 37 | 18 | | A | 45 | 7 |
| G1 | 6 | 8 | | B | 1 | 48 |
| B1 | 36 | 17 | | C | 48 | 6 |
| R2 | 35 | 16 | | D | 2 | 47 |
| G2 | 5 | 1 | | E | 4 | 2 |
| B2 | 0 | 15 | | CLK | 47 | 5 |
| LAT | 38 | 21 | | OE | 21 | 4 |

ESP32-DevKitC V4:

| Signal | V1.x | V2.x | | Signal | V1.x | V2.x |
|---|---|---|---|---|---|---|
| R1 | 18 | 18 | | A | 4 | 26 |
| G1 | 25 | 17 | | B | 3 | 16 |
| B1 | 5 | 19 | | C | 0 | 25 |
| R2 | 17 | 21 | | D | 21 | 4 |
| G2 | 33 | 23 | | E | 32 | 22 |
| B2 | 16 | 27 | | CLK | 2 | 33 |
| LAT | 19 | 2 | | OE | 15 | 32 |

The V2.x S3 column matches the vendor demo `examples/esp32-s3-devkitc-1-demo-v2.x/…/PatternPlasma.ino`.

## Gotchas

- **V1.x with an S3 R8/R16 module:** V1.x puts R1/B1/R2 on GPIO37/36/35, which are octal-PSRAM pins on N8R8 and N16R8 modules. It also uses the strapping pins GPIO0 and GPIO45. Use V2.x with PSRAM DevKits.
- **DevKitC V4 on V1.x:** B is on GPIO3, the UART0 RX pin, so the serial monitor and upload share it with the panel.
- **Panel driver chip:** the demos default to `HUB75_I2S_CFG::SHIFT`. FM6126A panels need `mxconfig.driver = HUB75_I2S_CFG::FM6126A`.
- **64×64 panels:** these need the E pin set (`PIN_E`). Demo V1 code leaves `CH_E -1`.
- **Power:** USB-C on the adapter is power only. Program through the DevKit's own USB. Don't hot-plug; check polarity first.

## Files

- `wiki/overview.md` (+ `wiki/img/`): vendor wiki page as markdown
- `hardware/schematic-v1.x.pdf`, `hardware/schematic-v2.2.pdf`
- `hardware/3d-model-v1.1.zip`: STEP model (V1.1)
- `examples/`: vendor PatternPlasma demos for both DevKits, V1.x and V2.x
- `sources.md`: where everything came from
