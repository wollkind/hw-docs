# Arduino Leonardo (A000057)

Uno-format board built on the **ATmega32U4**, whose USB is part of the microcontroller — so the board can present itself as a keyboard, a mouse or a CDC serial port with no second chip. Chip: [`chips/atmega32u4`](../../chips/atmega32u4/README.md).
Used by: `pio-lcd` (`[env:uno]`, which builds `board = leonardo`), and `pio-radio2`, whose env is named `feather32u4` but also builds `board = leonardo` — see Operational notes.

## Key specs

| | |
|---|---|
| Processor | ATmega32U4 at 16 MHz, 5 V logic |
| IO | **20 digital pins**, of which 7 can be PWM and **12 can be analogue inputs** |
| USB | Micro-USB, native to the microcontroller |
| Power | USB, a barrel jack (the product page suggests a 9 V battery), or a battery through the jack |
| Sketch space | 28672 B, with 2560 B RAM (PlatformIO board file) |

Compared with the Uno: more IO, more analogue channels, native USB, less sketch space (the USB bootloader takes more of the flash), and the same shield footprint.

## PlatformIO config

```ini
[env:uno]          ; the env name in pio-lcd; the board is a Leonardo
platform = atmelavr
board = leonardo
framework = arduino
monitor_speed = 115200
```

The board file sets `mcu atmega32u4`, `variant leonardo`, `-DARDUINO_AVR_LEONARDO`, 16 MHz, USB product string "Arduino Leonardo", and uploads over **`avr109` at 57600 with `use_1200bps_touch`, `wait_for_upload_port` and `disable_flushing`** — all four are consequences of the USB being inside the chip.

## Operational notes

- **`Serial` is the USB port; `Serial1` is the TX/RX pins.** This is the difference that breaks Uno sketches moved to a Leonardo: on an Uno both are the same thing.
- **The serial port disappears on reset.** Because the USB device is the sketch, uploading resets it, the port vanishes and a new one appears — hence the 1200-baud touch and the wait-for-port dance in the board file. A sketch that crashes early can make the board hard to program; double-tapping reset holds the bootloader open.
- **`while (!Serial);` blocks forever without a host.** On a battery-powered Leonardo that line hangs the sketch, where on an Uno it returns immediately.
- **`pio-radio2` builds `board = leonardo` for hardware that is a Feather 32u4 RFM69.** Both are ATmega32U4 at 16 MHz, so it compiles and uploads, but the pin map, the LED and the RFM69 chip-select assumptions belong to [the Feather entry](../adafruit-feather-32u4-rfm69/README.md), not to this board. `board = feather32u4` is the correct profile there.
- **12 analogue inputs, not 6**, and six of them are digital pins under another name. From the Arduino core's `leonardo` variant: **A6 = D4, A7 = D6, A8 = D8, A9 = D9, A10 = D10, A11 = D12**. Using one as an analogue input takes the digital pin with it.
- **5 V logic**, with the same level-shifting caveat as the Uno.

## Applications

- **USB HID device.** Keyboard and mouse emulation is the reason this board exists; Arduino ships `Keyboard` and `Mouse` libraries for it.
- **Shield host with more analogue channels** than an Uno.
- **Serial bridge**, using the USB CDC port and the hardware UART at the same time — something an Uno cannot do.
- **Unsuitable for:** anything wireless, sketches over 28 KB, and code that assumes `Serial` reaches the TX pin.

## Files

- `wiki/product-page.md`: Arduino's product page (features, tech-spec summary; the base64 images were stripped)
- `hardware/leonardo-schematic.pdf`, `hardware/leonardo-pinout.pdf`
- `reference/platformio-leonardo.json`: the `leonardo` board definition
- `reference/pins_arduino.h`: the Arduino AVR core's `leonardo` variant — the authority for the A6–A11 mapping
