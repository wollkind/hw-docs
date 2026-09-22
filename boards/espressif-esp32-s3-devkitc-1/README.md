# Espressif ESP32-S3-DevKitC-1 (v1.1)

Espressif's entry-level ESP32-S3 board: a WROOM-1/1U/2 module, two USB ports, and every GPIO except the flash bus on 2 × 22 headers. Chip: [`chips/esp32-s3`](../../chips/esp32-s3/README.md).

**This board's ids are also used as build profiles for other hardware.** Across the owner's projects, `esp32-s3-devkitc-1` appears in `infopanel64` (really the Waveshare ESP32-S3 RGB Matrix) and `pio-strip-com`'s `display` env (really a SmartPanle SC05); `esp32-s3-devkitc1-n16r8` in `pio-rlcd` (Waveshare ESP32-S3-RLCD-4.2); `esp32-s3-devkitc1-n8r8` in `pio-crowpanel2` (Elecrow CrowPanel 2.13). The board file is a memory and flash description, so any S3 board with matching flash/PSRAM builds against it. This entry documents the Espressif kit itself; follow the links above for the hardware those projects actually run on.

## Ordering variants

| Ordering code | Module | Flash | PSRAM | SPI voltage |
|---|---|---|---|---|
| ESP32-S3-DevKitC-1-N8R8 | ESP32-S3-WROOM-1-N8R8 | 8 MB Quad | 8 MB Octal | 3.3 V |
| ESP32-S3-DevKitC-1U-N8R8 | ESP32-S3-WROOM-1U-N8R8 (external antenna) | 8 MB Quad | 8 MB Octal | 3.3 V |
| ESP32-S3-DevKitC-1-N32R16V | ESP32-S3-WROOM-2-N32R16V | 32 MB Octal | 16 MB Octal | **1.8 V** |

## Key specs

| | |
|---|---|
| Module | ESP32-S3-WROOM-1 / -1U / -2 |
| USB | **Two micro-USB ports.** One is the S3's own full-speed USB OTG (USB 1.1, flashing, CDC, JTAG). The other goes through a USB-to-UART bridge, up to 3 Mbps |
| Power | 5 V to 3.3 V LDO. Three mutually exclusive supplies: either USB port, the 5V pin, or the 3V3 pin |
| RGB LED | Addressable. **GPIO38 on v1.1, GPIO48 on the initial version** — both are on sale |
| Buttons | Boot and Reset. Hold Boot, press Reset for firmware download mode |

## Pinout

The J1 and J3 tables from the v1.1 user guide.

### J1

| No. | Name | Function |
|---|---|---|
| 1, 2 | 3V3 | 3.3 V supply |
| 3 | RST | EN |
| 4–7 | 4, 5, 6, 7 | RTC_GPIOn, TOUCHn, ADC1_CH3–CH6 |
| 8 | 15 | GPIO15, U0RTS, ADC2_CH4, XTAL_32K_P |
| 9 | 16 | GPIO16, U0CTS, ADC2_CH5, XTAL_32K_N |
| 10 | 17 | GPIO17, U1TXD, ADC2_CH6 |
| 11 | 18 | GPIO18, U1RXD, ADC2_CH7, CLK_OUT3 |
| 12 | 8 | GPIO8, TOUCH8, ADC1_CH7, SUBSPICS1 |
| 13 | 3 | GPIO3, TOUCH3, ADC1_CH2 — **strapping (JTAG source)** |
| 14 | 46 | GPIO46 — **strapping (ROM log)** |
| 15 | 9 | GPIO9, TOUCH9, ADC1_CH8, FSPIHD |
| 16 | 10 | GPIO10, TOUCH10, ADC1_CH9, FSPICS0 |
| 17 | 11 | GPIO11, TOUCH11, ADC2_CH0, FSPID |
| 18 | 12 | GPIO12, TOUCH12, ADC2_CH1, FSPICLK |
| 19 | 13 | GPIO13, TOUCH13, ADC2_CH2, FSPIQ |
| 20 | 14 | GPIO14, TOUCH14, ADC2_CH3, FSPIWP |
| 21 | 5V | 5 V supply |
| 22 | G | Ground |

### J3

