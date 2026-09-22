# Seeed Studio XIAO nRF54LM20A Sense (SKU 100018440)

XIAO-format board around Nordic's nRF54LM20A: BLE 6.0 / Thread / Zigbee / Matter / NFC, 8 MB external flash, nPM1300 PMIC, and on the Sense version an LSM6DS3TR-C IMU and a PDM microphone. Chip: [../../chips/nrf54lm20a](../../chips/nrf54lm20a/README.md).
Used by: no project (new board, not in any `pio-*` repo checked).

## Key specs

| | |
|---|---|
| SoC | nRF54LM20A: Cortex-M33 @ 128 MHz + RISC-V coprocessor @ 128 MHz |
| RAM / NVM | 512 KB RAM, 2 MB on-chip NVM (PlatformIO reports 2 084 864 B max sketch, 524 288 B RAM) |
| External flash | 8 MB PY25Q64HA SPI NOR (on `spi00`) |
| PMIC | Nordic nPM1300: charging, regulation, ship mode; on its own I2C |
| Radio | BLE 6.0 incl. Channel Sounding, BLE Mesh, Thread, Zigbee, Matter, Amazon Sidewalk, proprietary 2.4 GHz (to 4 Mbps); PCB antenna + IPEX4 connector |
| Sense extras | LSM6DS3TR-C 6-axis IMU (I2C **0x6A**), MSM261DGT006 PDM MEMS microphone |
| I/O | 28 GPIO, 9 analog, 1× I2C, 1× UART, 1× SPI, NFC, SHPHLD pin |
| Onboard | RGB user LED, charge LED, reset button, user button, IPEX4 connector |
| Debug | SAMD11 coprocessor providing CMSIS-DAP (SWD shared with the nRF54; separate SAMD11_RESET pad) |
| Power | USB-C 5 V, or 3.7 V Li-ion on BAT+/BAT− |
| Sleep current (Sense, 3.7 V) | light sleep ~9.96 µA, System OFF ~4.76 µA (4.92 µA with GRTC wake), ship mode 0.33 µA |
| Size / temp | 21 × 17.8 mm, −20 °C to 70 °C |

## Pinout

Header pins, from Seeed's schematic. Pad names as the schematic labels them — each header pad carries an analogue name, a digital name and, where applicable, a bus name, all on one pin:

| Pad | Chip pin | Schematic label |
|---|---|---|
| A0 / D0 | P1.00 | `P1.00/A0/D0` |
| A1 / D1 | P1.31 | `P1.31/A1/D1` |
| A2 / D2 | P1.30 | `P1.30/A2/D2` |
| A3 / D3 | P1.29 | `P1.29/A3/D3` |
| **SDA / A7 / D4** | P1.03 | `P1.03/SDA/A7/D4` |
| **SCL / A8 / D5** | P1.07 | `P1.07/SCL/A8/D5` |
| TX / D6 | P1.08 | `P1.08/Tx/D6` |
| RX / D7 | P1.09 | `P1.09/Rx/D7` |
| SCK / A6 / D8 | P1.04 | `P1.04/SCK/A6/D8` |
| MISO / A5 / D9 | P1.05 | `P1.05/MISO/A5/D9` |
| MOSI / A4 / D10 | P1.06 | `P1.06/MOSI/A4/D10` |
| NFC1 / NFC2 | P1.01 / P1.02 | `P1.01/NFC1`, `P1.02/NFC2` |
| VBUS, 3V3, GND, BAT+, BAT−, SHPHLD | — | power |
| RESET, SWCLK, SWDIO, SAMD11_RESET | — | debug/reset |

Onboard peripherals (Seeed pin map, confirmed against the Zephyr overlays in `reference/`):

| Signal | Chip pin |
|---|---|
| User button (`sw0`, active low, pull-up) | P0.09 |
| RGB LED R / G / B | P1.22 / P1.24 / P1.23 |
| IMU I2C SDA / SCL (`i2c30`) | P0.08 / P0.07 |
| IMU INT1 | P0.06 |
| IMU CS | P3.12 |
| Mic data / clock (`pdm20`) | P1.14 / P1.13 |
| nPM1300 I2C SDA / SCL (bit-banged GPIO I2C) | P1.18 / P1.17 |
| NFC antenna | P1.02 / P1.01 |
| GRTC | P0.04 / P0.05 |
| External flash `py25q64` on `spi00`: HOLD# / SCK / MOSI / WP# / MISO / CS# | P2.00 / P2.01 / P2.02 / P2.03 / P2.04 / P2.05 |

