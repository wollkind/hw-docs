# ESP32-C5

Espressif's **dual-band** RISC-V SoC: 240 MHz high-performance core plus a 48 MHz low-power core, with Wi-Fi 6 on **both 2.4 GHz and 5 GHz**, Bluetooth LE (Core 6.0) and 802.15.4 for Thread 1.4 and Zigbee 3.0. QFN48 or LGA48, 6 × 6 mm.

- `esp32-c5_datasheet_en.pdf`: datasheet v1.5.
- `esp32-c5_technical_reference_manual_en.pdf`: registers and peripherals.
- `errata.md`: Espressif's chip errata list.

This is the only part in this library with a 5 GHz radio.

## Specs from the datasheet

| | |
|---|---|
| HP core | RISC-V, five-stage pipeline, up to 240 MHz, 820.19 CoreMark |
| LP core | RISC-V, two-stage pipeline, up to 48 MHz |
| Memory | 384 KB HP SRAM, 16 KB LP SRAM, 320 KB ROM. Flash and PSRAM are external, through a cached controller |
| Wi-Fi | 802.11ax on 2.4 and 5 GHz — OFDMA both ways, downlink MU-MIMO, beamformee, spatial reuse, TWT; also 802.11ac (20 MHz, downlink fullband MU-MIMO) and a/b/g/n at 20 and 40 MHz. Four virtual interfaces, antenna diversity, 802.11mc FTM |
| Bluetooth | LE, Bluetooth Core 6.0 certified; mesh 1.1; up to 20 dBm high-power mode; direction finding (AoA/AoD); PAwR; connection subrating; 125 kbps–2 Mbps |
| 802.15.4 | IEEE 802.15.4-2015, OQPSK at 250 kbps in 2.4 GHz; Thread 1.4, Zigbee 3.0 |
| GPIO | 29 |
| Analogue | 12-bit SAR ADC up to 6 channels, temperature sensor, brownout detector, analogue comparator |
| Digital | 2 × UART plus an LP UART, 2 × SPI for flash/PSRAM plus a general-purpose SPI, I2C plus an LP I2C, I2S, pulse counter, USB Serial/JTAG, **two CAN FD controllers** (ISO 11898-1:2015), SDIO slave (not on chip revisions v0.0 and v0.1) |

Part numbering seen on the cover: ESP32-C5HR2, ESP32-C5HR8 (in-package PSRAM) and ESP32-C5HF4 (in-package flash).

## Pins to know

- **Seven strapping pins:** GPIO7, GPIO25, GPIO26, GPIO27, GPIO28, MTMS and MTDI. GPIO27 and GPIO28 are pulled up by default (bit value 1); the rest float.
  - **Boot mode is GPIO26 + GPIO27 + GPIO28.** GPIO28 = 1 gives SPI boot; GPIO27 = 1 with GPIO28 = 0 gives joint download boot 0; all three low gives joint download boot 1.
  - Straps are latched at Chip Reset with a 3 ms hold time after CHIP_PU rises, and are ordinary IO afterwards.
- **GPIO13 and GPIO14 are USB_D- and USB_D+** for the USB Serial/JTAG controller.
- **GPIO11 and GPIO12 are UART0 TX and RX.**
- **Two CAN FD controllers** is unusual for this family — the C6 and C3 have one TWAI each.

## Errata worth knowing

From `errata.md`:

- **[CPU-718]** PSRAM read-after-write consistency.
- **[SRAM-436]** internal SRAM contents may be corrupted after the digital peripheral power domain powers down.
- **[FLASH-938]** manual flash encryption can fail with the CPU at 240 MHz.
- **[ECC-833]** forcing ECC memory power-down bypasses ECDSA_DS signature verification.
- **[HUK-576]** the hardware unique key is unavailable.

Boards: [espressif-esp32-c5-devkitc-1](../../boards/espressif-esp32-c5-devkitc-1/README.md)
