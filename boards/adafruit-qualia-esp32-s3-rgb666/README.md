# Adafruit Qualia ESP32-S3 for RGB-666 Displays (PID 5800)

ESP32-S3 board whose job is driving a 40-pin RGB-666 TTL panel from the S3's parallel LCD peripheral. No display is included. Chip: [`chips/esp32-s3`](../../chips/esp32-s3/README.md).
Used by: `pio-piotest` (the working display project — it selects the 4.0" 480×480 square panel, `tl040wvs03`), `pio-blink` (`[env:qualia]`), `pio-feather` (`[env:qualia]`).

## Key specs

| | |
|---|---|
| Module | ESP32-S3-WROOM, 240 MHz, Wi-Fi + BLE |
| Memory | **16 MB flash, 8 MB octal PSRAM** (`qio_opi`). The PSRAM is what holds the frame buffer |
| Display | 40-pin FPC connector, RGB-666 wiring: 16 GPIO for 5-6-5 colour plus HSync, VSync, DE and PCLK |
| Backlight | TPS61169 constant-current driver, up to 30 V forward. **25 mA by default**, settable to 200 mA in 25 mA steps by soldering the top jumpers |
| IO expander | **PCA9554A at 0x3F** on I2C, address settable 0x3B–0x3F by the jumpers on the reverse |
| USB | USB-C into the S3's native USB. `ARDUINO_USB_CDC_ON_BOOT=1`; UF2 bootloader at 0x410000 |
| I2C | STEMMA QT connector, pulled up to 3.3 V |
| Analog | 3-pin JST at `A0` (5 V by default, a cut-and-solder jumper moves it to 3 V), plus `A0`/`A1` pads |
| Buttons | Reset and Boot0 on the board; **UP and DN hang off the IO expander**, lightly pulled up, pressing pulls low |
| Regulators | LP2985 LDO plus the boost for the backlight rail |

There is **no battery jack and no charger** on this board, and no onboard NeoPixel or user LED.

## Pinout

From `variants/adafruit_qualia_s3_rgb666/pins_arduino.h` in arduino-esp32, which is what `board = adafruit_qualia_s3_rgb666` compiles against.

RGB-666 data, direct to ESP32-S3 GPIO:

| Signal | GPIO | | Signal | GPIO | | Signal | GPIO |
|---|---|---|---|---|---|---|---|
| R1 | 11 | | G0 | 48 | | B1 | 40 |
| R2 | 10 | | G1 | 47 | | B2 | 39 |
| R3 | 9 | | G2 | 21 | | B3 | 38 |
| R4 | 46 | | G3 | 14 | | B4 | 0 |
| R5 | 3 | | G4 | 13 | | B5 | 45 |
| | | | G5 | 12 | | | |

| Timing | GPIO |
|---|---|
| PCLK | 1 |
| DE | 2 |
| HSYNC | 41 |
| VSYNC | 42 |

Board IO:

| Function | GPIO |
|---|---|
| SDA / SCL (STEMMA QT and the expander) | 8 / 18 |
| SCK / MISO / MOSI / CS | 5 / 6 / 7 / 15 (CS has a 10 kΩ pull-up) |
| TX / RX | 16 / 17 |
| A0 / A1 | 17 / 16 — **the same two pins as RX/TX** |
| Touch pins | T3, T8–T12 map to GPIO 3, 8, 9, 10, 11, 12 |

On the PCA9554A expander (pin numbers on the expander, not GPIO):

| Function | Expander pin |
|---|---|
| TFT SCK / CS / MOSI | 0 / 1 / 7 |
| TFT RESET | 2 |
| Capacitive touch IRQ | 3 |
| TFT backlight | 4 |
| Button UP / DN | 5 / 6 |

The display's own SPI configuration bus runs through the expander, which is why `Arduino_XCA9554SWSPI(PCA_TFT_RESET, PCA_TFT_CS, PCA_TFT_SCK, PCA_TFT_MOSI, &Wire, 0x3F)` is the first thing every sketch builds.

## PlatformIO config

Verified in `pio-piotest`:

```ini
[env:adafruit_qualia_s3_rgb666]
platform = https://github.com/pioarduino/platform-espressif32/releases/download/stable/platform-espressif32.zip
board = adafruit_qualia_s3_rgb666
framework = arduino
monitor_speed = 115200
lib_deps =
	moononournation/GFX Library for Arduino@^1.6.5
	adafruit/Adafruit FT6206 Library@^1.1.1
```

The board file already sets `memory_type qio_opi`, `BOARD_HAS_PSRAM`, `flash_size 16MB` and the `tinyuf2-partitions-16MB.csv` partition table, so none of that needs repeating in the project. Upload speed is 460800 with `use_1200bps_touch`, which keeps the UF2 bootloader after an Arduino upload.

## Operational notes

- **A 40-pin display is not automatically an RGB-666 display.** Adafruit's own warning: the power pins are not in the same place on every 40-pin panel, and plugging a non-RGB-666 panel in risks damaging it. Connect the cable with its metal pins facing the board, pin 1 furthest from the JST connector.
- **The panel is not self-describing.** Resolution, porch/pulse timings and the init sequence have to be written into the sketch per panel. `pio-piotest` keeps all nine of Adafruit's known-good panels in `src/main.cpp` as commented blocks with the 4.0" 480×480 square (`tl040wvs03`) selected — the fastest way to retarget the board is to move the comment markers.
- **A0/A1 are RX/TX.** The variant assigns GPIO17 to both `A0` and `RX`, and GPIO16 to both `A1` and `TX`. Wire a sensor to the analog pads and the UART debug output is gone.
- **There is no `LED_BUILTIN`** in the variant header. `pio-blink` defines `-D LED_BUILTIN=18` for its `qualia` env, and GPIO18 is this board's **SCL** — that env blinks the I2C clock line, which is fine on a board with nothing on I2C and wrong the moment a STEMMA sensor is plugged in.
- **The RGB bus sits on three strapping pins.** Per [`chips/esp32-s3`](../../chips/esp32-s3/README.md) the S3's straps are GPIO0, 3, 45 and 46; this board puts `TFT_B4` on GPIO0, `TFT_R5` on GPIO3 and `TFT_B5` on GPIO45. It boots because the panel is passive at reset, but a panel or ribbon that loads those lines can change the boot mode or the VDD_SPI voltage. Suspect it first when a board with a display attached will not boot and the bare board does.
- **The backlight defaults to 25 mA.** A large panel looks dim until the top jumpers are soldered; up to 200 mA is available.
- **Backlight PWM is opt-in:** solder the bottom PWM jumper to get `A1` control over brightness.
- **The expander is on the I2C bus at 0x3F.** Any STEMMA device that also wants 0x3F has to move, or the expander does, via the jumpers (0x3B–0x3F).
- **Boot0 plus Reset** is the way into the ROM bootloader; the UF2 bootloader takes double-click of Reset.

## Applications

- **Large-format information display.** 16 MB flash and 8 MB PSRAM hold a 480×480 or 720×720 frame buffer and the S3's LCD peripheral DMAs it out continuously.
- **Touch HMI.** A capacitive panel's controller sits on the same I2C bus, with its interrupt on expander pin 3; `pio-piotest` uses an FT6206.
- **Instrument panel with external analog input.** The 3-pin JST at A0 takes a sensor or a NeoPixel strip (5 V by default), at the cost of the debug UART.
- **Unsuitable for:** battery-powered work — there is no charger and no battery connector, and a lit RGB panel is not a low-power load. Also unsuitable for SPI displays; this board's whole point is the parallel bus.

## Files

- `wiki/overview.md`, `wiki/pinouts.md`, `wiki/downloads.md`: the Learn guide pages, with images
- `hardware/eagle.sch`, `hardware/eagle.brd`: Adafruit's design
- `reference/pins_arduino.h`: the arduino-esp32 variant — the authority for every pin above
- `reference/platformio-board.json`: the `adafruit_qualia_s3_rgb666` board definition
