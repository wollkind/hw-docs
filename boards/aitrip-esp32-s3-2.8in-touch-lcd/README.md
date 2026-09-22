# AITRIP 2.8" ESP32-S3 touchscreen module (Amazon B0GGF7C46X) — **provisional entry**

Reseller-branded ESP32-S3 smart display: 2.8" 240×320 IPS with capacitive touch. **The real vendor design has not been identified**, and no pin map is recorded here — see "What is still unknown". Chip: [../../chips/esp32-s3](../../chips/esp32-s3/README.md).
Used by: no project.

## What is known

All of it is relayed from the Amazon listing text through a web search, because amazon.com is blocked from this sandbox. Treat every line as `(unverified)` until checked against the board:

| | |
|---|---|
| MCU module | ESP32-S3-R2 (i.e. 2 MB PSRAM); flash size not stated |
| Display | 2.8" IPS, 240×320, 262 K colours (RGB666) |
| Display driver | **ST7789P3** |
| Touch | capacitive, **FT6336U** |
| Wireless | 2.4 GHz Wi-Fi, Bluetooth 5.0 LE |
| Other | USB-C; the listing mentions an RS485 interface |

"AITRIP" is a reseller label. The same board appears on Amazon under several other sellers (B0GGBCMWCQ, B0GCN2SC3W, B0GT2TK9VF, B0GPXBS8XJ) with identical photos and wording, which is the usual sign of a white-label Shenzhen design rather than a documented product. It is **not** the Waveshare ESP32-S3-Touch-LCD-2.8, which is a different board sold under its own name with its own wiki.

## What is still unknown

Everything that matters for writing code:

- Which GPIOs drive the LCD (SPI or 8-bit parallel — ST7789P3 supports both), the backlight, and the FT6336U's I2C bus and interrupt
- Flash size and whether the PSRAM is octal or quad
- Whether the RS485 transceiver is populated on this SKU and which UART it uses
- Whether there is a microSD slot, and on which bus

## How to pin it down

1. Photograph the silkscreen on both sides. These boards normally carry a model code near the module (for example the `JC…` or `ZX…` codes used by the common CYD-family vendors); that code is what to search for.
2. Read the USB descriptor: `lsusb -v` or `esptool.py flash_id` gives the flash size and the chip revision, which settles ESP32-S3-R2 vs other variants.
3. With the board in hand, `i2cdetect`-style scan on the candidate pins finds the FT6336U (typically 0x38 `(unverified)`).
4. If the model code turns up a vendor demo repository, file the real entry under the vendor's name and delete this folder — the queue note asked for exactly that.

## Applications

Not stated. The board is unidentified and no pin map is recorded, so no application can be described without guessing which GPIO drives the display. Complete the identification steps above first.

## Files

None yet. No schematic, datasheet or demo code has been located for this board.
