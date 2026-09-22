# Seeed Studio Expansion Base for XIAO (SKU 103030356)

Carrier board for any XIAO: 0.96" OLED, PCF8563 RTC with coin-cell backup, microSD slot, buzzer, user button, Grove connectors, LiPo charging and a 5 V servo header.
Used by: no project found.

## Key specs (Seeed wiki)

| | |
|---|---|
| Power | 5 V USB-C or 3.7 V LiPo (JST 2.0 mm) |
| Charging | 460 mA max, onboard battery management |
| Display | 0.96" SSD1306 OLED, 128×64, on the XIAO I2C pins |
| RTC | PCF8563, ±1.5 s/day at 25 °C, CR1220 backup cell |
| Storage | microSD slot (on the back) |
| Grove | 2× I2C, 1× UART, 1× A0/D0 |
| Other | passive buzzer, user button, RESET button, SWD header, 5 V servo header |
| Size | about half a Raspberry Pi 4 |

## Pinout (XIAO pin names)

| Function | XIAO pin |
|---|---|
| OLED + RTC (shared I2C) | SDA / SCL |
| microSD chip select | **D2** |
| Passive buzzer | **A3** (the same pad as D3 — the wiki's text says A3, its example code says `D3`) |
| User button | **D1**, with `INPUT_PULLUP` |

The OLED is addressed through U8g2's `U8X8_SSD1306_128X64_NONAME_HW_I2C`. **The schematic confirms the address**: it prints "The I2C slave address is 0x78" against the `IIC_ADDR` strap (and 0x7a if the strap is moved), which is **0x3C** as a 7-bit address, 0x3D on the alternative. The RTC uses the `PCF8563` Arduino library; the schematic prints its addresses as write 0xA2 / read 0xA3, i.e. **0x51** 7-bit.

## Operational notes

- **Not compatible with every XIAO.** Seeed states the SWD pins differ on the **XIAO nRF54L15 and XIAO MG24**, so this board does not support them. SAMD21, RP2040 and nRF52840 are called out as compatible.
- **Seat the XIAO between the two female headers**, and plug the XIAO in before the USB-C cable — Seeed warns that getting this wrong damages both boards.
- **The 5 V pin is fed straight from USB**, not from the PMIC (Seeed's own FAQ), so on battery there is no 5 V for the servo header.
- **Charge LED semantics are inverted from the obvious reading:** steady on = charging, flashing = no battery or not charging.
- **The buzzer is hard-wired to A3/D3.** If that pad is needed for something else, the wiki shows the trace to cut.
- **The wiki's button example tests for `HIGH` as "pressed" while configuring `INPUT_PULLUP`**, which reads backwards; check the polarity on the actual board before copying it `(unverified)`.
- **Battery polarity is not keyed** — Seeed's photo is the only guide.

## Applications

- **Standalone logger.** PCF8563 supplies timestamps, the microSD slot on D2 stores records, the OLED displays current values. RTC accuracy is ±1.5 s/day at 25 °C with a CR1220 cell fitted.
- **Grove sensor prototyping.** Two I2C, one UART and one A0/D0 Grove port, battery charging at 460 mA maximum, no soldering required.
- **Timed alarm device.** RTC interrupt plus the passive buzzer on A3/D3.
- **Constraint:** the 5 V pin is fed from USB only. A servo on the 5 V header does not operate on battery power.

## Files

- `hardware/schematic-v1.0.pdf`: Seeed's v1.0 schematic (fetched 2026-09-22) — the source for the I2C addresses above
- `hardware/eagle-v1.0.sch`, `hardware/eagle-v1.0.brd`: the EAGLE design files
- `datasheets/eta1038.pdf`, `eta3410.pdf`, `eta6003.pdf`: the power-path, regulator and charger ICs
- `datasheets/pcf8563t.pdf`: the RTC
- `wiki/Seeeduino-XIAO-Expansion-Board.md`: the full Seeed wiki page (OLED, button, buzzer, RTC, SD and CircuitPython walkthroughs). Its images are remote links on `files.seeedstudio.com`.
