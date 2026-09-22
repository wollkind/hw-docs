# Seeed Studio XIAO nRF52840 Sense

A 21 × 17.8 mm nRF52840 board with an LSM6DS3TR-C IMU, a PDM mic, 2 MB QSPI flash, an RGB LED and a LiPo charger. Chip docs: [../../chips/nrf52840](../../chips/nrf52840/README.md).
Used by: none in `PlatformIO/Projects` yet. Wiring to the 1.69" LCD is in [../../parts/waveshare-1.69in-lcd-module](../../parts/waveshare-1.69in-lcd-module/README.md).

## Key specs

| | |
|---|---|
| MCU | nRF52840, Cortex-M4F 64 MHz, 1 MB flash / 256 KB RAM |
| Extra flash | 2 MB QSPI (P25Q16H) |
| Radio | BLE 5.4, Bluetooth Mesh, NFC |
| USB | native USB-C. The UF2 bootloader (Adafruit nRF52, 0.6.1, SoftDevice S140 7.3.0) shows up as a drive |
| IMU | LSM6DS3TR-C on its own I2C bus (Wire1), with a power-enable pin |
| Mic | PDM. The schematic names MSM261D3526H1CPM; the wiki links a WMM7035DTTJ0 datasheet |
| Charger | BQ25101: 50 or 100 mA, selected by P0.13 |
| I/O | 11 PWM, 6 analog, 1 I2C, 1 UART, 1 SPI on the headers. NFC pads on the back |

## Pinout (Seeed nRF52 core `variants/Seeed_XIAO_nRF52840_Sense/variant.cpp`)

| D | nRF pin | Role | | D | nRF pin | Role |
|---|---|---|---|---|---|---|
| D0/A0 | P0.02 | | | D11 | P0.26 | LED red (LED_BUILTIN) |
| D1/A1 | P0.03 | | | D12 | P0.06 | LED blue |
| D2/A2 | P0.28 | | | D13 | P0.30 | LED green |
| D3/A3 | P0.29 | | | D14 | P0.14 | VBAT_ENABLE (drive LOW to read) |
| D4/A4 | P0.04 | SDA (Wire) | | D15 | P1.08 | IMU power |
| D5/A5 | P0.05 | SCL (Wire) | | D16 / D17 | P0.27 / P0.07 | IMU SCL / SDA (Wire1) |
| D6 | P1.11 | TX (Serial1) | | D18 | P0.11 | IMU INT1 |
| D7 | P1.12 | RX (Serial1) | | D19 | P1.10 | mic power |
| D8 | P1.13 | SCK | | D20 / D21 | P1.00 / P0.16 | PDM CLK / DATA |
| D9 | P1.14 | MISO | | D22 | P0.13 | charge current select (HICHG) |
| D10 | P1.15 | MOSI | | D23 | P0.17 | ~CHG (low = charging) |
| | | | | D24–D29 | P0.21, .25, .20, .24, .22, .23 | QSPI flash |
| | | | | D30 / D31 | P0.09 / P0.10 | NFC1 / NFC2 |
| | | | | PIN_VBAT (32) | P0.31 (AIN7) | battery voltage |

The IMU I2C address is 0x6A according to the Seeed LSM6DS3 library default (unverified against the schematic, which doesn't show the SA0 strap clearly).

## Arduino cores

- **Seeed nRF52 Boards** (Adafruit-based): use it for BLE (Bluefruit) and low power. Serial may not compile without `#include <Adafruit_TinyUSB.h>`.
- **Seeed nRF52 mbed-enabled Boards:** use it for the IMU/PDM advanced functions and TinyML. Serial works out of the box.
- The two cores' pin definitions differ slightly.
- PlatformIO: no official board in `nordicnrf52`, so community platforms are needed (unverified). Arduino IDE is the vendor path.

## Operational notes

- **Battery reading can damage P0.31:** with P0.14 HIGH, P0.31 can see the full battery voltage and exceed its 3.6 V limit. Keep P0.14 **LOW** whenever reading, and don't set it HIGH while charging.
- **Charge current:** the wiki text says P0.13 as a hi-Z input selects 50 mA and driven LOW selects 100 mA. Its "low current" code sample drives HIGH instead. Use hi-Z or LOW as the text says.
- **Board not found or upload stuck:** press Reset once; if that doesn't work, double-tap it for the UF2 bootloader.
- **Bootloader recovery:** J-Link on the SWD pads, then flash `firmware/bootloader-0.6.1_s140_7.3.0.hex`.
- **Charge LED:** the green/red charge LED follows ~CHG (P0.17): lit while charging, off when full or not charging.

## Applications

- **Wearable motion logger.** The 6-axis IMU plus BLE in a 21 × 17.8 mm outline. Suitable for gesture classification and step or orientation logging.
- **Sound-level or keyword sensor.** The PDM microphone feeds edge inference without an external codec.
- **BLE beacon or peripheral.** nRF52840 supports BLE 5 and NFC; the board runs from a LiPo cell with onboard charging.

## Files

- `wiki/getting-started.md` (+ `img/`): covers the XIAO nRF52840, Sense and Plus
- `hardware/sense-schematic.pdf`, `sense-kicad-v1.1.zip`, `sense-pinout.xlsx`, `sense-dxf.zip`, `bottom-pads.zip`, `3d-model.zip`, `non-sense-schematic.pdf`
- `datasheets/`: BQ25101, LSM6DS3TR, WMM7035 mic, P25Q16H flash, BLE range test report
- `firmware/bootloader-0.6.1_s140_7.3.0.hex`
- `reference/variant.h`, `reference/variant.cpp` (Seeed nRF52 core)
