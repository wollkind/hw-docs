# GC9A01 1.28" round LCD module, 240×240 (HiLetgo and clones)

Generic round TFT breakout: a 1.28" 240×240 panel driven by a GC9A01A, 3.3 V, 4-wire SPI. Sold by HiLetgo, Waveshare and many others with the same panel and driver; there is no vendor wiki for the HiLetgo version.
Used by: no project found.

## Key specs (GC9A01A datasheet Rev 1.0, 2019-07-02)

| | |
|---|---|
| Controller | GC9A01A, single-chip a-Si TFT driver, 360 source × 32 gate outputs |
| Resolution | 240 RGB × 240, full 262 144 colours (idle mode drops to 8 colours) |
| Frame RAM | 129 600 bytes on-chip GRAM — the whole frame, so no external buffer needed |
| Interfaces (chip) | 8/9/12/16/18-bit 8080-I/II parallel, 6/12/16/18-bit RGB, 3-line and 4-line SPI, 2-data-lane SPI. **Modules wire up 4-line SPI.** |
| Logic supply | IOVCC 1.65–3.3 V |
| Analog supply | VCI 2.5–3.3 V |
| Gate drive (internal) | VGH 12.0–13.0 V, VGL −11.0 to −8.0 V, VGH − VGL ≤ 27 V; VCOM to GND |
| Operating temperature | −40 °C to 80 °C |
| SPI write timing | clock cycle ≥ 10 ns (≈100 MHz), SCL high/low ≥ 5 ns, CS setup ≥ 20 ns, D/CX setup and hold ≥ 10 ns |
| SPI read timing | clock cycle ≥ 150 ns — **reads top out near 6.7 MHz**, far below writes |

## Module pinout

Boards ship with 7 or 8 pins. The usual silkscreen, in order: `BLK, CS, DC, RES, SDA, SCL, VCC, GND` (7-pin boards drop `BLK` and tie the backlight on) `(unverified — no vendor document; from community sources and the module photos)`.

| Pad | Goes to | Note |
|---|---|---|
| VCC | 3.3 V | not 5 V tolerant unless the module has a regulator and level shifters |
| GND | GND | |
| SCL | SPI **SCK** | labelled like I2C, but it is the SPI clock |
| SDA | SPI **MOSI** | data in only; most modules bring out no MISO, so reads are impossible |
| RES | any GPIO | display reset, active low |
| DC | any GPIO | data/command (the datasheet calls it D/CX) |
| CS | any GPIO | chip select |
| BLK | any GPIO or 3.3 V | backlight enable; floating is on for most modules `(unverified)` |

## Library setup

TFT_eSPI (`GC9A01_DRIVER`), the stock ESP32 example in `reference/Setup200_GC9A01.h`:

```c
#define GC9A01_DRIVER
#define TFT_MOSI 15   // module "SDA"
#define TFT_SCLK 14   // module "SCL"
#define TFT_CS    5
#define TFT_DC   27
#define TFT_RST  33
#define TFT_BL   22
#define SPI_FREQUENCY 40000000
```

`reference/Setup46_GC9A01_ESP32.h` is the other stock variant (VSPI pins 23/18/15/2/4, `SPI_FREQUENCY 40000000`, `SPI_READ_FREQUENCY 20000000`).

Arduino/Adafruit_GFX: `Adafruit_GC9A01A tft(TFT_CS, TFT_DC, TFT_RST); tft.begin();` — `begin()` with no argument uses `SPI_DEFAULT_FREQ`, which is 24 MHz generic, 40 MHz on ESP32/SAMD51, 80 MHz on RP2040 (`reference/Adafruit_GC9A01A.h`).

CircuitPython: the community `gc9a01` displayio driver, `fourwire.FourWire(spi, command=tft_dc, chip_select=tft_cs, reset=tft_rst)` then `gc9a01.GC9A01(display_bus, width=240, height=240, backlight_pin=tft_bl)`.

## Gotchas

- **SDA/SCL are SPI, not I2C.** Wire SDA to MOSI and SCL to SCK; nothing on the module speaks I2C.
- **No MISO on most modules,** so `TFT_eSPI` register reads and `tft.readPixel()` return junk. Set `TFT_MISO -1` where the setup allows it.
- **Read clock is 20× slower than write** (150 ns vs 10 ns cycle). If a module does expose MISO, keep `SPI_READ_FREQUENCY` low — TFT_eSPI's stock 20 MHz read frequency is already above the datasheet's 6.7 MHz limit.
- **The init sequence is long and mostly undocumented registers** (0xEF/0xEB/0x84…0x90, gamma at 0xF0–0xF3). Use a library's table (`reference/GC9A01_Init.h`) rather than writing one; several registers are only reachable after the "inter register enable" pair 0xFE/0xEF.
- **3.3 V logic.** The datasheet allows IOVCC down to 1.65 V but the modules regulate nothing; driving them from 5 V logic needs level shifting.
- **Round panel, square framebuffer.** The controller still addresses 240×240; the corners exist in GRAM but are not visible.

## Files

- `datasheets/gc9a01a.pdf`: GC9A01A data sheet Rev 1.0 Preliminary, 2019-07-02, 192 pages
- `reference/GC9A01_Init.h`, `GC9A01_Defines.h`, `GC9A01_Rotation.h`: TFT_eSPI's driver tables
- `reference/Setup200_GC9A01.h`, `Setup46_GC9A01_ESP32.h`: TFT_eSPI stock setups for this panel
- `reference/Adafruit_GC9A01A.{h,cpp}`: the Adafruit_GFX driver, including its own init table and per-board default clocks
