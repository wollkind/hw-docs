# ESP32-C3

Espressif single-core 32-bit RISC-V SoC, up to 160 MHz, 2.4 GHz Wi-Fi 4 + Bluetooth 5 LE, USB Serial/JTAG. No PSRAM interface on the modules used here.

- `esp32-c3_datasheet_en.pdf`: pin functions, strapping pins, electrical specs
- `esp32-c3_technical_reference_manual_en.pdf`: registers and peripherals
- `errata.md`: silicon errata (CPU-863, ADC-183, ADC-270)

## Pins to know

- Strapping pins: **GPIO2, GPIO8, GPIO9** (datasheet §3 Boot Configurations). GPIO9 low at reset selects download boot.
- GPIO12–17 are the SPI0/1 flash interface. Leave them alone.
- GPIO18/19 are USB_D-/USB_D+ (USB Serial/JTAG); the pair can be swapped in software.
- GPIO20/21 are U0RXD/U0TXD.

Boards: [espressif-esp32-c3-devkitc-02](../../boards/espressif-esp32-c3-devkitc-02/README.md)
