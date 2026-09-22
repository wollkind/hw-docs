# Espressif ESP32-C3-DevKitC-02

Espressif's entry-level ESP32-C3 board: an ESP32-C3-WROOM-02 module with 4 MB flash, a micro-USB port through a USB-to-UART bridge, and the GPIO on 2 × 15 headers. Chip: [`chips/esp32-c3`](../../chips/esp32-c3/README.md).
Used by: `pio-blink` (`[env:esp32-c3]`).

## Key specs

| | |
|---|---|
| Module | ESP32-C3-WROOM-02 (PCB antenna) or -02U (external antenna connector), **4 MB SPI flash** |
| Radios | Wi-Fi 4 2.4 GHz and Bluetooth 5 LE, coexisting |
| USB | **Micro-USB**, through a USB-to-UART bridge at up to 3 Mbps. The chip's own USB Serial/JTAG pins (GPIO18/19) are on the header, not on the connector |
| Power | 5 V to 3.3 V LDO. Three mutually exclusive supplies: micro-USB (recommended), the 5V headers, or the 3V3 headers |
| RGB LED | Addressable, **driven by GPIO8** |
| Buttons | Boot and Reset. Hold Boot, press Reset for firmware download mode |

There is one hardware version; the user guide lists no previous revisions.

## Pinout

The J1 and J3 tables from the user guide, in header order.

### J1

| No. | Name | Function |
|---|---|---|
| 1 | G | Ground |
| 2, 3 | 3V3 | 3.3 V supply |
| 4 | RST | CHIP_PU |
| 5 | G | Ground |
| 6 | 4 | GPIO4, ADC1_CH4, FSPIHD, MTMS |
| 7 | 5 | GPIO5, ADC2_CH0, FSPIWP, MTDI |
| 8 | 6 | GPIO6, FSPICLK, MTCK |
| 9 | 7 | GPIO7, FSPID, MTDO |
| 10 | G | Ground |
| 11 | 8 | **Strapping, and the RGB LED.** GPIO8 |
| 12 | 9 | **Strapping.** GPIO9 |
| 13, 14 | 5V | 5 V supply |
| 15 | G | Ground |

### J3

| No. | Name | Function |
|---|---|---|
| 1 | G | Ground |
| 2 | 0 | GPIO0, ADC1_CH0, XTAL_32K_P |
| 3 | 1 | GPIO1, ADC1_CH1, XTAL_32K_N |
| 4 | 2 | **Strapping.** GPIO2, ADC1_CH2, FSPIQ |
| 5 | 3 | GPIO3, ADC1_CH3 |
| 6 | G | Ground |
| 7 | 10 | GPIO10, FSPICS0 |
| 8 | G | Ground |
| 9 | RX | GPIO20, U0RXD |
| 10 | TX | GPIO21, U0TXD |
| 11 | G | Ground |
| 12 | 18 | GPIO18, **USB_D-** |
| 13 | 19 | GPIO19, **USB_D+** |
| 14, 15 | G | Ground |

The SPI bus to the module's flash is not brought out.

## PlatformIO config

`pio-blink` builds it as:

```ini
[env:esp32-c3]
board = esp32-c3-devkitc-02
framework = arduino
build_flags = -D LED_BUILTIN=8
```

The board file sets `mcu esp32c3`, `variant esp32c3`, `-DARDUINO_ESP32C3_DEV`, 160 MHz, `flash_mode qio` at 80 MHz, `flash_size 4MB`, upload speed 460800. The variant defines no `LED_BUILTIN`, hence the project's own `-D LED_BUILTIN=8` — and 8 is correct here, since GPIO8 is the addressable LED. Note that `LED_BUILTIN` with `digitalWrite` toggles the WS2812's data line rather than lighting it properly; `neopixelWrite(8, r, g, b)` is the call that drives it.

## Operational notes

- **GPIO8 is both the RGB LED and a strapping pin.** Per the chip entry, GPIO8 = 1 with GPIO9 = 0 selects download boot. Anything else on GPIO8 that can pull it low at reset changes the boot mode.
- **GPIO9 has the weak pull-up** and is the pin the Boot button pulls down; GPIO2 should be left pulled up.
- **The micro-USB port is not the chip's native USB.** Flashing goes through the bridge; the chip's USB Serial/JTAG sits on GPIO18/19 at the header and needs wiring up to be used.
- **Only 4 MB flash and no PSRAM.** An Arduino sketch with a large filesystem or a display frame buffer will not fit.
- **Three power options, mutually exclusive.** Do not feed 5V or 3V3 with USB connected.
- **ADC2's DMA path is broken in silicon** ([ADC-183] in the chip errata) — use ADC1 channels, which on this board are GPIO0–5.

## Applications

- **Small Wi-Fi/BLE node**, where the C3's single RISC-V core and 4 MB flash are enough and the price is the point.
- **Bring-up board for RISC-V toolchain work**, with JTAG available over the chip's own USB pins.
- **TWAI/CAN experiments** — the C3 has the controller; a transceiver has to be added.
- **Unsuitable for:** PSRAM-hungry work, 802.15.4 (use the C6 kit), and anything needing more than the ~13 usable GPIO the headers expose.

## Files

- `wiki/user-guide.md`: Espressif's user guide, with images
- `hardware/schematic-v1.1.pdf`, `hardware/dimensions-v1.1.pdf`, `hardware/pcb-layout-v1.1.pdf`
- `hardware/esp32-c3-wroom-02_datasheet_en.pdf`: the module datasheet (WROOM-02 and -02U)
- `reference/platformio-board.json`: the `esp32-c3-devkitc-02` board definition
