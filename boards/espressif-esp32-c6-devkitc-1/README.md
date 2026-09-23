# Espressif ESP32-C6-DevKitC-1 (v1.2; schematics v1.2 / v1.3 / v1.4)

Espressif's entry-level ESP32-C6 board: ESP32-C6-WROOM-1 (PCB antenna) or -WROOM-1U (external antenna), 8 MB flash, two USB-C ports (CP2102N UART bridge + native USB), addressable RGB LED, current-measurement jumper. Chip: [../../chips/esp32-c6](../../chips/esp32-c6/README.md).
Used by: `pio-blink` (env `esp32-c6`, `board = esp32-c6-devkitc-1`). `MISSION.md` lists `esp32-c6-devkitc-1` among the outstanding board ids.

## Key specs

| | |
|---|---|
| Module | ESP32-C6-WROOM-1 or -1U: HP RISC-V up to 160 MHz + LP RISC-V up to 20 MHz, Wi-Fi 6 (2.4 GHz), Bluetooth 5 LE, IEEE 802.15.4 (Zigbee 3.0, Thread 1.3), **8 MB SPI flash, no PSRAM** |
| USB | two USB-C: **"USB Type-C to UART"** via CP2102N (up to 3 Mbps) on U0TXD/U0RXD, and **"ESP32-C6 USB Type-C"** native USB-Serial-JTAG (12 Mbps full speed) on GPIO12/13 |
| Power | either or both USB-C (default), or 5V/GND header, or 3V3/GND header — mutually exclusive. SGM2212-3.3 LDO |
| RGB LED | addressable WS2812B on GPIO8 |
| Buttons | Boot (GPIO9), Reset |
| J5 | current-measurement jumper in the module's 3.3 V feed (fitted by default) |
| LED | 3.3 V power-on LED |

## Revisions

| Schematic | Applies to | Change |
|---|---|---|
| v1.1 | initial release | separate guide (`user_guide_v1.1.html`, not fetched) |
| v1.2 | before PW-2023-07-0440 | from PW-2023-02-0139, J5 changed from straight to curved headers |
| v1.3 | from PW-2023-07-0440 | WS2812 drive: R29 4.7 kΩ → 10 kΩ, R6 10 kΩ → 3.3 kΩ |
| v1.4 | from PW-2024-03-0595 / -0921 | R7 on UART_RXD 0 Ω → 470 Ω |

The PW number is on the wholesale box label; a loose board gives no way to tell v1.2/1.3/1.4 apart without reading R6/R29/R7.

## Pinout

Source: Espressif user guide header tables (`wiki/user-guide.md`); numbering matches schematic v1.2.

**J1**

| Pin | Name | Function |
|---|---|---|
| 1 | 3V3 | 3.3 V |
| 2 | RST | chip enable (high = run) |
| 3 | 4 | MTMS (strapping), GPIO4, LP_GPIO4, LP_UART_RXD, ADC1_CH4, FSPIHD |
| 4 | 5 | MTDI (strapping), GPIO5, LP_GPIO5, LP_UART_TXD, ADC1_CH5, FSPIWP |
| 5 | 6 | MTCK, GPIO6, LP_GPIO6, **LP_I2C_SDA**, ADC1_CH6, FSPICLK |
| 6 | 7 | MTDO, GPIO7, LP_GPIO7, **LP_I2C_SCL**, FSPID |
| 7 / 8 | 0 / 1 | GPIO0 XTAL_32K_P ADC1_CH0 / GPIO1 XTAL_32K_N ADC1_CH1 (also LP_UART_DTRN/DSRN) |
| 9 | 8 | GPIO8 (strapping), RGB LED |
| 10 / 11 | 10 / 11 | GPIO10 / GPIO11 |
| 12 / 13 | 2 / 3 | GPIO2 ADC1_CH2 FSPIQ / GPIO3 ADC1_CH3 |
| 14 | 5V | 5 V |
| 15 | G | GND |
| 16 | NC | — |

**J3**

