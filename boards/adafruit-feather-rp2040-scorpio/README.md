# Adafruit Feather RP2040 SCORPIO (PID 5650)

Feather-format RP2040 board built for driving NeoPixels: 8 consecutive GPIOs (16–23) go through a 74AHCT245 level shifter to eight 5 V outputs, fed by the RP2040's PIO and DMA. Chip: RP2040 — no `chips/rp2040` entry yet.
Used by: no project found.

## Key specs

| | |
|---|---|
| MCU | RP2040, dual Cortex-M0+, 264 KB SRAM, 12 MHz crystal |
| Flash | 8 MB QSPI (CircuitPython builds for GD25Q64C / W25Q64JVxQ) |
| USB | USB-C, native RP2040 USB. CircuitPython VID:PID 0x239A:0x8122; Arduino core reports 0x239A:0x8121 |
| 8× outputs | GPIO16–23 → 74AHCT245 (`/OE` tied low, always enabled) → 100 Ω series resistors → pads NEOPIXEL0–7 |
| Shifter rail | solder jumper **SJ1** picks the '245 VCC: 3.3 V or VHI (the USB/battery rail, 5 V on USB) |
| Shifter direction | solder jumper **SJ2** drives the '245 `T/R` pin between 3.3 V and GND, so the eight pads can be flipped to inputs |
| Power | USB-C 5 V or JST-PH 3.7 V LiPo, MBR540 + DMG341 P-FET switchover, AP2112-3.3 LDO |
| Charger | MCP73831T-2ACI/OT with a 5.1 kΩ PROG resistor ⇒ ≈200 mA charge `(current derived from the resistor, MCP73831 datasheet not fetched)`; orange CHG LED |
| Onboard | status WS2812B/SK6805 NeoPixel, red LED, reset and BOOT buttons, STEMMA QT / Qwiic I2C connector |

## Pinout

| Function | GPIO |
|---|---|
| NEOPIXEL0–7 (level-shifted outputs) | 16, 17, 18, 19, 20, 21, 22, 23 |
| Status NeoPixel | 4 — **also brought out as header pin D4** |
| Red LED | 13 |
| BOOT button | 7 |
| I2C SDA / SCL (STEMMA QT and header) | 2 / 3 |
| SPI SCK / MOSI / MISO | 14 / 15 / 8 |
| UART TX / RX (D1 / D0) | 0 / 1 |
| A0–A3 | 26, 27, 28, 29 |
| D5, D6, D9–D13, D24, D25 | 5, 6, 9, 10, 11, 12, 13, 24, 25 |

Feather pin names map straight onto GPIO numbers everywhere except the analog pads and D0/D1.

## Toolchain

Arduino, with the arduino-pico core (`earlephilhower`): board id **`adafruit_feather_scorpio`**; `PIN_NEOPIXEL0`…`PIN_NEOPIXEL7` and `PIN_NEOPIXEL` (4) are predefined. The matching PlatformIO entry was not confirmed — the board JSON was not found at the paths tried, so check `pio boards scorpio` before trusting a `board =` line `(unverified)`.

CircuitPython: `board.NEOPIXEL0`…`NEOPIXEL7`, `board.NEOPIXEL`, `board.STEMMA_I2C()`.

## Gotchas

- **The status NeoPixel sits on GPIO4, which is also the D4 header pad.** Anything wired to D4 fights the onboard pixel.
- **Outputs are 5 V only if SJ1 says so.** The shifter's supply comes from that jumper; with it on the 3.3 V side the eight outputs swing 3.3 V. Factory default position is not documented here `(unverified)` — check the bottom of the board.
- **The 8 outputs can be made inputs** by moving SJ2 (T/R), which is how the board doubles as an 8-channel 5 V input. Both jumpers are on the underside.
- **100 Ω in series on every output** — already the resistor NeoPixel strips usually want, so don't add another.
- **Only GPIO16–23 are contiguous.** PIO programs that assume a run of pins must start at 16; other Feather pads are scattered.
- **VHI, not VBUS, feeds the LDO and the shifter jumper**: VHI is whichever of USB 5 V or battery is higher, so on battery the "5 V" outputs are the battery voltage.

## Files

- `hardware/eagle.sch`, `hardware/eagle.brd`: Adafruit's EagleCAD source for the board
- `reference/cpy-pins.c`, `cpy-mpconfigboard.h`, `cpy-mpconfigboard.mk`: the CircuitPython board definition (pin names, default buses, flash parts, USB ids)
- `reference/arduino-pico-pins_arduino.h`: the arduino-pico variant header
