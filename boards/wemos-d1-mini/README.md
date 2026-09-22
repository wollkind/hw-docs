# WEMOS LOLIN D1 mini (ESP8266)

34.2 × 25.6 mm ESP8266EX board with 4 MB flash, a CH340C USB-serial bridge and a LOLIN 4-pin I2C connector. Chip: [`chips/esp8266`](../../chips/esp8266/README.md).
Used by: `pio-d1mini`, `pio-d12`, `pio-bme280` (`[env:d1_mini]`), `pio-bme680` (`[env:d1_mini]`), `pio-feather` (`[env:d1mini]`), `pio-blink` (`[env:d1-mini]`) — the six `d1_mini` environments the bulk pass counted.

## Revisions

The vendor page lists V4.0.0 (current), V3.1.0, V3.0.0, V2.3.0 and V2.2.0. Only two differences are documented by WEMOS:

| | V4.0.0 | V3.1.0 and earlier |
|---|---|---|
| USB connector | Type-C | Micro USB |
| I2C connector | "LOLIN I2C Port" (SH1.0 4-pin, `P1` in the schematic) | not listed |

Everything else in the feature list — 11 digital IO, 1 analog input, 4 MB flash, 3.3 V IO — is identical across the two pages. Both revisions use the same PlatformIO board id and the same pin names.

## Key specs