| No. | Name | Function |
|---|---|---|
| 1 | G | Ground |
| 2 | TX | U0TXD, GPIO43 |
| 3 | RX | U0RXD, GPIO44 |
| 4 | 1 | GPIO1, TOUCH1, ADC1_CH0 |
| 5 | 2 | GPIO2, TOUCH2, ADC1_CH1 |
| 6–9 | 42, 41, 40, 39 | MTMS, MTDI, MTDO, MTCK (the JTAG pins) |
| 10 | 38 | GPIO38, FSPIWP — **the RGB LED on v1.1** |
| 11 | 37 | GPIO37, SPIDQS — **not usable on Octal flash/PSRAM boards** |
| 12 | 36 | GPIO36, SPIIO7 — **not usable on Octal boards** |
| 13 | 35 | GPIO35, SPIIO6 — **not usable on Octal boards** |
| 14 | 0 | GPIO0 — **strapping (boot mode)**, the Boot button |
| 15 | 45 | GPIO45 — **strapping (VDD_SPI voltage)** |
| 16 | 48 | GPIO48, SPICLK_N — **the RGB LED on the initial version** |
| 17 | 47 | GPIO47, SPICLK_P |
| 18 | 21 | GPIO21 |
| 19 | 20 | GPIO20, U1CTS, ADC2_CH9, **USB_D+** |
| 20 | 19 | GPIO19, U1RTS, ADC2_CH8, **USB_D-** |
| 21, 22 | G | Ground |

## PlatformIO config

Three board ids cover the variants, and they differ only in memory:

| Board id | Name in the board file | Flash | PSRAM | Partitions | Upload |
|---|---|---|---|---|---|
| `esp32-s3-devkitc-1` | ESP32-S3-DevKitC-1-N8 (8 MB QD, No PSRAM) | 8 MB `qio` | none | `default_8MB.csv` | 460800 |
| `esp32-s3-devkitc1-n8r8` | ESP32-S3-DevKitC-1-N8R8 | 8 MB | 8 MB octal (`qio_opi`) | `default_8MB.csv` | 921600 |
| `esp32-s3-devkitc1-n16r8` | ESP32-S3-DevKitC-1-N16R8V | 16 MB | 8 MB octal (`qio_opi`) | `default_16MB.csv` | 921600 |

All three set `mcu esp32s3`, `variant esp32s3`, 240 MHz and `-DARDUINO_ESP32S3_DEV`. Only the plain `esp32-s3-devkitc-1` adds `-DARDUINO_USB_MODE=1`; the two PSRAM profiles add `-DBOARD_HAS_PSRAM` instead. **Picking the wrong one silently costs the PSRAM**, exactly as with the Feather ESP32-S2 profiles.

## Operational notes

- **GPIO35, GPIO36 and GPIO37 are gone on any board with Octal flash or PSRAM** — that is every N8R8 and every WROOM-2 board. The user guide states it plainly; the pins are on the header but wired to the module's internal memory bus.
- **The RGB LED moved between revisions:** GPIO48 on the initial board, GPIO38 on v1.1. Both versions are still sold, so a blink sketch that does nothing is usually the wrong pin rather than a fault.
- **Four strapping pins sit on the headers:** GPIO0 (boot mode, under the Boot button), GPIO3 (JTAG source), GPIO45 (VDD_SPI voltage) and GPIO46 (ROM log). On a 1.8 V board (N32R16V) GPIO45 matters especially.
- **Two USB ports, different paths.** The UART bridge port is the default for flashing; the S3's own port gives CDC and JTAG without extra hardware.
- **Three power options, mutually exclusive.**

## Applications

- **Carrier host.** The [Seengreat RGB matrix adapter-E](../seengreat-rgb-matrix-adapter-e/README.md) in this library is built to take this board, which is the usual reason to own one.
- **Peripheral bring-up** before committing to a vendor board: every GPIO is on a header, and the touch, ADC and FSPI mappings are printed in the tables above.
- **PSRAM-dependent work** — frame buffers, audio buffers, TensorFlow Lite models — on the N8R8 or N16R8 variants.
- **Unsuitable for:** battery projects (no charger, no battery connector), and any design needing GPIO35–37 on an Octal-memory board.

## Files

- `wiki/user-guide-v1.1.md`: Espressif's v1.1 user guide, with images
- `hardware/schematic-v1.1.pdf`, `hardware/dimensions-v1.1.pdf`, `hardware/pcb-layout-v1.1.pdf`
- `hardware/esp32-s3-wroom-2_datasheet_en.pdf`: the WROOM-2 module datasheet (the WROOM-1/1U datasheet is in `chips/esp32-s3/`)
- `reference/platformio-esp32-s3-devkitc-1.json`, `-n8r8.json`, `-n16r8.json`: the three board definitions
