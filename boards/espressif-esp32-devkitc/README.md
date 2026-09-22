# Espressif ESP32-DevKitC V4 (and the `esp32dev` board id)

Espressif's original ESP32 board: a WROOM/WROVER module on a breadboard-width PCB with every usable pin on 2 × 19 headers. Chip: [`chips/esp32`](../../chips/esp32/README.md).
Used by: `pio-ir-decode`, `pio-num1-2`, `pio-feather` — all three build `board = esp32dev`.

**`esp32dev` is a generic profile, not this board.** Its board file is named "Espressif ESP32 Dev Module", its `url` field points at Wikipedia, and it describes nothing but an ESP32 with 4 MB of flash. Any ESP32 module board builds against it. **Which physical board the three projects run on is unconfirmed** — this entry documents Espressif's own DevKitC V4, which is the reference design those third-party boards copy, and which the [Seengreat RGB matrix adapter-E](../seengreat-rgb-matrix-adapter-e/README.md) in this library is built to host.

## Module options

V4 ships with any of: ESP32-WROOM-32E, -32UE, -32D, -32U, -32, ESP32-WROVER-E, -IE, ESP32-WROOM-DA (end of life) or ESP32-SOLO-1 (single core). Male or female headers. The WROVER modules add PSRAM — and take GPIO16/17 for it.

## Key specs

| | |
|---|---|
| Module | see above; the current default is ESP32-WROOM-32E |
| USB | Micro-USB through a USB-to-UART bridge, up to 3 Mbps. **No native USB** on the ESP32 |
| Power | Three mutually exclusive supplies: micro-USB, the 5V header, or the 3V3 header. Espressif's warning is explicit — using more than one can damage the board or the supply |
| Buttons | **Boot** and **EN**. EN is reset; hold Boot and press EN for firmware download mode |
| LED | 5 V power-on LED only — there is no user LED on the Espressif board (third-party clones usually add one on GPIO2) |

## Pinout

J2 and J3 from the V4 user guide.

### J2

| No. | Name | Function |
|---|---|---|
| 1 | 3V3 | 3.3 V supply |
| 2 | EN | CHIP_PU, reset |
| 3 | VP | GPIO36, ADC1_CH0 — **input only** |
| 4 | VN | GPIO39, ADC1_CH3 — **input only** |
| 5 | IO34 | GPIO34, ADC1_CH6 — **input only** |
| 6 | IO35 | GPIO35, ADC1_CH7 — **input only** |
| 7 | IO32 | GPIO32, ADC1_CH4, TOUCH_CH9, XTAL_32K_P |
| 8 | IO33 | GPIO33, ADC1_CH5, TOUCH_CH8, XTAL_32K_N |
| 9 | IO25 | GPIO25, ADC2_CH8, **DAC_1** |
| 10 | IO26 | GPIO26, ADC2_CH9, **DAC_2** |
| 11 | IO27 | GPIO27, ADC2_CH7, TOUCH_CH7 |
| 12 | IO14 | GPIO14, ADC2_CH6, TOUCH_CH6, MTMS |
| 13 | IO12 | GPIO12, ADC2_CH5, TOUCH_CH5, **MTDI — flash voltage strap** |
| 14 | GND | Ground |
| 15 | IO13 | GPIO13, ADC2_CH4, TOUCH_CH4, MTCK |
| 16–18 | D2, D3, CMD | GPIO9, GPIO10, GPIO11 — **the module's flash bus** |
| 19 | 5V | 5 V supply |

### J3

| No. | Name | Function |
|---|---|---|
| 1, 7 | GND | Ground |
| 2 | IO23 | GPIO23 |
| 3 | IO22 | GPIO22 |
| 4 | TX | GPIO1, U0TXD |
| 5 | RX | GPIO3, U0RXD |
| 6 | IO21 | GPIO21 |
| 8 | IO19 | GPIO19 |
| 9 | IO18 | GPIO18 |
| 10 | IO5 | GPIO5 — **strapping** |
| 11 | IO17 | GPIO17 — **not available on WROVER modules (PSRAM)** |
| 12 | IO16 | GPIO16 — **not available on WROVER modules (PSRAM)** |
| 13 | IO4 | GPIO4, ADC2_CH0, TOUCH_CH0 |
| 14 | IO0 | GPIO0, ADC2_CH1, TOUCH_CH1, **Boot strap** |
| 15 | IO2 | GPIO2, ADC2_CH2, TOUCH_CH2 — **strapping** |
| 16 | IO15 | GPIO15, ADC2_CH3, TOUCH_CH3, **MTDO — strapping** |
| 17–19 | D1, D0, CLK | GPIO8, GPIO7, GPIO6 — **the module's flash bus** |

## PlatformIO config

All three projects use nothing beyond:

```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
monitor_speed = 115200
```

The board file sets `mcu esp32`, `variant esp32`, `-DARDUINO_ESP32_DEV`, 240 MHz, `flash_mode dio` at 40 MHz, 4 MB flash, upload 460800. A board with more flash or with PSRAM needs `board_upload.flash_size`, `board_build.partitions` and `-DBOARD_HAS_PSRAM` added by hand — the generic profile assumes neither.

## Operational notes

- **GPIO6–GPIO11 are the module's SPI flash** and are on the headers anyway (D0–D3, CMD, CLK). Using them stops the board booting. This is the single most common mistake on an ESP32 board.
- **Six pins are input-only:** GPIO34, 35, 36, 39 (and per the chip entry, 37 and 38, which this board does not break out). No pull-ups, no outputs.
- **GPIO16 and GPIO17 vanish on WROVER modules**, where they are the PSRAM interface. A design that uses them stops working when the module changes.
- **MTDI (GPIO12) selects the flash voltage at reset.** Pulled high at boot, the chip expects 1.8 V flash and a 3.3 V module will not start.
- **Only ADC2 pins are free for analogue while Wi-Fi is on?** — the ESP32's ADC2 is unavailable to the application while the Wi-Fi driver is running, so use the ADC1 pins (32–36, 39) for anything measured during a connection.
- **Two DACs**, on GPIO25 and GPIO26. No other Espressif part in this library has them.
- **Note on C15:** on earlier V4 boards this capacitor can make the board boot into download mode, and it distorts a clock output on GPIO0. Espressif's remedy is to remove it.
- **No native USB.** Flashing and the serial monitor both go through the bridge chip.

## Applications

- **HUB75 matrix driving** through the [Seengreat adapter-E](../seengreat-rgb-matrix-adapter-e/README.md), which takes this board.
- **Analogue output** — the DACs on GPIO25/26 make this the part for simple waveform or audio output without an external DAC.
- **Ethernet** — the ESP32's MAC needs an external PHY, but it is there, which the S3 and C-series parts do not have.
- **General bring-up**, as `pio-ir-decode` (an IR receiver) and `pio-num1-2` (CCS811, ST7735, DHT, LM35) use it.
- **Unsuitable for:** USB device work, and any project that needs GPIO6–11 or expects the S3's pin count.

## Files

- `wiki/user-guide.md`: Espressif's V4 user guide, with images
- `hardware/schematic-v4.pdf`, `hardware/pcb-layout-v4.pdf`, `hardware/dimensions-v4.pdf`
- `hardware/esp32-wroom-32e_datasheet_en.pdf`: the current default module (covers WROOM-32E and -32UE)
- `reference/platformio-esp32dev.json`: the generic `esp32dev` board definition the projects build against