| Pin | Name | Function |
|---|---|---|
| 1, 12, 15 | G | GND |
| 2 / 3 | TX / RX | GPIO16 U0TXD / GPIO17 U0RXD (to the CP2102N) |
| 4 | 15 | GPIO15 (strapping) |
| 5–10 | 23, 22, 21, 20, 19, 18 | SDIO DATA3/DATA2/DATA1/DATA0/CLK/CMD |
| 11 | 9 | GPIO9 (strapping), Boot button |
| 13 / 14 | 13 / 12 | GPIO13 USB_D+ / GPIO12 USB_D- (native USB port) |
| 16 | NC | — |

**Arduino core defaults** (`reference/arduino-esp32-pins_arduino.h`, generic `esp32c6` variant): SDA 23, SCL 22, SPI SCK/MISO/MOSI/SS 21/20/19/18, TX/RX 16/17, A0–A6 = GPIO0–6, LP I2C `SDA1`/`SCL1` = 6/7 (fixed), `PIN_RGB_LED` 8, `LED_BUILTIN` = `SOC_GPIO_PIN_COUNT + 8` (virtual pin, `digitalWrite()` drives the RGB LED).

## PlatformIO

As in `pio-blink` (the `[env]` block points `platform` at a local pioarduino copy, `file://C:/Users/steve/pio-esp32-55.03.311`):

```ini
[env:esp32-c6]
board = esp32-c6-devkitc-1
```

**Verified: builds** on 2026-09-23 against the public pioarduino 55.03.311 release (Arduino core 3.3.11). Upload not tested.

**Needs pioarduino.** Upstream `platformio/platform-espressif32` defines `esp32-c6-devkitc-1` for `espidf` only (no Arduino, no variant). pioarduino's definition (`reference/platformio-board.json`) adds `arduino`, variant `esp32c6`, Bluetooth, 160 MHz, QIO 80 MHz, 8 MB. No `ARDUINO_USB_CDC_ON_BOOT`, so `Serial` goes to UART0 = the CP2102N port, not the native USB-C port `(inferred from the board file; not checked on hardware)`.

## Operational notes

- **Strapping pins: GPIO4 (MTMS), GPIO5 (MTDI), GPIO8, GPIO9, GPIO15** (user guide footnote and chip datasheet). GPIO9 = Boot button, GPIO8 = RGB LED.
- **Current measurement:** remove J5 and put an ammeter across it to read the module's current alone. When powering from the 3V3 header, remove J5 and put the ammeter in series with the external supply.
- **Two USB ports, either can power the board.** Flashing works through both: the UART port via esptool auto-reset, the native port via USB-Serial-JTAG.
- **LP I2C is fixed on GPIO6/7** (used by the LP core); the HP I2C default is 23/22.
- **No PSRAM.**

## Applications

- **Thread / Zigbee end device or Matter-over-Thread node** using the 802.15.4 radio, with the RGB LED as state indicator.
- **Wi-Fi 6 low-power sensor** with the LP RISC-V core polling an LP-I2C sensor on GPIO6/7 while the HP core sleeps; J5 measures the resulting current.
- **JTAG-debuggable firmware development** over the native USB-C port without an external probe.
- Unsuitable for PSRAM-dependent work (displays, audio buffers) or 5 GHz Wi-Fi (2.4 GHz only).

## Files

- `hardware/schematic-v1.2.pdf`, `schematic-v1.3.pdf`, `schematic-v1.4.pdf`
- `hardware/pcb-layout-v1.2.pdf`, `hardware/dimensions-v1.2.pdf`
- `datasheets/esp32-c6-wroom-1_wroom-1u_datasheet_en.pdf`: module datasheet
- `reference/platformio-board.json`: pioarduino `esp32-c6-devkitc-1` board definition
- `reference/arduino-esp32-pins_arduino.h`: generic `esp32c6` Arduino variant header
- `wiki/user-guide.md`: Espressif user guide (v1.2) with block diagram and pin-layout images
