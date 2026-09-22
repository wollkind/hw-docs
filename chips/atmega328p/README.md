# Microchip (Atmel) ATmega328P

8-bit AVR, up to 16 MHz, 32 KB flash, 2 KB SRAM, 1 KB EEPROM. The processor on the Arduino Uno and on Adafruit's Metro.

**There is no datasheet in this entry.** Microchip's combined ATmega48A/PA/88A/PA/168A/PA/328/P datasheet is a 33 MB PDF, past the size this library keeps; the URL is in `sources.md`.

## Specs, from the Arduino Uno R3 datasheet's feature list

| | |
|---|---|
| Core | 8-bit AVR, up to 16 MHz |
| Memory | 32 KB flash, 2 KB SRAM, 1 KB EEPROM |
| Timers | two 8-bit and one 16-bit timer/counter, each with a period register and compare channels; the 16-bit one also has input capture |
| Serial | one USART with a fractional baud-rate generator and start-of-frame detection, one SPI (controller or peripheral), one dual-mode I2C |
| Analogue | analogue comparator with a scalable reference |
| Other | six PWM channels, watchdog with its own oscillator, pin-change interrupt and wake-up, power-on reset, brown-out detection |

**No USB.** A board built on this part needs a separate USB-to-serial chip — the ATmega16U2 on the Uno.

Boards: [arduino-uno-r3](../../boards/arduino-uno-r3/README.md)
