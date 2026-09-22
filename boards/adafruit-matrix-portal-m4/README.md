# Adafruit MatrixPortal M4 (PID 4745)

A HUB75 controller that plugs straight onto the back of an RGB matrix. It has an ATSAMD51 MCU, an ESP32 Wi-Fi coprocessor and a LIS3DH accelerometer. Chip docs: [../../chips/atsamd51](../../chips/atsamd51/README.md).
Used by: `sandpanel` (64×32 panel, Protomatter).

## Key specs

| | |
|---|---|
| MCU | ATSAMD51J19, Cortex-M4 @ 120 MHz, 512 KB flash, 192 KB RAM, 3.3 V |
| Extra flash | 2 MB QSPI |
| Wi-Fi | ESP32 coprocessor (AirLift/NINA over SPI): CS = D33, BUSY = D31, RESET = D30 |
| Accelerometer | LIS3DH on I2C at **0x19** (not the library default 0x18) |
| USB | USB-C, native SAMD51. UF2 bootloader: double-tap reset |
| Power | USB-C 5 V supplies both the board and the matrix. 3V pin: 500 mA peak |
| Connectors | HUB75 2×8 (in a 2×10 shroud), +5V/GND M3 screw terminals, STEMMA QT I2C, 3-pin JST A0 |
| Buttons | Reset; UP = D2, DOWN = D3 (active low, **no pull-ups on the board**) |
| LEDs | status NeoPixel D4, red LED D13 |

## Pinout

HUB75 in Protomatter (Arduino pin numbers; from Adafruit's pixeldust example, as used in `sandpanel`):

| Signal | Pins |
|---|---|
| RGB (R1 G1 B1 R2 G2 B2) | 7, 8, 9, 10, 11, 12 |
| Address A–E | 17, 18, 19, 20, 21 (A–D for 32 rows, plus E for 64 rows) |
| CLK / LAT / OE | 14 / 15 / 16 |

Other pins: TX = D1, RX = D0, A0 (JST), A1–A4 along the bottom edge, SWD pads for debugging.

## PlatformIO (verified builds in sandpanel)

```ini
platform = atmelsam
board = adafruit_matrix_portal_m4
framework = arduino
lib_deps = adafruit/Adafruit Protomatter, adafruit/Adafruit LIS3DH, adafruit/Adafruit Unified Sensor
```

## Operational notes

- **LIS3DH address:** the address is **0x19** because SDO/SA0 is tied high. At 0x18, `begin()` fails and `setup()` hangs. Use `lis.begin(0x19)`.
- **Wrong HUB75 pin map:** gives a dark or garbled panel with no error. `sandpanel` guards against this with `_VARIANT_MATRIXPORTAL_M4_` and `#error`.
- **64×64 panels:** these need the Address-E solder jumper. Bridge the middle pad to **8** for Adafruit 64×64 panels; panels from other sources may need **16**, so check the panel datasheet.
- **Screw terminals are outputs only.** Powering the board through them while USB is plugged in can cause damage. For big panels, power the panel directly.
- **Buttons:** UP/DOWN need `INPUT_PULLUP`.
- **Bootloader:** double-tap reset for the UF2 drive (MATRIXBOOT).

## Applications

- **Networked information panel.** The ESP32 coprocessor supplies Wi-Fi for time and data; Protomatter drives a 64×32 or 64×64 HUB75 panel. Power the panel separately from the screw terminals for panels above 64×32.
- **Motion-reactive display.** The LIS3DH at 0x19 provides tilt and shake input. The `sandpanel` project uses this.

## Files

- `wiki/`: Adafruit Learn guide pages (overview, pinouts, prep, USB power, Arduino IDE, Protomatter library, downloads) with images, including the schematic and fab-print PNGs
- `hardware/pinout.pdf`, `hardware/eagle.sch`, `hardware/eagle.brd`
- `firmware/simpletest-64x32.uf2`, `firmware/simpletest-64x64.uf2`: known-good panel tests (drag them onto the UF2 drive)
