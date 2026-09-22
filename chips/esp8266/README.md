# ESP8266EX

Espressif single-core Tensilica L106 32-bit RISC @ 80/160 MHz, 2.4 GHz Wi-Fi 802.11 b/g/n (HT20), no Bluetooth, no internal program flash. QFN32 5 × 5 mm.

- `esp8266ex_datasheet_en.pdf`: datasheet v7.1 (2025.11). Pin definitions, power modes, peripherals, electrical specs.
- `esp8266-technical_reference_en.pdf`: registers and peripheral detail.

**Espressif marks the ESP8266EX NRND — not recommended for new designs — on the cover of datasheet v7.1, and names the ESP8684 as the upgrade.** Existing boards are unaffected; new designs are the point of the notice.

## Specs from the datasheet

| | |
|---|---|
| CPU | Tensilica L106 32-bit, max 160 MHz (80 MHz default in the Arduino core) |
| SRAM | No programmable ROM. Under Espressif's SDK the space available to a user application in Heap + Data is about 50 kB when the chip is in Station mode and associated |
| Flash | External SPI flash only, up to 16 MB. Minimum 512 kB without OTA, 1 MB with OTA |
| Crystal | 24–52 MHz (26 MHz and 40 MHz are the usual choices) |
| Supply | 2.5–3.6 V (VDDA/VDD3P3), VDDPST 1.8–3.6 V |
| Current | 80 mA average active; Modem-sleep 15 mA; Light-sleep 0.9 mA; Deep-sleep 20 µA; shut down 0.5 µA |
| Temperature | −40 °C to 125 °C |
| ADC | One 10-bit SAR ADC on TOUT (pin 6). It reads either the TOUT input **or** the VDD3P3 supply, never both |
| Radio | 802.11 b/g/n HT20, 2400–2483.5 MHz. TX +20 dBm (b), +17 dBm (g), +14 dBm (n) |

## Pins to know

- **GPIO16 is XPD_DCDC (pin 8).** The datasheet's pin table gives its function as "Deep-sleep wakeup (need to be connected to EXT_RSTB); GPIO16", so timed deep-sleep wakeup only works on a board that wires pin 8 to the reset pin.
- **GPIO0, GPIO2 and MTDO (GPIO15) carry the boot straps.** The datasheet's note under Table 2-1: "GPIO2, GPIO0, and MTDO are used to select booting mode and the SDIO mode; U0TXD should not be pulled externally to a low logic level during the powering-up." The required levels are not given in either document here — Espressif keeps them in a separate Strapping List, which was not fetched *(unverified)*. Boards resolve it with pulls: on the D1 mini, GPIO0 and GPIO2 are pulled up and GPIO15 pulled down.
- **Do not pull U0TXD (GPIO1) low at power-up**, per that same note. A load on the TX pin can stop the chip from booting.
- **GPIO6–GPIO11 (SD_CLK, SD_CMD, SD_DATA_0..3) go to the SPI flash.** On a board with a 4 MB QIO/DIO part they are not available.
- **CHIP_EN (pin 7)** must be high for the chip to run.
- TOUT must be left floating when the ADC is not used (datasheet, section 4.9).

Boards: [wemos-d1-mini](../../boards/wemos-d1-mini/README.md), [adafruit-feather-huzzah-esp8266](../../boards/adafruit-feather-huzzah-esp8266/README.md)
