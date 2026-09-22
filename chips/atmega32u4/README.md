# Microchip (Atmel) ATmega16U4 / ATmega32U4

8-bit AVR with a **full-speed USB device controller on the die**, which is what lets a board enumerate as a keyboard, mouse or CDC serial port with no second chip. 16 MHz at 5 V.

- `atmega16u4-32u4-datasheet.pdf`: Atmel's datasheet for both parts.

| | ATmega16U4 | ATmega32U4 |
|---|---|---|
| Flash | 16 KB | **32 KB** |
| SRAM | 1.25 KB | **2.5 KB** |
| EEPROM | 512 B | **1 KB** |

The boards in this library carry the 32U4.

## Why this part matters here

- **Native USB.** The Leonardo, the Feather 32u4 and the Micro all rely on it; an Uno instead uses a separate ATmega16U2 as a USB-to-serial bridge.
- **The USB stack lives in the sketch.** Resetting the board resets the USB device, so the serial port disappears and reappears across an upload. Tools handle this with a 1200-baud touch to trigger the bootloader.
- **`Serial` and `Serial1` are different things.** `Serial` is the USB CDC port; `Serial1` is the hardware UART on the pins. Code moved from an Uno that expects `Serial` on the TX/RX pins will talk to the wrong one.

Boards: [arduino-leonardo](../../boards/arduino-leonardo/README.md), [adafruit-feather-32u4-rfm69](../../boards/adafruit-feather-32u4-rfm69/README.md)
