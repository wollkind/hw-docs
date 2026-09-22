# SmartPanle SC05_X — ZX2D80CE02S-2432 (ESP32-S3 2.8" touch panel)

ESP32-S3 panel board with a 240×320 ST7789 LCD on an 8-bit 8080 parallel bus, FT5x06 capacitive touch and an RS485 transceiver. Sold by Shenzhen QM Smart Panlee / Wireless-Tag under the PanelLan line; the library calls it `BOARD_SC05_X` and the model code is `ZX2D80CE02S-2432`. Chip: [`chips/esp32-s3`](../../chips/esp32-s3/README.md).
Used by: `pio-strip-com`, the `display` env — an LVGL control surface that drives a NeoPixel strip over ESP-NOW.

**Identification.** The project builds it as `board = esp32-s3-devkitc-1`, which says nothing about this hardware; the identification comes from the project's own `platformio.ini` (`smartpanle/PanelLan`), its `src/display/main.cpp` header comment (`PanelLan BOARD_SC05_X`) and the library's board enum, where `BOARD_SC05_X` is `ZX2D80CE02S-2432`. Web search returns the vendor name for this model as **WT32S3-28S PRO**, but that title comes from a third-party document listing, not from the vendor *(unverified)*. No vendor datasheet could be fetched — see `sources.md`.

## Key specs

| | |
|---|---|
| MCU | ESP32-S3 (the driver is compiled only `#ifdef CONFIG_IDF_TARGET_ESP32S3`) |
| Panel | ST7789, **240 × 320** portrait native, `offset_rotation 2`, inverted, RGB order, not readable |
| Panel bus | **8-bit parallel 8080**, LovyanGFX `Bus_Parallel8`, write clock 20 MHz |
| Touch | **FT5x06** over I2C at 400 kHz, single touch point in this driver |
| Backlight | PWM, 21111 Hz, channel 7, non-inverted |
| Serial | RS485 transceiver with an RTS direction pin |
| Absent | No I2S, no microSD — every pin in those groups is `-1` in the pin header |
| Memory | The library's own table says SC05_X is **8 MB QIO flash with QSPI PSRAM**. `pio-strip-com` builds it as **16 MB with `qio_opi` (octal) PSRAM** and that build runs. The two do not agree; see Operational notes |

## Pinout

From `src/board/sc05_x/sc05x_pin.h` in the vendor library. These are ESP32-S3 GPIO numbers.

| Function | GPIO |
|---|---|
| Board reset (panel RST) | 3 |
| I2C SDA / SCL (board and touch) | 8 / 9 |
| Touch INT | 48 |
| Touch RST | not connected |
| LCD backlight | 47 |
| LCD RS (D/C) | 18 |
| LCD WR | 17 |
| LCD TE | 38 |
| LCD CS / RD / RST | not connected (`-1`) |
| LCD D0–D7 | 16, 40, 15, 7, 41, 42, 2, 1 |
| USB D+ / D- | 19 / 20 |
| RS485 RTS / RXD / TXD | 5 / 4 / 6 |
| External pins 1–6 | 10, 11, 12, 13, 14, 21 |

The six "external" pins are the only ones free for user hardware.

## PlatformIO config

From `pio-strip-com`, which builds and runs on the board:

```ini
[env:display]
board = esp32-s3-devkitc-1
board_upload.flash_size = 16MB
board_build.partitions = huge_app.csv
board_build.arduino.memory_type = qio_opi
build_flags =
	-DLV_CONF_INCLUDE_SIMPLE
	-I include
	-DBOARD_HAS_PSRAM
lib_deps =
	lvgl/lvgl@^8.4.0
	smartpanle/PanelLan@^0.0.5
```

There is no PlatformIO board id for this hardware. `esp32-s3-devkitc-1` is used as a memory description and then overridden, which is why the flash size, partition table and PSRAM mode are all set by hand. `platform` in that project points at `file://C:/Users/steve/pio-esp32-55.03.311`, a local fork that resolves on the owner's machine only — on another machine substitute the pioarduino release zip the other projects use.

## Operational notes

- **The flash and PSRAM figures disagree with the vendor library's table.** PanelLan's README lists SC05_X as 8 MB QIO flash + QSPI PSRAM, while this project flashes 16 MB with octal PSRAM and works. Either the owner's unit is a 16 MB/OPI build of the same model or the settings are larger than the hardware and the excess is simply never touched. Read the flash size with `esptool.py flash_id` before relying on either figure *(unverified)*.
- **The driver file contains a GT911 touch class that it does not use.** `sc05x.cpp` defines `Touch_GT911_Spec` and then instantiates `Touch_FT5x06` — the FT5x06 is what this board has. The library's README table agrees. Anything written against the GT911 register map will not talk to this panel.
- **The panel is native portrait.** 240 × 320 with `offset_rotation 2`; `pio-strip-com` sets LVGL rotation 1 to work in 320 × 240 landscape.
- **Only six GPIO are free** (10–14 and 21). Everything else is the parallel bus, touch, backlight, USB or RS485.
- **No CS pin on the LCD.** `LCD_CS_PIN` is `-1`, so the bus is not shared — nothing else can sit on those eight data lines.
- **Touch RST is not wired**, so a touch controller that has locked up can only be recovered by resetting the whole board.
- **The board's reset pin (GPIO3) also resets the panel** and is a strapping pin on the ESP32-S3 (JTAG source selection, per [`chips/esp32-s3`](../../chips/esp32-s3/README.md)).
- `pio-strip-com` runs the USB Serial/JTAG peripheral to detect an attached host (`usb_serial_jtag_is_connected()`) and suppresses light sleep while one is present, because sleeping drops the USB link mid-upload. That is a project decision, but it documents that the USB pins on this board are the S3's native ones.

## Applications

- **Wall or desk control surface.** LVGL over a 2.8" touch panel with six spare GPIO is enough for a room controller; `pio-strip-com` uses it exactly that way, over ESP-NOW.
- **RS485 field terminal.** The transceiver and its direction pin are already wired, so a Modbus HMI needs no extra hardware — the [XY-SK120 supply](../../parts/sk-120-buck-boost/README.md) in this library speaks Modbus RTU.
- **Unsuitable for:** anything needing an SD card, I2S audio, or more than six free pins; and for sharing the display bus with another parallel device.

## Files

- `wiki/board-index.md`: the vendor documentation site's ESP32-S3 board index. **It does not list this model** — kept as evidence of where the datasheet is not.
- `reference/sc05x_pin.h`: the vendor library's pin map, the authority for the pinout above
- `reference/sc05x.cpp`: the vendor library's panel, touch and backlight setup, including the ST7789 init sequence
- `reference/panellan-readme.md`: the library README, with the model and memory tables for every PanelLan board
