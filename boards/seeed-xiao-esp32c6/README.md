# Seeed Studio XIAO ESP32-C6

XIAO-format ESP32-C6 board: Wi-Fi 6, BLE 5, Zigbee/Thread/802.15.4, a ceramic antenna plus a U.FL connector with a GPIO-controlled RF switch, and battery charging.
Used by: `pio-solar`, `pio-soil1`, `pio-strip-com` (the `strip` env), `pio-xiao-hdc-wifi` — four of the owner's projects confirmed; `MISSION.md` counts nine `board = seeed_xiao_esp32c6` environments in total.

## Key specs (Seeed wiki)

| | |
|---|---|
| SoC | ESP32-C6: 32-bit RISC-V high-performance core to 160 MHz **plus** a low-power core to 20 MHz |
| Memory | 512 KB SRAM, 4 MB flash, no PSRAM |
| Wireless | Wi-Fi 6 (802.11ax) 2.4 GHz, BLE 5.0, IEEE 802.15.4 (Zigbee, Thread) |
| Antenna | onboard ceramic, plus U.FL; switchable in software |
| Interfaces | 1× UART + 1× LP_UART, 1× I2C + 1× LP_I2C, 1× SPI, 11× GPIO/PWM, 7× ADC, 1× SDIO |
| Buttons | reset, boot |
| Power | USB-C 5 V or 3.7 V LiPo; **no 5 V on the 5V pin when running from battery** |
| Sleep | modem-sleep 30 mA, light-sleep 3.1 mA, deep sleep 15 µA (at 3.8 V) |
| Size / temp | 21 × 17.8 mm, −40 °C to 85 °C |

## Pinout

| Pad | Function | GPIO | Low-power alias |
|---|---|---|---|
| D0 | ADC | GPIO0 | LP_GPIO0 |
| D1 | ADC | GPIO1 | LP_GPIO1 |
| D2 | ADC | GPIO2 | LP_GPIO2 |
| D3 | digital | GPIO21 | SDIO_DATA1 |
| D4 | SDA | GPIO22 | SDIO_DATA2 |
| D5 | SCL | GPIO23 | SDIO_DATA3 |
| D6 | TX | GPIO16 | |
| D7 | RX | GPIO17 | |
| D8 | SCK | GPIO19 | SPI_CLK |
| D9 | MISO | GPIO20 | SPI_MISO |
| D10 | MOSI | GPIO18 | SPI_MOSI |

Not on the pads: JTAG MTDO/MTDI/MTCK/MTMS on GPIO7/5/6/4, boot on GPIO9, **user LED on GPIO15**, RF switch select on GPIO14 and RF switch power on GPIO3.

## PlatformIO

Seeed's wiki uses their own platform:

```ini
platform = https://github.com/Seeed-Studio/platform-seeedboards.git
board = seeed-xiao-esp32-c6
framework = arduino
```

The owner's projects instead use the **pioarduino** fork with the mainline board id, which is what actually gets built here:

```ini
platform = https://github.com/pioarduino/platform-espressif32/releases/download/stable/platform-espressif32.zip
board = seeed_xiao_esp32c6
framework = arduino
```

`pio-soil1` pins the same fork's `#develop` branch instead of the stable zip. Note the two board ids differ (`seeed-xiao-esp32-c6` vs `seeed_xiao_esp32c6`) and belong to different platform packages.

## Gotchas

- **The stock `platformio/espressif32` platform has no ESP32-C6 Arduino support** — hence the pioarduino fork in every one of the owner's C6 projects. Copying a `platform = espressif32` line from an older project will not build.
- **Antenna switching needs two pins, in order.** GPIO3 (RF switch power) must be driven **low** to enable the switch at all; then GPIO14 low = ceramic antenna (default), high = external U.FL. Setting GPIO14 alone does nothing.
- **User LED is GPIO15 and is active low.** From `pio-strip-com`: driving it high parks it off; at 20 packets/second a per-packet blink reads as a steady glow, so that project drives the pin rather than leaving it floating, which would let it sit half-lit off leakage.
- **The charge LED is not a GPIO** — it is wired to the charger IC, so no firmware change can control it (same project).
- **Battery voltage needs a soldered divider.** There is no onboard divider: Seeed's method is a 200 kΩ resistor giving 1:2 into A0, then `analogReadMilliVolts(A0)` × 2.
- **Battery pads are unmarked for polarity:** negative is the pad on the left near the "D8" silkscreen, positive on the right near "D5".
- **No 5 V output on battery power.**
- **D3–D5 double as SDIO data lines**, so an SD card on SDIO collides with the I2C pads.

## Files

- `wiki/`: Seeed's ESP32-C6 pages — getting started, pin multiplexing, Wi-Fi, Bluetooth, PlatformIO, MicroPython, CircuitPython, NuttX, Embedded Swift, Zigbee and the application notes. Images are remote links on the blocked `files.seeedstudio.com`.
