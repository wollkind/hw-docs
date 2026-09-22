# Semtech SX1276 / SX1277 / SX1278 / SX1279 LoRa transceiver

Sub-GHz LoRa and (G)FSK/OOK transceiver in a QFN-28 package, driven over SPI. The radio on the [LilyGO T3 LoRa32 V1.6.1](../../boards/lilygo-t3-lora32-v1.6.1/README.md) and on Adafruit's RFM95-class modules.
Used by: `examples/lora-ping-pong` in this repository (the SX1276 side of the link).

## Variants

One datasheet covers four parts, which differ only in frequency coverage and spreading factors:

| Part | Frequency range | Spreading factors | Bandwidth | Effective bit rate | Sensitivity |
|---|---|---|---|---|---|
| SX1276 | 137–1020 MHz | 6–12 | 7.8–500 kHz | 0.018–37.5 kbps | −111 to −148 dBm |
| SX1277 | 137–1020 MHz | 6–9 | 7.8–500 kHz | 0.11–37.5 kbps | −111 to −139 dBm |
| SX1278 | **137–525 MHz** | 6–12 | 7.8–500 kHz | 0.018–37.5 kbps | −111 to −148 dBm |
| SX1279 | 137–960 MHz | 6–12 | 7.8–500 kHz | 0.018–37.5 kbps | −111 to −148 dBm |

The SX1276 and SX1278 are the two that appear on the boards here; a board sold as "SX1276/SX1278" is usually one part number per frequency band, not a dual-band radio.

## Key specs

| | |
|---|---|
| Link budget | up to 168 dB |
| TX power | +20 dBm (100 mW) constant against supply, or +14 dBm from the high-efficiency PA |
| Sensitivity | down to −148 dBm |
| RX current | 9.9 mA; 200 nA in register-retention |
| Modulations | LoRa, FSK, GFSK, MSK, GMSK, OOK |
| Synthesiser | fully integrated, 61 Hz resolution |
| Packet engine | up to 256 bytes with CRC |
| RSSI | 127 dB dynamic range |
| Extras | built-in temperature sensor, low-battery indicator, automatic RF sense and channel activity detection with fast AFC |
| Package | QFN-28, −40 to +85 °C |
| Front end | IIP3 = −11 dBm |

## Operational notes

- **There are two RF paths.** `RFI_LF` and `RFI_HF` are separate receive inputs, and the transmit side has `PA_BOOST` beside `RFO`. A module wired for PA_BOOST needs the driver told so, or the output is roughly 20 dB down. This is the usual cause of "it transmits but nothing hears it".
- **DIO0–DIO5 are mapped by register**, not fixed. A library needs the same mapping the board wired — DIO0 as TxDone/RxDone is the common arrangement.
- **The SX1278 stops at 525 MHz.** A 915 MHz configuration on an SX1278 board will not work no matter what the software says.
- **Spreading factor 6 is a special case** in the LoRa modem: implicit header only, and it needs its own detection-optimise and threshold register settings.
- The maximum useful payload with the packet engine is 256 bytes, and LoRa's own limits are tighter at high spreading factors; `examples/lora-ping-pong` in this repository documents a small fixed packet format for that reason.

## Files

- `datasheets/sx1276-77-78-79-datasheet-rev4.pdf`: Semtech's datasheet, Rev 4, March 2015, 132 pages
