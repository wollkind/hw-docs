# ESP32-C3

Espressif single-core 32-bit RISC-V at up to 160 MHz with 2.4 GHz Wi-Fi 4 and Bluetooth 5 LE. No Zigbee/Thread radio — that is the [ESP32-C6](../esp32-c6/README.md).

- `esp32-c3_datasheet_en.pdf`: datasheet v2.4.
- `esp32-c3_technical_reference_manual_en.pdf`: registers and peripherals.
- `errata.md`: Espressif's chip errata list.

## Specs from the datasheet

| | |
|---|---|
| CPU | 32-bit RISC-V single core, up to 160 MHz, 483.27 CoreMark |
| Memory | 400 KB SRAM (16 KB of it cache), 384 KB ROM, 8 KB RTC SRAM, 4096-bit eFuse (up to 1792 bits for users) |
| Flash | In-package on the FH4/FN4/FH8X parts, or off-package over SPI/Dual/Quad/QPI |
| GPIO | 22 on most parts (3 strapping, 6 taken by in-package flash), 16 on ESP32-C3FH4X and FH4AZ |
| Interfaces | 2 × UART, 3 × SPI, I2C, I2S, full-speed USB Serial/JTAG, TWAI (CAN 2.0), LED PWM (6 channels), RMT (2 TX + 2 RX) |
| Analog | Two 12-bit SAR ADCs, up to 6 channels; temperature sensor |
| Timers | Two 54-bit general-purpose, three digital watchdogs, analog watchdog, 52-bit system timer |

## Pins to know

- **Strapping pins are GPIO2, GPIO8 and GPIO9.** GPIO2 and GPIO8 float by default; **GPIO9 has a weak pull-up (bit value 1)**.
  - Boot mode: GPIO9 = 1 gives SPI boot, GPIO8 = 1 with GPIO9 = 0 gives joint download boot (UART or USB-Serial-JTAG). The datasheet's footnote says GPIO2 does not actually select the mode, but should be pulled up anyway to avoid glitches.
  - GPIO8 additionally controls ROM message printing. The straps are latched at Chip Reset and are ordinary IO afterwards.
- **GPIO18 and GPIO19 are USB_D- and USB_D+** for the USB Serial/JTAG controller.
- **GPIO20 and GPIO21 are UART0 RX and TX.**
- Six GPIOs are consumed by in-package flash on the F-suffixed parts and are not available at all.

## Errata worth knowing

Full list in `errata.md`:

- **[ADC-183]** the DMA path of SAR ADC2 does not work — use ADC1 for continuous sampling.
- **[ADC-270]** SAR ADC cannot sample enough data in DMA continuous mode after a restart.
- **[CPU-863]** misaligned memory access may raise an exception.

Boards: [espressif-esp32-c3-devkitc-02](../../boards/espressif-esp32-c3-devkitc-02/README.md)
