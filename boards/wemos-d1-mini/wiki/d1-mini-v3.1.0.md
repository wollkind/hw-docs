<!-- source: https://www.wemos.cc/en/latest/d1/d1_mini_3.1.0.html | fetched: 2026-09-23 -->
# LOLIN D1 mini v3.1.0 — WEMOS  documentation

# LOLIN D1 mini v3.1.0

|  |  |
| --- | --- |
| [TOP_IMG](https://www.wemos.cc/en/latest/_static/boards/d1_mini_v3.1.0_1_16x16.jpg) | [BOTTOM_IMG](https://www.wemos.cc/en/latest/_static/boards/d1_mini_v3.1.0_2_16x16.jpg) |

A mini wifi board with 4MB flash based on ESP-8266EX.
[[Buy it]](https://www.aliexpress.com/store/product/D1-mini-Mini-NodeMcu-4M-bytes-Lua-WIFI-Internet-of-Things-development-board-based-ESP8266/1331105_32529101036.html)

## Features

> - 11 digital IO, interrupt/pwm/I2C/one-wire supported(except D0)
> - 1 analog input(3.2V max input)
> - a Micro USB connection
> - Compatible with MicroPython, Arduino, nodemcu

## Tutorials

> - [Get started with MicroPython [D1/D1 mini series]](https://www.wemos.cc/en/latest/tutorials/d1/get_started_with_micropython_d1.html)
> - [Get started with Arduino [D1/D1 mini series]](https://www.wemos.cc/en/latest/tutorials/d1/get_started_with_arduino_d1.html)

## Documentation

> - [Schematic V3.1.0[PDF]](https://www.wemos.cc/en/latest/_static/files/sch_d1_mini_v3.0.0.pdf)
> - [CH340 Driver](https://www.wemos.cc/en/latest/ch340_driver.html)

## Technical specs

|  |  |
| --- | --- |
| Operating Voltage | 3.3V |
| Digital I/O Pins | 11 |
| Analog Input Pins | 1(3.2V Max) |
| Clock Speed | 80/160MHz |
| Flash | 4M Bytes |
| Size | 34.2\*25.6mm |
| Weight | 3g |

## Pin

| Pin | Function | ESP-8266 Pin |
| --- | --- | --- |
| TX | TXD | TXD |
| RX | RXD | RXD |
| A0 | Analog input, max 3.2V | A0 |
| D0 | IO | GPIO16 |
| D1 | IO, SCL | GPIO5 |
| D2 | IO, SDA | GPIO4 |
| D3 | IO, 10k Pull-up | GPIO0 |
| D4 | IO, 10k Pull-up, BUILTIN\_LED | GPIO2 |
| D5 | IO, SCK | GPIO14 |
| D6 | IO, MISO | GPIO12 |
| D7 | IO, MOSI | GPIO13 |
| D8 | IO, 10k Pull-down, SS | GPIO15 |
| G | Ground | GND |
| 5V | 5V | - |
| 3V3 | 3.3V | 3.3V |
| RST | Reset | RST |

Note

All of the IO pins run at 3.3V.

## Version

> - V3.1.0(current)
> - V3.0.0
> - V2.3.0
> - V2.2.0
