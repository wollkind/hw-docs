# WEMOS / LOLIN D1 mini (V4.0.0 USB-C; V3.x Micro-USB)

Small ESP8266EX Wi-Fi board, 34.2 × 25.6 mm, 4 MB flash, CH340C USB-serial. Chip: [../../chips/esp8266](../../chips/esp8266/README.md).
Used by: `pio-blink` (env `d1-mini`); `pio-d1mini` `(not read in this session)`. `MISSION.md` counts six environments with `board = d1_mini` across the owner's projects.

**Which revision the owner has is unconfirmed.** V4.0.0 has a USB-C port and a 4-pin "LOLIN I2C" connector; V3.x has Micro-USB and no I2C connector. D1 mini clones from other sellers are common and may differ from both schematics.

## Key specs

| | |
|---|---|
| SoC | ESP8266EX, Tensilica L106 32-bit, 80/160 MHz, Wi-Fi 2.4 GHz only, no Bluetooth |
| Flash | 4 MB SPI (W25Q32FVSS on V3.0.0; "25Q" 150 mil footprint on V4.0.0) |
| USB | CH340C USB-serial; auto-reset via UMH3N dual transistor on DTR/RTS → RST/GPIO0 |
| Power | USB 5 V → **ME6211** 3.3 V LDO (ME6211C33 on V4). V3.0.0 adds a 0.5 A fuse and a B5819W diode on USB 5 V; V4.0.0 does not show them |
| ADC | one input, A0 → TOUT through a **220 kΩ / 100 kΩ divider**, so A0 accepts up to 3.2 V (WEMOS spec) |
| LED | blue LED on GPIO2 (D4) to 3.3 V: **active low** (1 kΩ on V3.0.0, 2 kΩ on V4.0.0) |
| Buttons | reset only |
| Deep sleep | GPIO16 (D0) → RST solder jumper: SJ1 "Deep_Sleep" on V3.0.0; JP1 with a 470 Ω series resistor on V4.0.0 (open by default) |
| I/O | 11 digital (interrupt/PWM/I2C/one-wire on all but D0), 1 analog. All 3.3 V |

## Pinout

Sources: WEMOS V3.1.0 pin table, V3.0.0 and V4.0.0 schematics, `reference/esp8266-pins_arduino.h`.

| Label | GPIO | Board circuitry | Default role |
|---|---|---|---|
| TX / RX | 1 / 3 | UART0 to CH340C (470 Ω on TX side) | `Serial` |
| A0 | ADC (TOUT) | 220k/100k divider | analog in, 0–3.2 V |
| D0 | 16 | deep-sleep jumper to RST | no interrupt / PWM / I2C |
| D1 | 5 | — | I2C SCL |
| D2 | 4 | — | I2C SDA |
| D3 | 0 | 12 kΩ pull-up (10k per the V3.1.0 page), auto-reset | boot strap |
| D4 | 2 | 12 kΩ pull-up, blue LED | `LED_BUILTIN`, boot strap |
| D5 | 14 | — | SPI SCK |
| D6 | 12 | — | SPI MISO |
| D7 | 13 | — | SPI MOSI |
| D8 | 15 | 12 kΩ pull-down (10k per the V3.1.0 page) | SPI SS, boot strap |
| RST | — | reset button, 100 nF | |
| 5V / 3V3 / G | | USB 5 V / LDO output / ground | |

The V3.1.0 web page states 10 kΩ for the strap resistors; both schematics show 12 kΩ. The schematics are taken as authoritative.

V4.0.0 "LOLIN I2C" connector (SH1.0 4-pin): GND, SDA (GPIO4), SCL (GPIO5), 3V3.

## PlatformIO

As in `pio-blink`:

```ini
[env:d1-mini]
platform = espressif8266
board = d1_mini
framework = arduino
```

Board definition (`reference/platformio-board.json`, "WeMos D1 R2 and mini"): `-DARDUINO_ESP8266_WEMOS_D1MINI`, 80 MHz CPU, DIO flash at 40 MHz, `eagle.flash.4m1m.ld` (4 MB flash, 1 MB filesystem), `resetmethod = nodemcu`, upload 115200. `board_build.f_cpu = 160000000L` selects 160 MHz.

**Verified: builds** on 2026-09-23 (platform espressif8266 4.2.1, Arduino core 3.1.2). Upload not tested.

## Operational notes

- **Boot straps:** GPIO0 (D3), GPIO2 (D4) and GPIO15 (D8) select the boot mode (ESP8266EX datasheet). The board pulls D3/D4 up and D8 down for flash boot. Peripherals that pull D3/D4 low or D8 high at power-up can prevent a normal boot.
- **LED is inverted:** `digitalWrite(LED_BUILTIN, LOW)` turns it on (LED from 3.3 V into GPIO2 in both schematics). The pull-up that keeps GPIO2 high for boot also keeps the LED off at reset.
- **Deep sleep wake needs D0 bridged to RST** (solder jumper). With the bridge, D0 cannot be used as GPIO.
- **A0 is scaled for 0–3.2 V**, not the bare ESP8266 0–1 V range, because of the on-board divider.
- **D0 (GPIO16)** has no interrupt, PWM or I2C support (WEMOS feature list).
- **Wi-Fi only, 2.4 GHz**; the ESP8266 has no Bluetooth and roughly 50 KB of heap in station mode (ESP8266EX datasheet).

## Applications

- **Wi-Fi relay or LED controller** via a D1 mini shield or a MOSFET on D5–D8, controlled over MQTT/HTTP.
- **Deep-sleep sensor** (I2C on D1/D2, or the V4 LOLIN I2C connector) with the D0–RST jumper closed for timed wake.
- **Analog level monitor** on A0 (0–3.2 V) reported over Wi-Fi.
- Unsuitable for Bluetooth, for TLS-heavy workloads (limited heap), or for projects needing more than one ADC channel.

## Files

- `hardware/schematic-v4.0.0.pdf`, `hardware/dimensions-v4.0.0.pdf`: current revision (USB-C)
- `hardware/schematic-v3.0.0.pdf`: V3.0.0 schematic (WEMOS links it from the V3.1.0 page)
- `reference/platformio-board.json`: `d1_mini` board definition (platform-espressif8266)
- `reference/esp8266-pins_arduino.h`: ESP8266 Arduino core `d1_mini` variant
- `wiki/d1-mini.md`, `wiki/d1-mini-v3.1.0.md`: WEMOS product pages
