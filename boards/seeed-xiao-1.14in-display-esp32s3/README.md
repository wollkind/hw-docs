# Seeed XIAO 1.14" IPS Display (ESP32-S3)

A display board with a XIAO ESP32-S3 Plus built in (the product page calls it "1.14 Inch Display Powered by XIAO ESP32-S3 Plus", SKU 6991). It has a 135×240 ST7789 LCD, an LSM6DS3 IMU, a PDM mic, three buttons, a Grove I2C port and a LiPo connector. MCU docs: [../seeed-xiao-esp32s3](../seeed-xiao-esp32s3/README.md) (Plus). Chip: [../../chips/esp32-s3](../../chips/esp32-s3/README.md).
Used by: none yet.

## Key specs

| | |
|---|---|
| MCU | XIAO ESP32-S3 Plus: ESP32-S3R8, 8 MB PSRAM, 16 MB flash, Wi-Fi + BLE 5 |
| LCD | 1.14" IPS, 135 × 240, ST7789, SPI |
| IMU | LSM6DS3 at I2C **0x6A** (schematic U2), INT1 → D14 |
| Mic | ZTS6131 PDM mic (schematic MIC1) |
| Buttons | A (front-left, D6), B (front-right, D7), C (side, D19). Each has an external 1 kΩ pull-up |
| Battery | 2-pin JST, 3.7 V LiPo. Voltage via D16 through a 316k/160k divider (×2.975). No charge-status signal |
| Expansion | Grove I2C (D4/D5), I2S pads (D11–D13), JTAG pads |
| Size | 26 × 48 × 10.6 mm |

## Pinout

From the wiki pin map (`wiki/getting-started.md`). GPIO numbers are from the Plus variant header.

| XIAO | GPIO | Net | Use |
|---|---|---|---|
| D0 | 1 | PDM_CLK | mic clock |
| D1 | 2 | MIC_DATA | mic data |
| D2 | 3 | LCD_CS | |
| D3 | 4 | LCD_DC | |
| D4 | 5 | SDA | IMU + Grove |
| D5 | 6 | SCL | IMU + Grove |
| D6 | 43 | BTN_A | also U1 test pad |
| D7 | 44 | BTN_B | also U2 test pad |
| D8 | 7 | SCK | LCD |
| D9 | 8 | NC | |
| D10 | 9 | MOSI | LCD |
| D11 | 38 | I2S_SD | bottom pad |
| D12 | 39 | I2S_SCK | bottom pad |
| D13 | 40 | I2S_WS | bottom pad |
| D14 | 41 | IMU_INT | LSM6DS3 INT1, can wake from sleep |
| D15 | 42 | NC | test point TP15 |
| D16 | 10 | BAT_ADC | **don't use externally** |
| D17 | 13 | LCD_RST | |
| D18 | 12 | LCD_BL | PWM backlight |
| D19 | 11 | BTN_C | also U3 test pad |

## Software

- Arduino core: esp32 3.3.11, board `XIAO_ESP32S3_PLUS`. For PlatformIO, see the Plus entry (`board = seeed_xiao_esp32_s3_plus`, pioarduino). Untested here.
- Graphics library: **Seeed_GFX2** v1.0.0 (https://github.com/Seeed-Studio/Seeed_GFX2), which isn't in the Library Manager. Start it with `display.begin<Board_XIAO_1inch14_LCD<13, 12>, Config_Seeed_1inch14_LCD_ST7789>()` (RST=GPIO13, BL=GPIO12).
- The older Seeed_GFX (TFT_eSPI fork) uses a `driver.h` with `#define BOARD_SCREEN_COMBO 75` and `#define USE_XIAO_TFT_DISPLAY_BOARD`. See `examples/xiao_esp32s3_114_display/`.
- The vendor demos read the IMU with raw `Wire` register access, so no IMU library is needed. The mic uses the IDF 5 `driver/i2s_pdm.h`.

## Gotchas

- **UART0 is taken:** D6/D7 (UART0 TX/RX) are buttons A/B, so serial goes over USB CDC.
- **I2C address:** the IMU sits at 0x6A on the shared I2C bus, so Grove devices must avoid that address.
- **I2C hot-plugging:** hot-plugging on Grove I2C can hang the bus. The factory dashboard's I2C scan freezes; press Reset.
- **Battery voltage:** V = ADC mV × (316+160)/160. The code is in `examples/xiao_esp32s3_114_bat/`.
- **Partitions:** the 16 MB flash needs a 16 MB partition table. The PIO board default is 8 MB.

## Files

- `wiki/getting-started.md`, `wiki/function-demos.md` (+ `img/`)
- `hardware/schematic.pdf` (v1.0, 2026-06-10), `hardware/kicad-project.zip`, `hardware/3d-model.step.zip`
- `datasheets/lcd-1.14in.pdf`
- `firmware/factory-firmware.zip`: DashBoard factory image (app, bootloader, partitions, boot_app0, flash README)
- `examples/`: vendor basic sketches (display, battery, buttons, I2C scan, I2S) and the IMU wake-up demo
