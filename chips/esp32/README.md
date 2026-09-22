# ESP32 (original series)

Espressif's first-generation Xtensa LX6 SoC: single or dual core at up to 240 MHz, 520 KB SRAM, 2.4 GHz Wi-Fi 4 and Bluetooth Classic + BLE. The chip behind `board = esp32dev` and behind the **ESP32-PICO-D4** SiP on the [LilyGO T3 LoRa32](../../boards/lilygo-t3-lora32-v1.6.1/README.md).

- `esp32_datasheet_en.pdf`: datasheet v5.3.
- `esp32_technical_reference_manual_en.pdf`: registers and peripherals.
- `esp32-pico-d4_datasheet_en.pdf`: the system-in-package part — ESP32 die, crystal, filters and **4 MB flash in one 7 × 7 mm package**.
- `errata.md`: Espressif's chip errata list, 32 entries.

## Specs from the datasheet

| | |
|---|---|
| CPU | Xtensa LX6, single or dual core, up to 240 MHz. 1079.96 CoreMark on two cores |
| Memory | 520 KB SRAM, 448 KB ROM, 16 KB RTC SRAM |
| Flash/PSRAM | External QSPI; some parts carry it in package (ESP32-U4WDH flash, ESP32-D0WDRH2-V3 PSRAM) |
| GPIO | **34 programmable**, of which 5 strapping, **6 input-only**, and 6 taken by in-package memory on those parts |
| Analogue | 12-bit SAR ADC on up to 18 channels, **two 8-bit DACs**, 10 touch sensors |
| Interfaces | 4 × SPI, 2 × I2S, 2 × I2C, 3 × UART, SD/eMMC/SDIO host, SDIO/SPI slave, **Ethernet MAC** with IEEE 1588, TWAI (CAN 2.0), RMT, pulse counter |
| Clocks | Internal 8 MHz and RC oscillators; external 2–60 MHz crystal (**40 MHz required for Wi-Fi/Bluetooth**); 32 kHz RTC crystal |

The ESP32 is the only Espressif part in this library with DACs and an Ethernet MAC.

## Pins to know

- **GPIO34, 35, 36, 37, 38 and 39 are input-only** — they have no output drivers and no internal pull-ups or pull-downs. Datasheet names: VDET_1, VDET_2, SENSOR_VP, SENSOR_CAPP, SENSOR_CAPN, SENSOR_VN.
- **Strapping pins and their defaults:** GPIO0 pull-up (1), GPIO2 pull-down (0), MTDI (GPIO12) pull-down (0), MTDO (GPIO15) pull-up (1), GPIO5 pull-up (1).
  - **Boot mode is GPIO0 + GPIO2:** GPIO0 = 1 gives SPI boot whatever GPIO2 does; both low gives joint download boot (UART or SDIO).
  - **MTDI (GPIO12) sets the flash voltage.** A board that pulls it high at reset selects 1.8 V VDD_SDIO; getting this wrong on a 3.3 V flash part stops the chip booting.
- **GPIO6–11 go to SPI flash** on a standard module.

## Errata worth knowing

Full list in `errata.md`. The ones most likely to be met:

- **[RES-3.4] The brown-out reset does not work.**
- **[RES-3.1] / [RES-3.8]** spurious watchdog resets at power-up or on deep-sleep wake, the second one caused by flash start-up time.
- **[GPIO-3.6]** on pads that have both GPIO and RTC_GPIO functions, the GPIO pull-up/pull-down register fields do nothing — configure the RTC_GPIO side.
- **[GPIO-3.14]** within a GPIO group, edge interrupts cannot be mixed with other interrupt types.
- **[GPIO-3.11]** GPIO36 and GPIO39 are pulled down for about 80 ns when certain RTC peripherals power on — visible as spurious ADC samples or edges.
- **[CPU-3.5]** the CPU can crash when the clock frequency switches.
- **[ULP-3.19]** the ULP coprocessor and touch sensors are unusable in deep sleep if RTC_PERIPH stays powered.
- **[CLK-3.22]** the ESP32 cannot be the PHY clock source when Wi-Fi and Ethernet run together.

Boards: [espressif-esp32-devkitc](../../boards/espressif-esp32-devkitc/README.md), [lilygo-t3-lora32-v1.6.1](../../boards/lilygo-t3-lora32-v1.6.1/README.md) (ESP32-PICO-D4)
