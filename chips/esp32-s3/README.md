# ESP32-S3

Espressif dual-core Xtensa LX7 @ 240 MHz, 512 KB SRAM, 384 KB ROM, Wi-Fi 4 + BLE 5, native USB-OTG / USB-Serial-JTAG, 45 GPIO.

- `esp32-s3_datasheet_en.pdf`: pin functions, strapping pins, electrical specs, part-number decoding (e.g. N32R16 = 32 MB flash, 16 MB PSRAM)
- `esp32-s3_technical_reference_manual_en.pdf`: registers and peripherals (LCD_CAM, GDMA, I2S, RMT…)
- `errata.md`: silicon errata

## Pins to know

- Strapping pins: GPIO0 (boot mode), GPIO3 (JTAG source), GPIO45 (VDD_SPI voltage), GPIO46 (ROM log/boot).
- GPIO26–32 connect to SPI flash/PSRAM. On octal-PSRAM parts (R8/R16), GPIO33–37 are used too. Leave them alone.
- GPIO19/20 are USB D-/D+.
- GPIO43/44 are UART0 TX/RX by default.

Module datasheet for the WROOM-1/1U (`esp32-s3-wroom-1_datasheet_en.pdf`) is here too.

Boards: [waveshare-esp32-s3-rgb-matrix](../../boards/waveshare-esp32-s3-rgb-matrix/README.md), [adafruit-esp32-s3-reverse-tft-feather](../../boards/adafruit-esp32-s3-reverse-tft-feather/README.md), [seeed-xiao-esp32s3](../../boards/seeed-xiao-esp32s3/README.md), [seeed-xiao-1.14in-display-esp32s3](../../boards/seeed-xiao-1.14in-display-esp32s3/README.md), [adafruit-qualia-esp32-s3-rgb666](../../boards/adafruit-qualia-esp32-s3-rgb666/README.md)
