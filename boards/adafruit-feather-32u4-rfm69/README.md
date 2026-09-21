# Adafruit Feather 32u4 RFM69HCW (RadioFruit, PID 3076 / 3077)

ATmega32U4 Feather with an RFM69HCW packet radio on board. The same PCB carries the RFM9x LoRa variants, so the pinout files cover both.
Used by: `pio-radio`, `pio-radio1`, `pio-radio2` — all three run RadioHead's `RH_RF69` at **915 MHz**, which is the 868/915 MHz SKU (PID 3076).

## Key specs

| | |
|---|---|
| MCU | ATmega32U4-MU, 8 MHz resonator, 3.3 V logic |
| Radio | RFM69HCW (868/915 MHz = PID 3076, 433 MHz = PID 3077); the same board is sold with RFM95/RFM96 LoRa as PID 3078/3079 |
| USB | micro-USB, native 32U4 USB |
| Power | USB 5 V or JST-PH LiPo; AP2112-3.3 LDO, MBR120 schottky, MCP73831 charger with orange CHG LED |
| Antenna | U.FL connector **and** a wire-antenna pad |
| Other | red LED on D13, reset button, ICSP header |

## Radio pinout (read from the schematic)

| Signal | Feather pin | 32U4 port |
|---|---|---|
| NSS / CS | **D8** | PB4 (ADC11) |
| DIO0 / IRQ | **D7** | PE6 (INT6/AIN0) |
| RESET | **D4** | PD4 (ICP1/ADC8) |
| SCK | SCK | PB1 |
| MOSI | MOSI | PB2 |
| MISO | MISO | PB3 |

DIO1, DIO2 and DIO3 are brought out to header pads rather than wired to fixed pins; DIO5 is unconnected. SPI is the hardware SPI, shared with the ICSP header.

The owner's three projects all use exactly this:

```cpp
#define RFM69_CS   8
#define RFM69_INT  7
#define RFM69_RST  4
#define RF69_FREQ  915.0
RH_RF69 rf69(RFM69_CS, RFM69_INT);
```

## PlatformIO (as used in the owner's projects)

```ini
[env:feather32u4]
platform = atmelavr
board = feather32u4
framework = arduino
lib_deps = mikem/RadioHead@^1.120     ; pio-radio uses epsilonrt/RadioHead@^1.122.1
```

**`pio-radio2` sets `board = leonardo` inside an env still named `feather32u4`.** Both are ATmega32U4 at 8 MHz, so it builds and runs, but the board profile differs (USB VID/PID and the bootloader description), so uploads and USB identification behave like a Leonardo. Worth correcting to `feather32u4` unless that was deliberate.

## Gotchas

- **Reset the radio at boot.** Adafruit's example, which all three projects copy, pulses `RFM69_RST` high for ~10 ms then low before `rf69.init()`; skipping it leaves the module in an undefined state after a brown-out.
- **915 MHz vs 433 MHz is a hardware difference.** `RF69_FREQ` must match the module fitted; the wrong value passes `init()` and then transmits nothing usable.
- **Antenna required before transmit** — the U.FL socket or a quarter-wave wire on the antenna pad.
- **D4/D7/D8 are taken** by the radio and are not free for user I/O.
- **32U4 USB serial drops on reset:** the port disappears while the sketch restarts, which makes `monitor` reconnect races common with PlatformIO.
- **Only 2.5 KB RAM.** RadioHead's 60-byte buffers plus a display library is already tight; `pio-radio2` drives a Waveshare 2.13" e-paper and an HDC302x from the same 32U4.

## Files

- `hardware/eagle.sch`, `hardware/eagle.brd`: the shared RFMxx PCB source
- `hardware/pinout-rfm69.pdf`, `hardware/pinout-rfm9x.pdf`: Adafruit's pinout diagrams for both radio fits
