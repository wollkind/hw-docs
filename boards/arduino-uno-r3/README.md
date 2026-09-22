# Arduino Uno R3 (A000066)

The reference Arduino: an ATmega328P at 16 MHz with 5 V logic, a separate ATmega16U2 as the USB bridge, and the shield header every Arduino-format board copies. Chip: [`chips/atmega328p`](../../chips/atmega328p/README.md).
Used by: `pio-lcd2`, `pio-feather` (`[env:uno]`).

## Key specs

| | |
|---|---|
| Processor | ATmega328P, 8-bit AVR up to 16 MHz — 32 KB flash, 2 KB SRAM, 1 KB EEPROM |
| USB bridge | **ATmega16U2**, itself an 8-bit AVR with 16 KB ISP flash, 512 B EEPROM, 512 B SRAM, 2.7–5.5 V, debugWIRE |
| IO | 14 digital (6 PWM), 6 analogue inputs |
| Power in | VIN 6–20 V, or 5 V from USB (USB maximum 5.5 V) |
| Temperature | −40 °C to 85 °C as a conservative board limit. Arduino warns that at the extremes the EEPROM, the regulator and the crystal may misbehave |
| Sketch space | 32256 B, with 2048 B RAM (PlatformIO board file) |

## Pinout

From the datasheet's connector tables.

### JANALOG

| Pin | Name | Notes |
|---|---|---|
| 1 | NC | |
| 2 | IOREF | Logic reference, tied to 5 V |
| 3 | Reset | |
| 4 | +3V3 | 3.3 V rail |
| 5 | +5V | 5 V rail |
| 6, 7 | GND | |
| 8 | VIN | Voltage input |
| 9–12 | A0–A3 | Analogue in or GPIO |
| 13 | A4 / SDA | Analogue in or **I2C data** |
| 14 | A5 / SCL | Analogue in or **I2C clock** |

### JDIGITAL

| Pin | Name | Notes |
|---|---|---|
| 1–10 | D0–D9 | D0 and D1 are also the UART |
| 11 | SS | SPI chip select |
| 12 | MOSI | |
| 13 | MISO | |
| 14 | SCK | |
| 15 | GND | |
| 16 | AREF | Analogue reference |
| 17, 18 | A4 / A5 | **Duplicates** of the I2C pins on JANALOG |

## PlatformIO config

`pio-lcd2` and `pio-feather` build it as:

```ini
[env:uno]
platform = atmelavr
board = uno
framework = arduino
monitor_speed = 115200
```

The board file sets `mcu atmega328p`, `variant standard`, `-DARDUINO_AVR_UNO`, 16 MHz, and uploads with the `arduino` protocol at 115200. Maximum sketch 32256 B, RAM 2048 B.

## Operational notes

- **A4/A5 appear twice on the headers** and are the same two pins. An I2C device and an analogue sensor cannot share them.
- **2 KB of SRAM is the real constraint.** A few `String` objects or a large `char` buffer exhaust it, and the failure mode is silent corruption rather than a compile error. Keep constant text in flash with `F()`.
- **The USB bridge is a second microcontroller.** The sketch's `Serial` goes through the ATmega16U2; resetting the board does not drop the USB connection the way a native-USB board does.
- **5 V logic.** Every 3.3 V board in this library needs level shifting or a divider to talk to an Uno — including the [D1 mini](../wemos-d1-mini/README.md) and every ESP32 board here.
- **VIN accepts 6–20 V** but the linear regulator turns the difference into heat; near 20 V with any real load it will get hot.

## Applications

- **5 V shield host.** The header exists so shields plug in; the board's own value is the footprint.
- **Teaching and bring-up**, which is what `pio-lcd2` uses it for — a `LiquidCrystal` character display and nothing else.
- **Long-lived fixed-function controller.** An AVR at 16 MHz with no radio is predictable, which is why the datasheet notes industrial PLC use.
- **Unsuitable for:** anything wireless, anything needing more than 2 KB of RAM, USB HID, or 3.3 V sensors wired directly.

## Files

- `hardware/uno-rev3-datasheet.pdf`: Arduino's board datasheet, including the connector tables above
- `hardware/uno-rev3-schematic.pdf`, `hardware/uno-rev3-pinout.pdf`
- `reference/platformio-uno.json`: the `uno` board definition
