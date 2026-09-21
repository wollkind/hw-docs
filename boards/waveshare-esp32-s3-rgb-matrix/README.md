# Waveshare ESP32-S3-RGB-Matrix

HUB75 LED-panel driver board. SKU 34422. Chip docs: [../../chips/esp32-s3](../../chips/esp32-s3/README.md).
Used by: `infopanel64` (in `Documents/PlatformIO/Projects`).

## Key specs

| | |
|---|---|
| MCU | ESP32-S3-N32R16: dual LX7 @ 240 MHz, 512 KB SRAM |
| Flash / PSRAM | 32 MB QIO flash + 16 MB **octal** PSRAM (stacked) |
| Radio | 2.4 GHz Wi-Fi, BLE 5 |
| USB | Type-C, native USB (CDC/JTAG), no USB-UART bridge |
| Power | USB-C plus a separate screen-power input. Drives up to six 64×64 panels |
| Onboard | ES7210 4-ch mic ADC + 2 mics, ES8311 codec + speaker header, QMI8658 IMU, SHTC3 temp/RH, PCF85063A RTC (SH1.0 cell connector), TF slot |
| Buttons | RST, BOOT (GPIO0, user-readable) |

## Pinout

HUB75 (from `reference/esp32s3-default-pins.hpp` and `reference/sdkconfig.defaults`):

| Signal | GPIO | Signal | GPIO |
|---|---|---|---|
| R1 | 4 | A | 18 |
| G1 | 5 | B | 8 |
| B1 | 6 | C | 3 |
| R2 | 7 | D | 42 |
| G2 | 15 | E | 9 |
| B2 | 16 | LAT | 40 |
| CLK | 41 | OE | 2 |

Peripherals (from `reference/bsp-config.h`):

| Bus | Pins |
|---|---|
| I2C (400 kHz) | SDA 47, SCL 48 |
| I2S | MCLK 12, BCLK/SCLK 43, WS/LRCK 38, DOUT (to ES8311) 21, DIN (from ES7210) 39 |
| Speaker amp enable | 11 |
| TF card (SDMMC 1-bit) | CLK 1, CMD 44, D0 17. The SPI-mode CS is 14 |
| BOOT button | 0 |
| RTC interrupt | 10? (unverified, per infopanel64 notes) |

I2C addresses: ES7210 0x40–0x43, QMI8658 0x6B or 0x6A (WHO_AM_I = 0x05), PCF85063A 0x51. The SHTC3 is at 0x70 per its datasheet, not yet confirmed on this board.

## PlatformIO config (verified in infopanel64)

```ini
platform = https://github.com/pioarduino/platform-espressif32/releases/download/55.03.311/platform-espressif32.zip
framework = arduino
board = esp32-s3-devkitc-1
board_build.arduino.memory_type = qio_opi
board_build.flash_mode = qio
board_build.partitions = partitions_32MB.csv
board_upload.flash_size = 32MB
build_flags = -DBOARD_HAS_PSRAM -DARDUINO_USB_CDC_ON_BOOT=1 -DARDUINO_USB_MODE=1
```

## Gotchas

- **Arduino core:** Arduino-ESP32 3.3.x is only available through the pioarduino platform fork. Stock `espressif32` is too old for the vendor examples.
- **Vendored HUB75 driver:** the driver `#include`s `platforms/esp32s3/gdma_lcd_parallel16.cpp` itself. Exclude that folder with `build_src_filter = +<*> -<platforms/>` or the symbols get defined twice.
- **Panel driver chip:** the 64×64 panel in use has an FM6126A driver. Set the driver in `mxconfig`. P4 panels need `mxconfig.driver = HUB75_I2S_CFG::SHIFTREG`.
- **Default resolution:** 64×64. A wrong size setting shows a misaligned or partial image.
- **Boot loops after flashing:** usually a config mismatch or a missing screen power supply. USB alone can't power a panel.
- **USB drops out or resets:** the USB supply is below about 4.9 V.
- **Upload fails:** hold BOOT, tap RST, then release BOOT.
- **UART0 pins are taken:** GPIO43/44 (U0TXD/U0RXD) carry I2S BCLK and SD CMD. Serial goes over native USB CDC.
- **Pins reserved for flash/PSRAM:** don't reassign the HUB75 pins onto octal-PSRAM pins (GPIO33–37). The vendor mapping already avoids them.
- **Speaker amp:** GPIO11 enables the speaker amp. Hold it low when the speaker isn't used.

## Files

- `wiki/`: vendor wiki pages as markdown, with images (overview, arduino, esp-idf, instructions-for-use, firmware-flashing, faq, resources-and-documents)
- `hardware/schematic.pdf`, `hardware/dimensions-2d.pdf`
- `firmware/factory-test.bin`: factory test firmware. See `wiki/firmware-flashing.md`
- `reference/`: vendor BSP pin headers, the BSP README (Chinese), the repo README and `sdkconfig.defaults`
- `sources.md`: where everything came from
