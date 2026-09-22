# ESP32-C6

Espressif single-core 32-bit RISC-V (HP) at up to 160 MHz plus a 20 MHz low-power RISC-V core, with **Wi-Fi 6 (802.11ax) on 2.4 GHz, Bluetooth 5 LE, and 802.15.4 for Zigbee 3.0 and Thread 1.3** sharing one antenna. QFN40 (30 GPIO) or QFN32 (22 GPIO, in-package flash).

- `esp32-c6_datasheet_en.pdf`: datasheet v1.5. Pin tables, strapping, power, RF characteristics, package.
- `esp32-c6_technical_reference_manual_en.pdf`: registers and peripherals.
- `errata.md`: Espressif's chip errata list, converted from the ESP Chip Errata site.

## Specs from the datasheet

| | |
|---|---|
| HP core | 32-bit RISC-V, four-stage pipeline, up to 160 MHz, 496.66 CoreMark |
| LP core | 32-bit RISC-V, two-stage pipeline, up to 20 MHz |
| Memory | 512 KB HP SRAM, 16 KB LP SRAM, 320 KB ROM, 32 KB L1 cache, 4096-bit eFuse (up to 1792 bits for users) |
| Flash | SPI/Dual/Quad/QPI off-package, or in-package on the FH4 / FH8 parts (QFN32) |
| GPIO | 30 on QFN40, 22 on QFN32. **5 are strapping pins; 6 more are taken by off-package flash** |
| Radios | Wi-Fi 6 2.4 GHz, Bluetooth 5 LE, 802.15.4 — coexisting on one antenna |

Part numbering: `ESP32-C6` (no flash) / `ESP32-C6FH4` / `ESP32-C6FH8` — `F` = in-package flash, `H` = high-temperature flash, the digit = flash size in MB.

## Pins to know

- **Strapping pins are GPIO4, GPIO5, GPIO8, GPIO9 and GPIO15.** Defaults: MTMS (GPIO4), MTDI (GPIO5), GPIO8 and GPIO15 float; **GPIO9 has a weak pull-up (bit value 1)**.
  - **Boot mode is GPIO8 + GPIO9**: GPIO9 = 1 gives SPI boot whatever GPIO8 does; GPIO8 = 1 with GPIO9 = 0 gives joint download boot (USB-Serial-JTAG, UART or SDIO download).
  - GPIO8 also controls ROM message printing; GPIO15 selects the JTAG signal source; MTMS/MTDI set the SDIO sampling and driving clock edges.
  - Every strap is latched at Chip Reset and the pins are ordinary IO afterwards. Hold time after CHIP_PU goes high is 3 ms.
- **GPIO12 and GPIO13 are USB_D- and USB_D+**, wired to the USB Serial/JTAG controller by default. They have to be reconfigured to serve as GPIO.
- **GPIO16 and GPIO17 are UART0 TX and RX.**
- **SPICLK, SPICS0, SPID, SPIQ, SPIWP and SPIHD go to off-package flash.** Espressif's own notice: do not use the flash pins for anything else. On QFN32 parts with in-package flash those pins are not routed out at all.
- **VDD_SPI (GPIO27 on QFN40)** powers off-package flash and is only usable as a GPIO when the flash has its own supply.

## Errata worth knowing

Full list in `errata.md`. The ones that change how code is written:

- **[ADC-1477]** loss of precision in the lower four bits of the SAR ADC — treat the ADC as coarser than 12 bits.
- **[CLK-8588]** the 32 kHz internal slow RC oscillator may fail to oscillate.
- **[CLK-6996]** RC_FAST_CLK calibration is inaccurate.
- **[SPI-304]** enabling flash auto-suspend can corrupt reads.
- **[RMT-176]** the idle-state level can be wrong in RMT continuous TX mode — relevant to anything driving addressable LEDs from RMT.
- **[WIFI-9686]** the ESP32-C6 cannot act as an 802.11mc FTM initiator.
- **[CPU-206]** (v0.0/v0.1 only, fixed in v0.2) and **[CPU-863]** concern LP SRAM execution and misaligned access.

Boards: [seeed-xiao-esp32c6](../../boards/seeed-xiao-esp32c6/README.md), [espressif-esp32-c6-devkitc-1](../../boards/espressif-esp32-c6-devkitc-1/README.md)
