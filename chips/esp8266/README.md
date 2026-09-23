# ESP8266EX

Espressif Wi-Fi SoC: Tensilica L106 32-bit, 80 MHz (up to 160 MHz), 2.4 GHz 802.11 b/g/n, no Bluetooth, external SPI flash, one 10-bit ADC.

- `esp8266ex_datasheet_en.pdf`: pin list, boot modes, electrical specs
- `esp8266_technical_reference_en.pdf`: peripherals and registers

## Pins to know

- Boot mode is selected by **GPIO0, GPIO2 and MTDO (GPIO15)** (datasheet). The level table is not in this datasheet; boards pull GPIO0/GPIO2 up and GPIO15 down for flash boot (D1 mini schematics) `(level table unverified against an Espressif source)`.
- GPIO2 is the UART TX during flash programming (datasheet pin table).
- TOUT (ADC) input range is **0–1.0 V** on the bare chip; boards add a divider (the D1 mini's 220k/100k gives 0–3.2 V).
- GPIO16 (XPD_DCDC) is the deep-sleep wake output and must be connected to EXT_RSTB for timed wake (datasheet pin table).
- Heap + data in station mode is around 50 kB (datasheet).

Boards: [wemos-d1-mini](../../boards/wemos-d1-mini/README.md)
