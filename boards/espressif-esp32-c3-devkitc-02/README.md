# Espressif ESP32-C3-DevKitC-02 (v1.1)

Espressif's entry-level ESP32-C3 board: ESP32-C3-WROOM-02 (PCB antenna) or -WROOM-02U (external antenna), 4 MB flash, CP2102N USB-UART on a Micro-USB port, addressable RGB LED. Chip: [../../chips/esp32-c3](../../chips/esp32-c3/README.md).
Used by: `pio-blink` (env `esp32-c3`, `board = esp32-c3-devkitc-02`). `MISSION.md` lists `esp32-c3-devkitc-02` among the outstanding board ids.

## Key specs

| | |
|---|---|
| Module | ESP32-C3-WROOM-02 or -02U: single-core RISC-V 160 MHz, Wi-Fi 4 + BLE 5, **4 MB SPI flash, no PSRAM** |
| USB | **Micro-USB → CP2102N USB-UART bridge** (up to 3 Mbps) on U0TXD/U0RXD. The chip's native USB (GPIO18/19) goes only to header pins J3-12/13, not to a connector |
| Power | Micro-USB (default), or 5V/GND header, or 3V3/GND header — mutually exclusive. SGM2212-3.3 LDO (5 V → 3.3 V) |
| RGB LED | addressable, GPIO8 (SK68XXMINI-HS per the schematic) |
| Buttons | Boot (GPIO9), Reset (CHIP_PU) |
| LED | 5 V power-on LED |
| Revision | v1.1 is the only version ("No previous versions available") |

## Pinout

Source: Espressif user guide header tables (`wiki/user-guide.md`); numbering matches the schematic.

**J1**

| Pin | Name | Function |
|---|---|---|
| 1, 5, 10, 15 | G | GND |
| 2, 3 | 3V3 | 3.3 V |
| 4 | RST | CHIP_PU |
| 6 | 4 | GPIO4, ADC1_CH4, FSPIHD, MTMS |
| 7 | 5 | GPIO5, ADC2_CH0, FSPIWP, MTDI |
| 8 | 6 | GPIO6, FSPICLK, MTCK |
| 9 | 7 | GPIO7, FSPID, MTDO |
| 11 | 8 | GPIO8 (strapping), RGB LED |
| 12 | 9 | GPIO9 (strapping), Boot button |
| 13, 14 | 5V | 5 V |

**J3**

| Pin | Name | Function |
|---|---|---|
| 1, 6, 8, 11, 14, 15 | G | GND |
| 2 / 3 | 0 / 1 | GPIO0 ADC1_CH0 XTAL_32K_P / GPIO1 ADC1_CH1 XTAL_32K_N |
| 4 | 2 | GPIO2 (strapping), ADC1_CH2, FSPIQ |
| 5 | 3 | GPIO3, ADC1_CH3 |
| 7 | 10 | GPIO10, FSPICS0 |
| 9 / 10 | RX / TX | GPIO20 U0RXD / GPIO21 U0TXD (to the CP2102N) |
| 12 / 13 | 18 / 19 | GPIO18 USB_D- / GPIO19 USB_D+ |

**Arduino core defaults** (`reference/arduino-esp32-pins_arduino.h`, generic `esp32c3` variant): SDA 8, SCL 9, SPI SCK/MISO/MOSI/SS 4/5/6/7, TX/RX 21/20, A0–A5 = GPIO0–5, `PIN_RGB_LED` 8, `LED_BUILTIN` = `SOC_GPIO_PIN_COUNT + 8` (a virtual pin that routes `digitalWrite()` to the RGB LED). The default SDA/SCL land on the two strapping pins used by the LED and Boot button.

## PlatformIO

As in `pio-blink` (the `[env]` block points `platform` at a local pioarduino copy, `file://C:/Users/steve/pio-esp32-55.03.311`):

```ini
[env:esp32-c3]
board = esp32-c3-devkitc-02
build_flags =
      ${env.build_flags}
      -D LED_BUILTIN=8
```

**This env does not compile.** Built on 2026-09-23 against the public pioarduino 55.03.311 release (Arduino core 3.3.11): `-D LED_BUILTIN=8` turns the variant's `static const uint8_t LED_BUILTIN = …` into `static const uint8_t 8 = …` → `error: expected unqualified-id before numeric constant`. The owner's local platform copy was not available; it is assumed to carry the same variant header `(unverified)`. Fix: drop the `-D LED_BUILTIN=8` line. The variant's own `LED_BUILTIN` already drives the RGB LED on GPIO8 through `digitalWrite()`. Driving GPIO8 as a plain GPIO does not light an addressable LED reliably.

Board definition (`reference/platformio-board.json`): `-DARDUINO_ESP32C3_DEV`, 160 MHz, QIO flash 80 MHz, 4 MB, variant `esp32c3`, upload 460800. No `ARDUINO_USB_CDC_ON_BOOT`, so `Serial` is UART0 through the CP2102N — which is what the Micro-USB port carries.

## Operational notes

- **Strapping pins GPIO2, GPIO8, GPIO9** (Espressif footnote). GPIO9 is the Boot button (low at reset = download mode); GPIO8 carries the RGB LED. External pull-downs on either affect boot. See `chips/esp32-c3` for the boot-mode table.
- **Download mode:** hold Boot, press Reset. Automatic reset via the CP2102N's DTR/RTS also works with esptool `(auto-reset transistor pair not traced in the schematic here)`.
- **Single core.** `xTaskCreatePinnedToCore(..., 1)` fails on C3.
- **No PSRAM.** Only on-chip SRAM is available for buffers.
- **Native USB is only on header pins 18/19.** USB-JTAG debugging needs a cable wired to J3-12/13.

## Applications

- **Wi-Fi/BLE sensor node** on header I2C/SPI; single RISC-V core and 4 MB flash suit small IoT firmware.
- **BLE 5 beacon or GATT peripheral**, RGB LED as status.
- **Serial bridge / test fixture** using the CP2102N for logs while GPIO0–10 drive the device under test.
- Unsuitable for camera or display-buffer work (no PSRAM) or for USB-device projects without extra wiring (native USB is not on a connector).

## Files

- `hardware/schematic-v1.1.pdf`, `hardware/pcb-layout-v1.1.pdf`, `hardware/dimensions-v1.1.pdf`
- `datasheets/esp32-c3-wroom-02_datasheet_en.pdf`: module datasheet
- `reference/platformio-board.json`: `esp32-c3-devkitc-02` board definition
- `reference/arduino-esp32-pins_arduino.h`: generic `esp32c3` Arduino variant header
- `wiki/user-guide.md`: Espressif user guide with block diagram and pin-layout images
