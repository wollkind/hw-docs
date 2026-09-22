# Espressif ESP32-C5-DevKitC-1 (v1.2)

Espressif's ESP32-C5 board: an ESP32-C5-WROOM-1(U) module, two USB-C ports and the GPIO on 2 × 16 headers. Chip: [`chips/esp32-c5`](../../chips/esp32-c5/README.md) — the only **dual-band (2.4 and 5 GHz) Wi-Fi 6** part in this library.
Used by: `pio-seafive`, which builds `board = esp32-c5-devkitc1-n4` for **two separate MCUs** (`mcu_a` and `mcu_b`) from one project, with an SSD1306 display and MicroNMEA GPS on the B side.

## Key specs

| | |
|---|---|
| Module | ESP32-C5-WROOM-1 (PCB antenna) or -1U (external connector) |
| Radios | Wi-Fi 6 on 2.4 **and 5 GHz**, Bluetooth 5 LE, 802.15.4 (Thread, Zigbee) |
| USB | **Two USB-C ports.** One is the ESP32-C5's own USB 2.0 full speed (12 Mbps; flashing, CDC, JTAG). The other goes through a USB-to-UART bridge at up to 3 Mbps |
| Power | 5 V to 3.3 V DC/DC. Three mutually exclusive supplies: either USB-C port, the 5V header, or the 3V3 header |
| RGB LED | Addressable, **driven by GPIO27** |
| Buttons | Boot and Reset. Hold Boot, press Reset for firmware download mode |
| J5 | Current-measurement header, jumper fitted from the factory |

## Pinout

J1 and J3 from the v1.2 user guide, in header order. **Strapping pins are marked**; per the chip entry they are GPIO7, 25, 26, 27, 28, MTMS (GPIO2) and MTDI (GPIO3).

### J1

| No. | Name | Function |
|---|---|---|
| 1 | 3V3 | 3.3 V supply |
| 2 | RST | High enables the chip, low disables it |
| 3 | 2 | **Strapping.** MTMS, GPIO2, LP_GPIO2, LP_UART_RTSN, LP_I2C_SDA, ADC1_CH1, FSPIQ |
| 4 | 3 | **Strapping.** MTDI, GPIO3, LP_GPIO3, LP_UART_CTSN, LP_I2C_SCL, ADC1_CH2 |
| 5 | 0 | GPIO0, XTAL_32K_P, LP_GPIO0, LP_UART_DTRN |
| 6 | 1 | GPIO1, XTAL_32K_N, LP_GPIO1, LP_UART_DSRN, ADC1_CH0 |
| 7 | 6 | GPIO6, LP_GPIO6, ADC1_CH5, FSPICLK |
| 8 | 7 | **Strapping.** GPIO7, FSPID, SDIO_DATA1 |
| 9 | 8 | GPIO8, PAD_COMP0, SDIO_DATA0 |
| 10 | 9 | GPIO9, PAD_COMP1, SDIO_CLK |
| 11 | 10 | GPIO10, FSPICS0, SDIO_CMD |
| 12 | 26 | **Strapping.** GPIO26 |
| 13 | 25 | **Strapping.** GPIO25 |
| 14 | 5V | 5 V supply |
| 15 | G | Ground |
| 16 | NC | Not connected |

### J3

| No. | Name | Function |
|---|---|---|
| 1 | G | Ground |
| 2 | TX | U0TXD, GPIO11 |
| 3 | RX | U0RXD, GPIO12 |
| 4 | 24 | GPIO24 |
| 5 | 23 | GPIO23 |
| 6 | NC/15 | Not connected, or GPIO15 depending on the board |
| 7 | 27 | **Strapping, and the RGB LED.** GPIO27 |
| 8 | 4 | MTCK, GPIO4, LP_GPIO4, LP_UART_RXD, ADC1_CH3, FSPIHD |
| 9 | 5 | MTDO, GPIO5, LP_GPIO5, LP_UART_TXD, ADC1_CH4, FSPIWP |
| 10 | NC | Not connected |
| 11 | 28 | **Strapping.** GPIO28 |
| 12 | G | Ground |
| 13 | 14 | GPIO14, **USB_D+**, SDIO_DATA2 |
| 14 | 13 | GPIO13, **USB_D-**, SDIO_DATA3 |
| 15 | G | Ground |
| 16 | NC | Not connected |

**J1 and J3 changed within v1.2:** boards from PW-2025-04-0446 onward have updated header functions, and the tables above are the updated ones. An earlier v1.2 board, or a v1.1, does not match.

## PlatformIO config

`pio-seafive` builds every env from a shared `[env]`:

```ini
[env]
platform = https://github.com/pioarduino/platform-espressif32/releases/download/stable/platform-espressif32.zip
board = esp32-c5-devkitc1-n4
framework = arduino
monitor_speed = 115200
build_flags = -DCORE_DEBUG_LEVEL=0
board_upload.before_reset = no-reset
board_upload.after_reset = no-reset
upload_speed = 460800
```

The board id is `esp32-c5-devkitc1-n4` — the 4 MB in-package-flash variant — not the `esp32-c5-devkitc-1` spelling the documentation uses for the kit. `no-reset` before and after upload is that project's choice, not a board requirement.

## Operational notes

- **GPIO27 drives the RGB LED and is a strapping pin** that is pulled up by default and takes part in boot-mode selection. Anything else on GPIO27 that can pull it low changes how the board boots.
- **Seven strapping pins, five of them on the headers** (GPIO2, 3, 7, 25, 26, 27, 28). This board has more straps in the way than the C3 or C6 kits.
- **GPIO13/14 are the native USB port**, so taking them as GPIO costs the USB-C port that does CDC and JTAG.
- **5 GHz is the reason for this part.** Nothing else here reaches the 5 GHz band, which matters where 2.4 GHz is congested.
- **Two CAN FD controllers** are in the chip; a transceiver still has to be added.
- **Three power options, mutually exclusive.** When powering from the 3V3 header, pull the J5 jumper and put the ammeter between the supply and 3V3 — the 3V3 header feeds the module directly, bypassing J5.
- **SDIO slave does not work on chip revisions v0.0 and v0.1** (chip datasheet), and the errata in the chip entry list PSRAM, SRAM power-down and flash-encryption items worth reading before relying on those features.

## Applications

- **Dual-band Wi-Fi 6 node**, where 5 GHz or TWT power saving is the point.
- **Thread or Zigbee device with a 5 GHz uplink** — one chip covers both radios.
- **Two-MCU designs** such as `pio-seafive`, which splits its firmware into `mcu_a` and `mcu_b` build environments against this same board.
- **CAN FD work**, with an external transceiver.
- **Unsuitable for:** anything needing lots of free GPIO — 29 on the chip, seven of them strapping — and for designs that assume the C6's pin numbering.

## Files

- `wiki/user-guide.md`: Espressif's v1.2 user guide, with images
- `hardware/schematic-v1.2.pdf`, `hardware/pcb-layout-v1.2.pdf`, `hardware/dimensions-v1.2.pdf`
- `hardware/esp32-c5-wroom-1_datasheet_en.pdf`: the module datasheet (WROOM-1 and -1U)
