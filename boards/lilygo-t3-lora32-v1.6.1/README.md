# LilyGO T3 LoRa32 V1.6.1 (TTGO LoRa32)

ESP32-PICO-D4 board with an SX1276/SX1278 LoRa module, a 0.96" SSD1306 OLED, a microSD slot and a Li-ion charger. Sold as [lilygo.cc/products/lora3](https://lilygo.cc/products/lora3) ("T3 LoRa32 V1.6.1").
Chip: ESP32-PICO-D4 — no `chips/esp32` entry yet (espressif.com is unreachable from the sandbox).
Used by: no project found (`pio-radio`, `pio-radio1`, `pio-radio2` are all Feather 32u4 / RadioHead, not this board).

## Key specs

| | |
|---|---|
| SoC | ESP32-PICO-D4, 4 MB flash (quad-SPI), **no PSRAM** |
| Radio | SX1276 (830–945 MHz) or SX1278 (433 MHz), on a "TTGO LORA" module; SMA or IPEX antenna |
| LoRa data rate | LoRa 0.018–37.5 kbps, FSK 1.2–300 kbps; FSK/GFSK/MSK/GMSK/LoRa/OOK |
| Display | 0.96" SSD1306 128×64, I2C at **0x3C** (module strapped for I2C: R1/R4/R6/R7/R8 fitted) |
| Storage | microSD (push-pull TF slot) on its own SPI bus |
| USB | Micro-USB, **CP2104** USB-UART (schematic V1.6, 2021-01-06) |
| Power | USB 5 V, JST PH-2.0 battery, ME6211 3.3 V LDO, SK-12D02 slide switch |
| Charger | TP4054, 500 mA charge current, 3.7 V Li-ion; CHRG LED |
| Battery sense | GPIO35 through a 100 kΩ / 100 kΩ divider (4.2 V max, no compensation) |
| Buttons / LEDs | RST button; user LED on GPIO25 (active high); CHG LED; no user button |

## Pinout

LoRa module (schematic sheet 2 and `reference/utilities.h`, `T3_V1_6_SX1276` block — they agree):

| Signal | GPIO | Note |
|---|---|---|
| SCK | 5 | |
| MISO | 19 | |
| MOSI | 27 | |
| NSS / CS | 18 | |
| RESET | 23 | GPIO14 on the older V1.3 |
| DIO0 | 26 | not listed in the vendor pin table; from `utilities.h` + schematic net `IO26=DI0/IO0` |
| DIO1 | 33 | schematic net `HPDIO1` |
| DIO2 / BUSY | 32 | schematic net `HPDIO2`; `BUSY` only on SX1262 boards |

OLED and card slot:

| Signal | GPIO |
|---|---|
| I2C SDA (OLED) | 21 |
| I2C SCL (OLED) | 22 |
| OLED reset | not connected |
| SD CS | 13 |
| SD MOSI | 15 |
| SD SCK | 14 |
| SD MISO | 2 |

Other: battery ADC 35, user LED 25. GPIO34/35 are input-only on the ESP32, so the ADC pin cannot be driven.

## PlatformIO (from the vendor repo, untested here)

```ini
[env:T3_V1_6_SX1276]
platform = espressif32@6.13.0
board = esp32dev
framework = arduino
board_build.partitions = huge_app.csv
upload_speed = 921600
monitor_speed = 115200
build_flags = -DT3_V1_6_SX1276     ; or -DT3_V1_6_SX1278 for the 433 MHz board
```

The matching Arduino IDE settings from the vendor doc: ESP32 Dev Module, 240 MHz, 4 MB (32 Mb) flash, QIO, 80 MHz, partition scheme "Huge APP (3 MB No OTA/1 MB SPIFFS)".

## Operational notes

- **No battery protection on the board.** LilyGO says to use a Li-ion cell that has its own protection circuit.
- **Never transmit without an antenna** — it damages the RF module.
- **Remove the SD card before uploading a sketch**, otherwise the upload fails (vendor doc). The card slot shares GPIO2/12-adjacent pins with the boot straps `(unverified — no ESP32 datasheet fetched)`.
- **Pick the right radio flag.** `-DT3_V1_6_SX1276` (868/915 MHz) vs `-DT3_V1_6_SX1278` (433 MHz); the wrong one still compiles against the same pin map but the radio will not start.
- **Antenna path:** the board ships on the SMA path. To use the IPEX connector, rotate the matching resistor 90° left and resolder it (`wiki/img/LoRa-IPEX.png`).
- **The TCXO SKU is a different board.** On "T3 V1.6.1 TCXO" (sold as `t3-tcxo`) GPIO33 is the TCXO enable, not DIO1, and LilyGO notes it does not support their LoRaWAN examples.
- **USB bridge conflict:** the schematic in this folder shows a Micro-USB connector with a CP2104. The vendor quick-start text tells you to install the **CH9102** driver and mentions USB-C — that text is shared across the T3 series, so later production runs may carry a CH9102F `(unverified)`. Identify the bridge chip on the board before selecting a driver.
- **V1.3 is not pin-compatible:** LoRa RESET moves from GPIO14 (V1.3) to GPIO23 (V1.6/V1.6.1), and V1.3 has no SD slot in the pin map.

## Demo

[`examples/lora-ping-pong`](../../examples/lora-ping-pong/README.md) builds for this board: a ping/pong link test that reports RSSI and SNR in both directions. Untested on hardware.

## Applications

- **LoRa receiver with local logging.** Packets to the microSD card, status on the SSD1306. Remove the card before each sketch upload.
- **Field sensor node.** Battery powered, OLED for local readout during installation, LoRa uplink to a base station. No battery protection circuit is present, so the cell must have its own.
- **Meshtastic node.** LilyGO lists Meshtastic as a supported application for this board.
- **Point-to-point link test.** See [`examples/lora-ping-pong`](../../examples/lora-ping-pong/README.md); this board interoperates with the SX1262 kit.

## Files

- `wiki/t3-lora32-v1.6.1-hardware.md`: LilyGO's own hardware page for this board (pins, electrical, RF, IPEX mod), with `wiki/img/`
- `hardware/schematic-v1.6.1.pdf`, `hardware/dimensions-v1.6.dwg`, `hardware/3d-model-v1.6.7z`
- `reference/utilities.h`: the vendor pin header covering every T3/T-Beam variant (see the `T3_V1_6_SX1276` block)
- `reference/lilygo-platformio.ini`: the vendor `platformio.ini` with every board env
