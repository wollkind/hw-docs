# Raspberry Pi Pico 2 and Pico 2 W (RP2350)

The RP2350 successor to the Pico, in the same 21 × 51 mm 40-pin footprint: 4 MB flash, and on the W a 2.4 GHz radio. Chip: [`chips/rp2350`](../../chips/rp2350/README.md).
Used by: `pio-pico3` (`[env:pico]`, `board = rpipico2`, `framework = micropython`) and `pio-feather` (`[env:pico2]`, `board = rpipico2w`).

## Pico 2 against Pico 2 W

| | Pico 2 | Pico 2 W |
|---|---|---|
| MCU | RP2350A | RP2350 |
| Flash | 4 MB | 4 MB (W25Q16JV-class part named in the datasheet) |
| Radio | none | **Infineon CYW43439**, 802.11n Wi-Fi and Bluetooth 5.2 (LE central/peripheral and Classic), on-board Abracon-licensed antenna, connected over SPI |
| User LED | GPIO25 | **WL_GPIO0** — on the radio chip, not the RP2350 |
| GPIO on the header | 26, three ADC-capable | 26, three ADC-capable |

Both expose 26 of the chip's 30 GPIO, a 3-pin SWD port and castellated edges for module use, and both run VSYS from about 1.8 to 5.5 V into a buck-boost SMPS.

## Pins used by the board itself

**Pico 2** — same arrangement as the original Pico:

| GPIO | Direction | Use |
|---|---|---|
| 23 | out | SMPS power-save control |
| 24 | in | VBUS sense |
| 25 | out | User LED |
| 29 | in | ADC3, VSYS ÷ 3 |

**Pico 2 W** — the same four RP2350 pins are taken, but by the radio, and three board functions move onto the CYW43439:

| Pin | Direction | Use |
|---|---|---|
| GPIO23 | out | Wireless power-on |
| GPIO24 | out/in | Wireless SPI data / IRQ |
| GPIO25 | out | Wireless SPI CS — and when high, enables GPIO29's ADC to read VSYS |
| GPIO29 | out/in | Wireless SPI CLK, or ADC3 for VSYS ÷ 3 |
| WL_GPIO0 | out | **User LED** |
| WL_GPIO1 | out | SMPS power-save control |
| WL_GPIO2 | in | VBUS sense |

Non-GPIO header pins are the same on both: 40 VBUS, 39 VSYS, 37 3V3_EN, 36 3V3, 35 ADC_VREF, 33 AGND, 30 RUN.

## PlatformIO config

Both projects use `platform = https://github.com/maxgerhardt/platform-raspberrypi.git`.

```ini
[env:pico2]          ; pio-feather
board = rpipico2w
board_build.core = earlephilhower
framework = arduino
```

| Board id | Name | MCU | CPU | Clock | Flash | RAM | Extra flags |
|---|---|---|---|---|---|---|---|
| `rpipico2` | Pico 2 | rp2350 | cortex-m33 | 150 MHz | 4 MB | 512 kB | — |
| `rpipico2w` | Pico 2W | rp2350 | cortex-m33 | 150 MHz | 4 MB | 512 kB | `-DARDUINO_RASPBERRY_PI_PICO_2W -DUSBD_MAX_POWER_MA=250 -DPICO_CYW43_SUPPORTED=1 -DCYW43_PIN_WL_DYNAMIC=1` |

Both upload over `picotool` with `use_1200bps_touch`, and both debug against `rp2350.cfg` / `RP2350_M33_0`.

## Operational notes

- **`pio-pico3` declares `framework = micropython` for `board = rpipico2`, and that board file does not list micropython.** On `maxgerhardt/platform-raspberrypi` `develop` at the commit recorded in `sources.md`, `rpipico2.json` lists `arduino`, `picosdk` and `mbed-ce` only. Whether the build still resolves depends on the platform revision that project pins — check before assuming that env builds.
- **The user LED is not a GPIO on the W.** It is `WL_GPIO0` on the CYW43439, so the radio must be initialised before the LED can be driven. A blink sketch ported from a Pico or Pico 2 does nothing until then. `-DCYW43_PIN_WL_DYNAMIC=1` in the board file is part of how the arduino-pico core handles this.
- **On the W, four RP2350 pins belong to the radio** (23, 24, 25, 29) — the same numbers the plain Pico 2 uses for the LED, VBUS sense and SMPS control. Any code that pokes those directly will fight the Wi-Fi driver.
- **Reading VSYS on the W needs GPIO25 high**, because that line doubles as the wireless chip select.
- **RP2350 GPIO tolerate 5 V while powered** (per the chip entry), which the RP2040's do not — but ADC_VREF and the 3V3 rail are unchanged, so analogue inputs still want 0–3.3 V.
- **USB current declaration differs:** 500 mA on the original Pico's board file, 250 mA on the Pico 2 W's.
- **No reset button.** RUN (pin 30) to ground resets; BOOTSEL held at power-up gives the mass-storage bootloader.

## Applications

- **Wi-Fi/BLE sensor node with PIO peripherals** (Pico 2 W): twelve PIO state machines and a radio in one 21 × 51 mm board.
- **MicroPython work** — `pio-pico3` runs MicroPython on the Pico 2; the RP2350's 520 kB of SRAM leaves real room for it.
- **Signed-boot or security experiments.** The RP2350's OTP-backed boot signing has no equivalent on the RP2040.
- **Unsuitable for:** a drop-in RP2040 replacement in a project that talks to GPIO23–25 and 29 directly on a W, and for any design relying on 5 V analogue input.

## Files

- `hardware/pico-2-datasheet.pdf`, `hardware/pico-2-w-datasheet.pdf`: Raspberry Pi's board datasheets, each with its schematic appendix
- `hardware/pico-2-pinout.pdf`, `hardware/pico-2-w-pinout.pdf`: the pinout diagrams
- `reference/platformio-rpipico2.json`, `reference/platformio-rpipico2w.json`: the two board definitions
