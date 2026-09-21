# Sources (fetched 2026-09-21)

- Product pages https://www.adafruit.com/product/3076 (868/915 MHz), /3077 (433 MHz), /3078, /3079 and the Learn guide: **not fetched** — adafruit.com and cdn-learn.adafruit.com are blocked by the sandbox proxy.
- https://github.com/adafruit/Adafruit-Feather-32u4-RFM-LoRa-PCB @ `ace22faec73dda4b8dcfec16e1667551456689dd`:
  - `Adafruit Feather 32u4 RFMxx.{sch,brd}` → `hardware/eagle.{sch,brd}`
  - `Adafruit Feather 32u4 RFM69 Pinout.pdf`, `Adafruit Feather 32u4 RFM9x Pinout.pdf` → `hardware/`
  - The radio pin table (NSS→D8/PB4, DIO0→D7/PE6, RESET→D4/PD4) and the power-path parts (AP2112-3.3, MCP73831, MBR120) were read out of the schematic XML nets; the product-variant list comes from the repo README.
- Owner's projects (shallow clones): `wollkind/pio-radio`, `wollkind/pio-radio1`, `wollkind/pio-radio2` — they establish the 915 MHz RFM69 fit, the pin defines and the `board = leonardo` discrepancy in `pio-radio2`.
- Missing: the ATmega32U4 datasheet (microchip.com not reachable from this sandbox) and the RFM69HCW / SX1231 datasheet (semtech.com and hoperf.com blocked). No `chips/atmega32u4` entry as a result.
