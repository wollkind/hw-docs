# RP2040

Raspberry Pi's dual Cortex-M0+ microcontroller: 133 MHz (200 MHz at 1.15 V core), 264 kB SRAM, no internal flash. QFN-56 7 × 7 mm.

- `rp2040-datasheet.pdf`: the full datasheet (build 2025-02-20). Pinout, peripherals, registers, electrical specs.

## Specs from the datasheet

| | |
|---|---|
| Cores | Two Cortex-M0+, up to 133 MHz; 200 MHz is reachable at a 1.15 V core voltage (datasheet §2.15.3) |
| SRAM | 264 kB in 6 banks, no internal flash |
| Flash | External QSPI with execute-in-place and a 16 kB cache; 6 dedicated IO carry it |
| GPIO | 30 multifunction, 1.8–3.3 V IO |
| ADC | 4 channels plus an internal temperature sensor, 12-bit, 500 ksps |
| USB | USB 1.1 host or device |
| PIO | Programmable IO blocks for peripherals the hardware does not implement |

## Pins to know

- **Six IO are consumed by the QSPI flash** and are not general-purpose.
- **PIO is the answer to a missing peripheral.** WS2812, DVI, extra UARTs and SDIO are all implemented as PIO programs rather than in silicon.
- The ADC reference is a separate pin on boards that break it out; the [Pico](../../boards/raspberrypi-pico/README.md) filters 3.3 V into it.

Boards: [raspberrypi-pico](../../boards/raspberrypi-pico/README.md), [adafruit-feather-rp2040-scorpio](../../boards/adafruit-feather-rp2040-scorpio/README.md)