**The A7/SDA question is settled by the schematic:** they are one pin. Seeed's silkscreen names P1.03 `SDA`, `A7` and `D4`, and the schematic net is literally `P1.03/SDA/A7/D4`. The same applies to SCL, which is also `A8` and `D5` on P1.07. Using the user I2C therefore costs two of the analogue inputs.

## PlatformIO (from the Seeed wiki, untested here)

```ini
[env:seeed-xiao-nrf54lm20a]
platform = https://github.com/Seeed-Studio/platform-seeedboards.git
framework = zephyr
board = seeed-xiao-nrf54lm20a
monitor_speed = 115200
```

Install the platform once with `pio pkg install -g -p "https://github.com/Seeed-Studio/platform-seeedboards.git"`. Upload defaults to CMSIS-DAP through the onboard SAMD11 (pyOCD/probe-rs/J-Link also listed); `pio run -e seeed-xiao-nrf54lm20a -t upload`.

Arduino is possible but unofficial: the wiki points at a **third-party** core, `https://raw.githubusercontent.com/lolren/nrf54-arduino-core/main/package_nrf54l15clean_index.json` ("nRF54L15 Boards" → XIAO nRF54LM20A). Zephyr, either through PlatformIO or the nRF Connect SDK, is the supported path; MicroPython has a flash package too.

## Operational notes

- **The IMU and mic are not powered at boot.** The rails are `power_en` (fixed regulator on P1.12) and `imu_vdd`/`dmic_vdd` = nPM1300 **LDO1** at 3.3 V. Seeed's samples mark the sensor `zephyr,deferred-init` and enable the rails from `main()`, because the nPM1300 hangs off a GPIO-bit-banged I2C that is not ready when the regulator driver initialises (priority 92 vs sensor 90). Initialise in that order or the IMU never answers.
- **IMU driver:** the LSM6DS3TR-C binds to Zephyr's `st,lsm6dsl` driver (`CONFIG_LSM6DSL=y`) at address 0x6A on `i2c30`.
- **Charger defaults** in Seeed's sample: 4.2 V termination, 150 mA charge current, 500 mA VBUS limit. Raise the current only after checking the cell's rating.
- **Ship mode** is entered through the PMIC and drops the board to 0.33 µA. The SHPHLD pad returns it to normal operation.
- **Two I2C buses:** the user I2C (P1.03/P1.07) is separate from both the IMU bus (P0.08/P0.07) and the PMIC bus (P1.18/P1.17). A sensor added to the user bus cannot conflict with the onboard devices.
- **Non-Sense variant:** same board without the IMU and microphone; everything else in the pin map is identical.

## Applications

- **Motion-wake asset tag.** LSM6DS3TR-C interrupt on P0.06 wakes the SoC from System OFF at 4.76 µA; ship mode at 0.33 µA covers storage and transport. Power the IMU rail from nPM1300 LDO1 before initialising the sensor.
- **Audio or vibration event recorder.** PDM microphone on `pdm20`, 8 MB PY25Q64 flash on `spi00` for buffered capture.
- **Matter or Thread sensor.** BLE 6.0, Thread, Zigbee and Matter are supported through the nRF Connect SDK; PlatformIO builds the same Zephyr targets.
- **Constraint:** Arduino support is a third-party core. Zephyr is the supported path.

## Files

- `hardware/schematic.pdf`: Seeed's schematic (fetched 2026-09-22)
- `hardware/sch-pcb-v1.0.zip`: the V1.0 schematic and PCB source archive, kept packed
- `wiki/`: Seeed's wiki pages in their source form — getting started, built-in sensors, pin multiplexing, low power, NCS, Arduino, MicroPython, BLE, Matter, NFC, e-paper + SD application. Images are remote links on `files.seeedstudio.com`, which was unreachable when the pages were saved, so they do not render offline.
- `reference/seeed-xiao-nrf54lm20a.json`: the PlatformIO board definition (memory sizes, upload protocols, SVD name)
- `reference/tapwake-imu.overlay`, `reference/npm1300.overlay`: Seeed's Zephyr overlays for the IMU rails and the PMIC I2C/charger settings
