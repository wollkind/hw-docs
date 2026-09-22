# Raspberry Pi Pico (RP2040)

21 × 51 mm DIP-style board carrying an RP2040 and 2 MB of QSPI flash, with castellated edges so it can be reflowed as a module. Chip: [`chips/rp2040`](../../chips/rp2040/README.md).
Used by: `pio-feather` (`[env:pico]`, built with `board_build.core = earlephilhower`).

## Key specs

| | |
|---|---|
| MCU | RP2040, dual Cortex-M0+ at up to 133 MHz |
| Flash | **2 MB** QSPI (W25Q16 class), execute-in-place |
| RAM | 264 kB (`maximum_ram_size` 262144 in the board file) |
| IO | **26 GPIO on the header** of the chip's 30; 23 digital-only, 3 ADC-capable |
| ADC | 12-bit, 500 ksps; `ADC_VREF` on pin 35 is filtered 3.3 V and can be driven externally |
| USB | Micro-USB B, USB 1.1 device or host |
| Power | VSYS 1.8–5.5 V into an RT6150 buck-boost SMPS |
| Debug | 3-pin ARM SWD port |
| Board | 40 pins, 0.1″, 1 mm PCB, castellated |

## Pins used by the board itself

These four RP2040 GPIO are not free:

| GPIO | Direction | Use |
|---|---|---|
| 23 | out | On-board SMPS power-save control |
| 24 | in | VBUS sense — high when USB power is present |
| 25 | out | **User LED** |
| 29 | in | ADC3, reads VSYS ÷ 3 |

Non-GPIO pins on the 40-pin header:

| Pin | Name | Notes |
|---|---|---|
| 40 | VBUS | 5 V from the micro-USB connector, or 0 V when unpowered |
| 39 | VSYS | Main input, 1.8–5.5 V, feeds the SMPS |
| 37 | 3V3_EN | SMPS enable, pulled to VSYS through 100 kΩ. **Short it low to kill the 3.3 V rail and the RP2040 with it** |
| 36 | 3V3 | SMPS output. Usable for external circuits; keep the load under 300 mA |
| 35 | ADC_VREF | ADC supply and reference, filtered 3.3 V |
| 33 | AGND | Analogue ground for GPIO26–29, on its own plane |
| 30 | RUN | RP2040 enable, ~50 kΩ internal pull-up. Short low to reset |

Six test points exist for module use: TP1 ground, TP2 USB DM, TP3 USB DP, TP4 GPIO23 (do not use), TP5 GPIO25/LED (not recommended — it only swings between 0 V and the LED forward voltage), TP6 BOOTSEL (short low at power-up for mass-storage programming).

## PlatformIO config

`pio-feather` builds it as:

```ini
[env:pico]
platform = https://github.com/maxgerhardt/platform-raspberrypi.git
board = pico
board_build.core = earlephilhower
framework = arduino
```

The board file sets `mcu rp2040`, `cpu cortex-m0plus`, 133 MHz, `-D ARDUINO_RASPBERRY_PI_PICO -DARDUINO_ARCH_RP2040 -DUSBD_MAX_POWER_MA=500`, 2 MB maximum sketch size, and uploads over `picotool` with `use_1200bps_touch`. `board_build.core = earlephilhower` selects the arduino-pico core rather than the Arduino Mbed core; the board file's `earlephilhower` block then supplies variant `rpipico`, the `boot2_w25q080_2_padded_checksum.S` second-stage bootloader and USB VID/PID 0x2e8a/0x000a. Frameworks available: `arduino` and `picosdk`.

## Operational notes

- **BOOTSEL is a boot-time-only button.** Hold it while applying power (or while releasing RUN) and the board enumerates as a mass-storage device; drop a UF2 on it. There is no reset button on the Pico — RUN (pin 30) shorted to ground is the reset.
- **The LED is on GPIO25 on this board, not on the wireless boards.** Code that blinks `LED_BUILTIN` moves to a Pico W or Pico 2 W and goes dark, because there the LED hangs off the CYW43 chip.
- **3V3_EN is a foot-gun in a wiring harness**: it is pulled up to VSYS, and grounding it powers the board down.
- **Do not sink much from the 3V3 pin.** Raspberry Pi's own limit is 300 mA, and it shrinks as the RP2040's own load rises.
- **GPIO23's SMPS power-save setting affects ADC noise** — the datasheet ties the powerchain behaviour to it, which is why it is exposed as an output rather than left fixed.
- **2 MB of flash is the whole budget.** The Pico 2 has 4 MB.

## Applications

- **PIO-driven peripherals.** The reason to pick an RP2040 over an ESP32 is the programmable IO: WS2812, DVI output, extra UARTs, SDIO — all implemented in PIO programs.
- **USB device work.** Native USB 1.1, and the board enumerates as mass storage for programming with no toolchain on the host.
- **Deterministic two-core control loops**, with no radio stack stealing cycles.
- **Unsuitable for:** anything wireless — there is no radio on this board — and for large data buffers, with 264 kB of SRAM and 2 MB of flash.

## Files

- `hardware/pico-datasheet.pdf`: Raspberry Pi's board datasheet, including the schematic appendix
- `hardware/pinout.pdf`: the A4 pinout diagram
- `reference/platformio-pico.json`: the `pico` board definition from the platform the project builds against
