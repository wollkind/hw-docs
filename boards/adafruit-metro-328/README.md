# Adafruit METRO 328 (PID 2466)

Adafruit's Uno-format ATmega328 board: same shield footprint and same processor, with a CP2104 USB bridge, a DC jack with a power switch, and a solder jumper that moves the logic level to 3.3 V. Chip: [`chips/atmega328p`](../../chips/atmega328p/README.md).
Used by: `pio-bme280` (`[env:metro]`).

## Key specs

From Adafruit's description in the PCB repository:

| | |
|---|---|
| Processor | ATmega328 at 16 MHz. 32 KB flash, of which 512 B is the **Optiboot** bootloader; 2 KB RAM |
| Power | 7–9 V polarity-protected DC on a 2.1 mm jack **with an on/off switch**, or 5 V over micro-USB. The board switches between them automatically |
| IO | 20 GPIO, 6 of them analogue inputs, **2 reserved for the USB-serial converter**. Six PWM outputs across three timers (one 16-bit, two 8-bit) |
| Buses | hardware SPI, hardware I2C, hardware UART wired to USB |
| **Logic level** | **5 V by default; cutting one jumper and soldering another moves it to 3.3 V** |
| LEDs | four on the front edge: green power, RX and TX, and a red LED on **PB5** (Arduino pin 13) |
| USB bridge | CP2104 on the Rev C design |
| Shields | Adafruit's own description: works with all Adafruit-designed shields |

Sold without headers or the DC jack fitted; the parts are in the bag.

## PlatformIO config

`pio-bme280` builds it as:

```ini
[env:metro]
platform = atmelavr
board = metro
framework = arduino
```

The board file sets `mcu atmega328p`, `variant standard`, `-DARDUINO_AVR_METRO`, 16 MHz, upload protocol `arduino` at 115200, maximum sketch 32256 B, RAM 2048 B — the same numbers as the `uno` profile, with a different `ARDUINO_AVR_*` define. The two are interchangeable in practice; the define is what a library uses to tell the boards apart.

## Operational notes

- **The 3.3 V jumper is the feature the Uno does not have.** A [D1 mini](../wemos-d1-mini/README.md), an ESP32 board or any 3.3 V sensor can share a bus with a Metro set to 3.3 V logic, with no level shifter. Switch it before wiring, and remember that a shield expecting 5 V will then be out of spec.
- **Two of the 20 GPIO belong to the USB bridge**, as on any Uno-format board — D0 and D1.
- **Optiboot leaves more flash for the sketch** than the older Uno bootloader: 512 B rather than 2 KB, which is why the PlatformIO maximum is 32256 B.
- **The DC jack has a switch.** Unlike an Uno, the board can be left wired and turned off.
- **2 KB of SRAM**, with the same caution as the Uno: keep strings in flash with `F()`.
- The repository also holds the **Metro Mini** designs (Rev A, Rev B and a V2 with STEMMA QT). Those are a different, smaller board; only the full-size Metro files are copied here.

## Applications

- **Mixed-voltage prototyping.** The 3.3 V jumper makes this the AVR to reach for when the sensors are 3.3 V — which, in this library, is all of them.
- **Shield host** with a switched DC input for bench work.
- **Sensor logging**, as `pio-bme280` uses it — a BME280 read over hardware I2C.
- **Unsuitable for:** anything wireless or USB-HID, and sketches over ~32 KB.

## Files

- `hardware/schematic-revc-cp2104.pdf`: the Rev C (CP2104) schematic
- `hardware/eagle-revc-cp2104.sch`, `.brd`: the same design in EAGLE
- `hardware/pinout.pdf`: Adafruit's Metro 328P pinout diagram
- `reference/platformio-metro.json`: the `metro` board definition
- `reference/pcb-repo-readme.md`: Adafruit's own description of the board, the source for the specs table above
