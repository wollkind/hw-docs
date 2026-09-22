# Adafruit Feather HUZZAH ESP8266 (PID 2821)

Feather-format ESP8266 board: ESP-12 module, CP2104 USB-serial, LiPo charger and a 3.3 V regulator. Chip: [`chips/esp8266`](../../chips/esp8266/README.md).
Used by: `pio-huzzah`, `pio-radio` (`[env:huzzah]`) — the two `huzzah` environments in the bulk pass.

**Which Adafruit ESP8266 board this is.** PlatformIO has one id, `huzzah`, and its board file is named "Adafruit HUZZAH ESP8266" with `url` pointing at product **2471**, the non-Feather breakout. Both boards carry the same ESP-12 module and build against the same `adafruit` Arduino variant, so the id works for either. `pio-huzzah` drives an ILI9341 TFT **FeatherWing** and uses Adafruit's ESP8266 FeatherWing pin block (`TFT_CS 0`, `TFT_DC 15`, `SD_CS 2`, `STMPE_CS 16`), which only makes sense on a Feather — so this entry documents the Feather HUZZAH (2821). If the board in hand turns out to be the 2471 breakout, the pinout below is wrong about the power pins and the LEDs, and nothing else.

## Key specs

| | |
|---|---|
| Module | ESP-12 (ESP8266 @ 80 MHz, 160 MHz selectable, 3.3 V logic) |
| Flash | 4 MB (32 Mbit). PlatformIO builds it **`qio`** at 40 MHz with `eagle.flash.4m1m.ld` |
| RAM | `maximum_ram_size` 81920 bytes in the PlatformIO board file |
| USB-serial | CP2104, uploads at up to 921600 baud, with auto-reset |
| Regulator | AP2112K-3.3, 500 mA peak — Adafruit advises staying under 250 mA of load so the ESP8266 keeps its headroom |
| Battery | JST-PH 2-pin, MCP73831/2 charger at **100 mA**, CHG status LED; Schottky + P-MOSFET switch to USB when it is present |
| GPIO | 9: 0, 2, 4, 5, 12, 13, 14, 15, 16. **12 mA maximum per pin**, none of them 5 V tolerant |
| Analog | One input, **1.0 V maximum** — no divider on this board |
| LEDs | Red on GPIO0 (`LED_BUILTIN` in the `adafruit` variant, reverse wired: LOW turns it on), blue on GPIO2 near the antenna |
| Size | 51 × 23 × 8 mm without headers, 6 g, 4 mounting holes |

## Pinout

From the Learn guide's Pinouts page; the Rev G EAGLE schematic in `hardware/` is the design of record.

| Pin | GPIO | Notes |
|---|---|---|
| RX | 3 | **5 V compliant** — there is a level shifter on this pin |
| TX | 1 | 3.3 V output |
| SDA | 4 | I2C data (default) |
| SCL | 5 | I2C clock (default) |
| SCK | 14 | Hardware SPI clock |
| MOSI | 13 | |
| MISO | 12 | |
| #0 | 0 | Boot mode select, **no internal pull-up**, red LED (active low) |
| #2 | 2 | Boot mode select, pull-up fitted, blue LED |
| #15 | 15 | Boot mode select, pull-down fitted — must not be pulled high at startup |
| #16 | 16 | Deep-sleep wakeup; wire it to RST to use timed wakeups |
| A | — | Analog in, 1.0 V max |

Power and control pins: **GND**, **BAT** (JST jack), **USB** (micro-USB jack), **EN** (3.3 V regulator enable, pulled up — ground it to shut the regulator off), **3V** (regulator output), **RST** (pulled up, momentary to ground resets). Every other pad on the Feather footprint is **NC**, fitted only so the board matches the rest of the Feather line.

RX and TX run through to the CP2104, so anything wired to them also sees the USB traffic.

## PlatformIO config

Verified in `pio-huzzah` and `pio-radio`:

```ini
[env:huzzah]
platform = espressif8266
board = huzzah
framework = arduino
monitor_speed = 115200
```

The board file sets `-DARDUINO_ESP8266_ADAFRUIT_HUZZAH`, `flash_mode qio` (the D1 mini uses `dio`), `f_cpu` 80 MHz, upload speed 115200 and `resetmethod nodemcu`. The CP2104 will take 921600 for uploads — `upload_speed = 921600` is the change to make if flashing time matters. 160 MHz needs `board_build.f_cpu = 160000000L`.

## Operational notes

- **The analog pin tops out at 1.0 V, not 3.2 V.** This is the one place where a sketch written for a D1 mini will read wrong, or damage the input, when moved to this board: the D1 mini has a divider in front of the chip's TOUT pin and this board does not. Divide externally.
- **12 mA per GPIO.** That is Adafruit's stated limit. Drive a relay or an LED string through a transistor.
- **GPIO0, 2 and 15 are the boot straps** and carry the fitted pulls named above. GPIO0 has no internal pull-up, so anything that can sink it low at power-up puts the board into the bootloader instead of the sketch.
- **GPIO16 is the only deep-sleep wakeup path**, and only when it is strapped to RST.
- **The charger is fixed at 100 mA.** A large LiPo takes a long time; a very small one should not be left on it.
- **`EN` grounds the regulator, not the ESP8266.** `RST` and the ESP8266's own `EN (CH_PD)` are different pins on the header, both pulled up.
- Only 9 GPIO are brought out, and three of them are boot straps — this board runs out of pins before most ESP32 Feathers do.

## Applications

- **Wi-Fi Feather host for a FeatherWing stack.** `pio-huzzah` runs an ILI9341 TFT FeatherWing with a TSC2007 touch controller on it.
- **Battery-powered I2C sensor node.** JST jack, onboard charger, SDA/SCL on fixed pins; `pio-huzzah` reads an HDC302x and an INA228 this way.
- **Deep-sleep telemetry** with GPIO16 wired to RST, at the ESP8266's 20 µA sleep current.
- **Unsuitable for:** BLE, USB device work, anything needing more than 9 GPIO or an analog input above 1.0 V, and high-current outputs driven straight from a pin.

## Files

- `wiki/overview.md`, `wiki/pinouts.md`, `wiki/downloads.md`: the Learn guide pages, with images
- `hardware/eagle-revg.sch`, `hardware/eagle-revg.brd`: Adafruit's Rev G design
- `hardware/pinout-v1.2.pdf`: Adafruit's pinout diagram
- `hardware/cp2104-datasheet.pdf`: the USB-serial bridge
- `reference/platformio-huzzah.json`: the `huzzah` board definition the projects build against
- `reference/pins_arduino.h`: the ESP8266 Arduino core's `adafruit` variant (SDA 4, SCL 5, `LED_BUILTIN` 0)