| | |
|---|---|
| MCU | ESP8266EX, 80/160 MHz |
| Flash | 4 MB (`25Q-150MIL` part on the V4 schematic). PlatformIO builds it `dio` at 40 MHz with the `eagle.flash.4m1m.ld` layout: ~1019 KB sketch, ~2052 KB unused, 1000 KB filesystem, then EEPROM, rfcal and Wi-Fi config |
| RAM | `maximum_ram_size` 81920 bytes in the PlatformIO board file |
| USB-serial | CH340C (V4 schematic). Needs the CH340 driver on the host |
| Auto-reset | `UMH3N` dual digital transistor driving RST/GPIO0 from DTR/RTS; PlatformIO calls this `resetmethod: nodemcu` |
| Regulator | ME6211C33, 3.3 V |
| Crystal | 26 MHz |
| Antenna | PCB trace antenna (`ANT_PCB_2.4G_15.2MM_F`) |
| USB-C | 5.1 kΩ CC resistors (`R1`, `R2`) — a plain C-to-C cable supplies it |
| IO | 11 digital, 1 analog. **All IO run at 3.3 V** |
| Analog in | A0, 3.2 V maximum (board divider ahead of the chip's TOUT pin) |
| Size / weight | 34.2 × 25.6 mm, 3 g |

## Pinout

From the WEMOS V3.1.0 pin table, confirmed against `variants/d1_mini/pins_arduino.h` in the ESP8266 Arduino core. Both agree on every pin.

| Header pin | GPIO | Function | Pull on the board |
|---|---|---|---|
| TX | 1 | UART0 TX | |
| RX | 3 | UART0 RX | |
| A0 | — | Analog input, 3.2 V max | |
| D0 | 16 | IO. **No interrupt, PWM, I2C or one-wire** — the vendor feature list excludes D0 | |
| D1 | 5 | IO, **SCL** | |
| D2 | 4 | IO, **SDA** | |
| D3 | 0 | IO | pull-up |
| D4 | 2 | IO, `LED_BUILTIN` | pull-up |
| D5 | 14 | IO, SCK | |
| D6 | 12 | IO, MISO | |
| D7 | 13 | IO, MOSI | |
| D8 | 15 | IO, SS | pull-down |
| G | — | Ground | |
| 5V | — | 5 V; the `VBUS` net on the schematic, so it is the USB supply, not a regulated output | |
| 3V3 | — | 3.3 V rail | |

The pull values disagree between the sources: the V3.1.0 pin table calls all three 10 kΩ, the V4.0.0 schematic fits 12 kΩ parts (the board carries six 12 kΩ resistors; which designator sits on which net does not survive text extraction). Treat the V4 schematic as authoritative for a V4 board.

The LOLIN I2C connector `P1` (V4) is an SH1.0 4-pin part carrying SDA, SCL and +3V3 on pins 1–3. The fourth pin's net label does not extract cleanly from the schematic PDF *(unverified — read it off the board or the PDF by eye before wiring)*.

## PlatformIO config

Verified in `pio-d1mini`, `pio-d12`, `pio-bme280`, `pio-bme680`, `pio-feather` and `pio-blink`, all of which build this board with nothing beyond:

```ini
[env:d1_mini]
platform = espressif8266
board = d1_mini
framework = arduino
monitor_speed = 115200
```

The board file is named "WeMos D1 R2 and mini" — one definition covers the D1 mini and the larger D1 R2, so the id alone does not tell the two apart. It sets `-DARDUINO_ESP8266_WEMOS_D1MINI`, `f_cpu 80 MHz`, `f_flash 40 MHz`, `flash_mode dio`, upload speed 115200 and `resetmethod nodemcu`. To run the core at 160 MHz, add `board_build.f_cpu = 160000000L`.

## Operational notes

- **D0 (GPIO16) is not a general-purpose pin.** The vendor feature list says interrupt, PWM, I2C and one-wire are supported on every digital IO "except D0". It is the chip's XPD_DCDC pin, and wiring it to RST is what makes a timed deep-sleep wakeup possible.
- **D3, D4 and D8 carry the boot straps** (GPIO0, GPIO2, GPIO15), which is why they have fixed pulls. A device held on D8 at reset, or one that sinks D3/D4 low, stops the board from booting. Put switches and open-drain devices elsewhere.
- **D4 also drives the onboard LED** (`LED_BUILTIN` in the variant header). A sketch that leaves the pin as an output fights anything else on D4. The LED's polarity is not readable from the schematic PDF's text layer *(unverified — ESP8266 boards are usually active-low)*.
- **`pio-d12` drives GPIO5 (D1) as a "done" output** (`#define DONEPIN 5`) while the same sketch talks to an MPL115A2 and a BME280 over `Wire`, whose default pins on this variant are SDA GPIO4 / SCL GPIO5. GPIO5 is therefore both the I2C clock and a hard-driven output in that project. It is not a board fault, but it is a bug waiting in that project, and any board wired from it inherits the conflict.
- **A0 is a single 10-bit input with a divider in front of it.** 3.2 V is the board's limit, not the chip's; the ESP8266EX reads either TOUT or its own supply, never both, so an application cannot read the battery voltage and an external sensor on the same pin.
- **No Bluetooth, no USB device mode.** Everything goes over Wi-Fi or the CH340 serial bridge.

## Applications

- **Mains-adjacent or battery Wi-Fi sensor node.** The I2C connector and the 3.3 V rail drive a BME280/BME680 directly, which is what `pio-bme280`, `pio-bme680` and `pio-d1mini` do.
- **Deep-sleep logger.** Wiring D0 to RST gives timed wakeups at the chip's 20 µA deep-sleep current; `pio-d12` instead hands the wakeup job to an external timer and pulses a done pin.
- **Wi-Fi bridge for a 3.3 V SPI peripheral.** D5–D8 are the hardware SPI bus.
- **Unsuitable for:** anything needing BLE, USB HID, more than one analog channel, or a 5 V-tolerant input.

## Files

- `wiki/d1-mini.md`, `wiki/d1-mini-v3.1.0.md`: the two vendor pages, with images
- `hardware/schematic-v4.0.0.pdf`, `hardware/dimensions-v4.0.0.pdf`: V4.0.0 KiCad schematic and mechanical drawing
- `hardware/schematic-v3.0.0.pdf`: the V3 schematic (vendor links it from the V3.1.0 page)
- `reference/platformio-d1_mini.json`: the `d1_mini` board definition the projects build against
- `reference/pins_arduino.h`: the ESP8266 Arduino core's `d1_mini` variant
- `reference/eagle.flash.4m1m.ld`: the flash layout that board file selects
