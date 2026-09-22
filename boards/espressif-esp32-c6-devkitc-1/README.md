# Espressif ESP32-C6-DevKitC-1 (v1.2)

Espressif's entry-level ESP32-C6 board: an ESP32-C6-WROOM-1 module with 8 MB flash, two USB-C ports, and every GPIO except the flash bus on 2 × 16 headers. Chip: [`chips/esp32-c6`](../../chips/esp32-c6/README.md).
Used by: `pio-blink` (`[env:esp32-c6]`).

## Key specs

| | |
|---|---|
| Module | ESP32-C6-WROOM-1 (PCB antenna) or -1U (external antenna connector), **8 MB SPI flash** |
| Radios | Wi-Fi 6 2.4 GHz, Bluetooth 5 LE, 802.15.4 (Zigbee 3.0, Thread 1.3) |
| USB | **Two USB-C ports.** One is the ESP32-C6's own USB 2.0 full-speed port (12 Mbps; flashing, CDC and JTAG debugging). The other goes through a USB-to-UART bridge, up to 3 Mbps |
| Power | 5 V to 3.3 V LDO. Three mutually exclusive supplies: either USB-C port, the 5V header, or the 3V3 header |
| RGB LED | Addressable WS2812-type, **driven by GPIO8** |
| Buttons | Boot and Reset. Hold Boot, press Reset for firmware download mode |
| J5 | Current-measurement header. Jumper fitted from the factory; remove it and put an ammeter across J5 to read module current |

## Pinout

The J1 and J3 tables from the v1.2 user guide, in header order.

### J1

| No. | Name | Function |
|---|---|---|
| 1 | 3V3 | 3.3 V supply |
| 2 | RST | High enables the chip, low disables it |
| 3 | 4 | **Strapping.** MTMS, GPIO4, LP_GPIO4, LP_UART_RXD, ADC1_CH4, FSPIHD |
| 4 | 5 | **Strapping.** MTDI, GPIO5, LP_GPIO5, LP_UART_TXD, ADC1_CH5, FSPIWP |
| 5 | 6 | MTCK, GPIO6, LP_GPIO6, LP_I2C_SDA, ADC1_CH6, FSPICLK |
| 6 | 7 | MTDO, GPIO7, LP_GPIO7, LP_I2C_SCL, FSPID |
| 7 | 0 | GPIO0, XTAL_32K_P, LP_GPIO0, LP_UART_DTRN, ADC1_CH0 |
| 8 | 1 | GPIO1, XTAL_32K_N, LP_GPIO1, LP_UART_DSRN, ADC1_CH1 |
| 9 | 8 | **Strapping, and the RGB LED.** GPIO8 |
| 10 | 10 | GPIO10 |
| 11 | 11 | GPIO11 |
| 12 | 2 | GPIO2, LP_GPIO2, LP_UART_RTSN, ADC1_CH2, FSPIQ |
| 13 | 3 | GPIO3, LP_GPIO3, LP_UART_CTSN, ADC1_CH3 |
| 14 | 5V | 5 V supply |
| 15 | G | Ground |
| 16 | NC | Not connected |

### J3

| No. | Name | Function |
|---|---|---|
| 1 | G | Ground |
| 2 | TX | U0TXD, GPIO16, FSPICS0 |
| 3 | RX | U0RXD, GPIO17, FSPICS1 |
| 4 | 15 | **Strapping.** GPIO15 |
| 5 | 23 | GPIO23, SDIO_DATA3 |
| 6 | 22 | GPIO22, SDIO_DATA2 |
| 7 | 21 | GPIO21, SDIO_DATA1, FSPICS5 |
| 8 | 20 | GPIO20, SDIO_DATA0, FSPICS4 |
| 9 | 19 | GPIO19, SDIO_CLK, FSPICS3 |
| 10 | 18 | GPIO18, SDIO_CMD, FSPICS2 |
| 11 | 9 | **Strapping.** GPIO9 |
| 12 | G | Ground |
| 13 | 13 | GPIO13, **USB_D+** |
| 14 | 12 | GPIO12, **USB_D-** |
| 15 | G | Ground |
| 16 | NC | Not connected |

The SPI bus to the module's flash is not brought out at all, which is why GPIO24–30 are missing from the headers.

## PlatformIO config

`pio-blink` builds it as:

```ini
[env:esp32-c6]
board = esp32-c6-devkitc-1
framework = arduino
```

The board file sets `mcu esp32c6`, `variant esp32c6`, 160 MHz, `flash_mode qio` at 80 MHz, `flash_size 8MB` and upload speed 460800. It declares no PSRAM — the WROOM-1 module on this kit has none.

`pio-blink` reaches it through `platform = file://C:/Users/steve/pio-esp32-55.03.311`, a local platform fork that resolves on the owner's machine only. On any other machine use the pioarduino release zip, as the other projects do.

## Operational notes

- **GPIO8 drives the RGB LED and is a strapping pin.** Per the chip entry, GPIO8 with GPIO9 selects the boot mode, and the WS2812 circuit hangs on it. It works because the LED presents a high impedance at reset, but a second device on GPIO8 that pulls it can send the board into download mode.
- **GPIO12/13 are the native USB port.** Taking them as GPIO costs the USB-C port that does CDC and JTAG.
- **Five straps to keep clear of at reset:** GPIO4, 5, 8, 9 and 15, all on the headers. GPIO9 is the one with a weak pull-up.
- **Both USB-C ports can power the board, but the three supply options are mutually exclusive** — do not feed 5V or 3V3 headers while a USB cable is connected.
- **When powering from the 3V3 header, pull the J5 jumper** and put the ammeter in series externally, as the user guide instructs.
- **Revisions matter for two circuits:** boards after PW-2023-07-0440 changed the WS2812 drive resistors (R29 4.7 kΩ → 10 kΩ, R6 10 kΩ → 3.3 kΩ, schematic v1.3), and boards after PW-2024-03-0595 put 470 Ω in series with UART_RXD in place of 0 Ω (schematic v1.4). `hardware/schematics_v1.4.pdf` here is the newest; the v1.2 and v1.3 PDFs are linked in `sources.md` if an older board turns up.
- ADC calibration changed too: boards from July 2023 use multi-point calibration, and the datasheet's ADC characteristics apply to those only.

## Applications

- **Thread or Zigbee border work.** The 802.15.4 radio is the reason to reach for this board over an ESP32-C3 or -S3 kit.
- **Wi-Fi 6 client testing** against an AX access point, where the point is the radio rather than any onboard peripheral.
- **Low-power experiments** with the LP core and LP_I2C/LP_UART pins, which are broken out on J1 (GPIO0–7).
- **Current profiling** of a module without cutting a trace, via the J5 jumper.
- **Unsuitable for:** anything wanting PSRAM (the module has none), or a board with sensors already fitted — this kit has an LED and nothing else.

## Files

- `wiki/user-guide.md`: Espressif's v1.2 user guide, with images
- `hardware/schematics_v1.4.pdf`: current schematic
- `hardware/dimensions_v1.2.pdf`, `hardware/pcb-layout_v1.2.pdf`
- `hardware/esp32-c6-wroom-1_datasheet_en.pdf`: the module datasheet (WROOM-1 and -1U)
- `reference/platformio-board.json`: the `esp32-c6-devkitc-1` board definition
