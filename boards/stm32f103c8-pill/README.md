# STM32F103C8T6 "Pill" boards (the `blackpill_f103c8` board id)

The 53 × 21 mm STM32F103C8T6 minimum-system board sold as Blue Pill, Black Pill and BluePill Plus by many makers. Chip: STM32F103C8T6, Cortex-M3 at 72 MHz — **no `chips/stm32f103` entry**, because ST's datasheet could not be fetched (see `sources.md`).
Used by: `pio-feather` (`[env:stm]`, `board = blackpill_f103c8`).

**Which board this is, is not established.** `blackpill_f103c8` is a generic profile: it names the MCU, the 72 MHz clock and the `variant_PILL_F103Cx.h` pin map, and nothing about a particular vendor's PCB. The Arduino variant it selects covers Blue Pill and Black Pill together and differs between them in one place — the LED. This entry documents what the id defines, plus WeAct Studio's BluePill Plus as the one design in this family with published schematics.

## Key specs

| | |
|---|---|
| MCU | STM32F103C8T6, Arm Cortex-M3, **72 MHz**, 64 KB flash, 20 KB SRAM |
| Package board | ~53 × 21 mm, 2 × 20 side pins plus a 1 × 4 SWD header (WeAct BluePill Plus V1.1) |
| Clocks | 8 MHz system crystal, 32.768 kHz RTC crystal (same board) |
| USB | The F103 has a USB device peripheral on PA11/PA12; whether a given clone's USB works depends on its pull-up resistor, which is the family's best-known defect |
| Debug | SWD on PA13 (SWDIO) and PA14 (SWCLK). The board file defaults to an ST-Link |

WeAct also sells the same PCB with a **GD32F303CCT6** (Cortex-M4, 120 MHz, 256 KB flash, 48 KB SRAM). It is not the same part and does not take the STM32 bootloader.

## Pinout

From `variant_PILL_F103Cx.h` in the STM32duino core, which is what `board = blackpill_f103c8` compiles against. Arduino pin numbers on the left, port pins as labelled on the silk.

| Arduino | Port | Note |
|---|---|---|
| 0–6 | PB9, PB8, PB7, PB6, PB5, PB4, PB3 | PB7/PB6 are the default I2C SDA/SCL |
| 7 | PA15 | |
| 8, 9 | PA12, PA11 | **USB D+ and D−** |
| 10, 11 | PA10, PA9 | **Default UART RX and TX** (`Serial1`) |
| 12 | PA8 | |
| 13–16 | PB15, PB14, PB13, PB12 | **PB12 is the LED on a Black Pill** |
| 17 | PC13 | **PC13 is the LED on a Blue Pill** |
| 18, 19 | PC14, PC15 | 32.768 kHz crystal on most boards |
| A0–A7 | PA0–PA7 | PA4/PA5/PA6/PA7 are also SPI SS/SCK/MISO/MOSI |
| A8, A9 | PB0, PB1 | |
| 30, 31 | PB10, PB11 | |
| 32 | PB2 | **BOOT1** |
| 33, 34 | PA13, PA14 | **SWDIO, SWCLK** |

35 digital pins, 10 analogue inputs. Defaults: SPI SS PA4, SCK PA5, MISO PA6, MOSI PA7; I2C SDA PB7, SCL PB6; `Serial1` on PA9/PA10; tone on TIM3, servo on TIM2.

On the WeAct BluePill Plus specifically: blue LED on **PB2**, active high; a KEY button on **PA0**; a red power LED.

## PlatformIO config

`pio-feather` builds it as:

```ini
[env:stm]
platform = ststm32
board = blackpill_f103c8
framework = arduino
```

The board file sets `mcu stm32f103c8t6`, `cpu cortex-m3`, `-DSTM32F1 -DSTM32F103xB`, 72 MHz, variant `STM32F1xx/F103C8T_F103CB(T-U)` with `variant_h` `variant_PILL_F103Cx.h`, debug through `stlink` with `openocd_target stm32f1x` and `reset_config none`. Its USB hardware IDs are `0x1EAF:0x0003` and `0x1EAF:0x0004` — the **Maple** bootloader's IDs, not ST's.

## Operational notes

- **The LED pin differs between Blue Pill and Black Pill.** The variant picks PC13 when `ARDUINO_BLUEPILL_F103C8`/`F103CB` is defined and **PB12 otherwise**, and `blackpill_f103c8` does not define either, so `LED_BUILTIN` compiles to PB12. On a Blue Pill that blinks nothing; use PC13 explicitly. WeAct's BluePill Plus puts its LED on PB2, so neither default is right there.
- **`-DSTM32F103xB` describes a 128 KB part**, while a C8 is documented as 64 KB. Many C8 dies do have the full 128 KB and the ST-Link will program it, but that is silicon lottery: a sketch over 64 KB may work on one board and not the next.
- **The hardware IDs in the board file are Maple's.** If the board arrived with an ST-Link or a DFU bootloader instead, upload protocol and IDs both need overriding.
- **USB on the clones is unreliable by design.** The family's usual fault is the wrong D+ pull-up value; SWD, or a USB-serial adapter on PA9/PA10, is the dependable route.
- **BOOT0 and BOOT1 jumpers select the boot source**; BOOT1 is PB2, which is also WeAct's LED pin.
- **No `chips/` entry.** ST's own datasheet and RM0008 reference manual are not in this library — st.com refuses scripted downloads (see `sources.md`).

## Applications

- **Cheap 5 V-tolerant GPIO with real timers.** Three general-purpose timers, SPI, I2C and USART in a board that costs less than its debugger.
- **SWD practice.** The 1 × 4 header takes an ST-Link clone directly, which makes this the board to learn a debugger on.
- **CAN or USB device experiments** on hardware where a failure costs nothing.
- **Unsuitable for:** anything wireless, anything needing more than 20 KB of RAM, and any design that depends on the USB working on an unknown clone.

## Files

- `hardware/weact-bluepill-plus-v11-schematic.pdf`: WeAct Studio's BluePill Plus V1.1 schematic — the closest published design to this family
- `hardware/weact-bluepill-plus-v11-board-shape.pdf`: the same board's outline drawing
- `reference/variant_PILL_F103Cx.h`: the STM32duino variant the board id selects — the authority for the pin table
- `reference/platformio-blackpill_f103c8.json`: the board definition
