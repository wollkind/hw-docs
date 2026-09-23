# ESP32-C6

Espressif SoC with a high-performance 32-bit RISC-V core (up to 160 MHz) and a low-power RISC-V core (up to 20 MHz); 2.4 GHz Wi-Fi 6 (802.11ax), Bluetooth 5 LE and IEEE 802.15.4 (Zigbee, Thread) sharing one antenna; USB Serial/JTAG.

- `esp32-c6_datasheet_en.pdf`: pin functions, strapping pins, electrical specs
- `esp32-c6_technical_reference_manual_en.pdf`: registers and peripherals
- `errata.md`: silicon errata (CPU-206, CPU-863, CLK-6996, CLK-8588, RES-7080, SPI-304, RMT-176, ADC-305, ADC-1477, WIFI-9686)

## Pins to know

- Strapping pins: **GPIO4 (MTMS), GPIO5 (MTDI), GPIO8, GPIO9, GPIO15** (datasheet §3). GPIO9 = boot button on dev boards.
- GPIO24–30 carry the SPI flash (SPICS0 24, SPIQ 25, SPIWP 26, SPIHD 28, SPICLK 29, SPID 30).
- GPIO12/13 are USB_D-/USB_D+ (USB Serial/JTAG); swappable in software.
- GPIO16/17 are U0TXD/U0RXD.
- LP peripherals (usable by the LP core in sleep) sit on GPIO0–7: LP_I2C SDA/SCL on GPIO6/7, LP_UART on GPIO4/5.

Boards: [espressif-esp32-c6-devkitc-1](../../boards/espressif-esp32-c6-devkitc-1/README.md), [seeed-xiao-esp32c6](../../boards/seeed-xiao-esp32c6/README.md)
