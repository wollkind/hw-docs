# RP2350

Raspberry Pi's second-generation microcontroller: two **Cortex-M33 or RISC-V Hazard3** cores at 150 MHz, selectable at boot, 520 kB SRAM, no internal flash on the A and B parts. QFN-60 (RP2350A) or QFN-80 (RP2350B).

- `rp2350-datasheet.pdf`: the full datasheet. Pinout, peripherals, registers, security model, electrical specs.

## Specs from the datasheet

| | |
|---|---|
| Cores | Two Cortex-M33 (Armv8-M Main) **or** two Hazard3 RISC-V, chosen at boot time; 150 MHz |
| SRAM | 520 kB in 10 banks; 8 kB OTP |
| External memory | Up to 16 MB QSPI flash or PSRAM, plus another 16 MB on an optional second chip select |
| Power | On-chip switched-mode supply for the core, with a low-quiescent LDO mode for sleep |
| GPIO | **5 V-tolerant when powered, 3.3 V-failsafe when unpowered** |
| Peripherals | 2 × UART, 2 × SPI, 2 × I2C, 24 × PWM, USB 1.1 host/device, **12 PIO state machines**, 1 × HSTX |
| Security | Optional signed boot enforced by mask ROM, OTP-held key fingerprint and decryption key, bus filtering by security/privilege level, per-peripheral and per-DMA security domains, fault-injection mitigations, SHA-256 accelerator |

Family: RP2350A is QFN-60 with 30 GPIO and 4 analogue inputs; RP2350B is QFN-80 with 48 GPIO and 8 analogue inputs. Flash-in-package variants exist.

## Differences from the RP2040 that change code

- **The cores are M33 or Hazard3, not M0+.** Binaries are not interchangeable, and the boot-time core choice is a property of the image.
- **Twelve PIO state machines** rather than eight, in three blocks.
- **GPIO tolerate 5 V while powered** — the RP2040's do not.
- **520 kB SRAM** against 264 kB.
- **HSTX** is new: a high-speed transmit peripheral for display interfaces.

Boards: [raspberrypi-pico-2](../../boards/raspberrypi-pico-2/README.md)
