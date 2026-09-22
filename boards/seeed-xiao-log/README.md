# Seeed XIAO Logger HAT / XIAO-LOG (SKU 6341, open-source design by potblitd)

XIAO-sized HAT with temperature/humidity, ambient light, a real-time clock and battery-voltage monitoring — built for battery-powered loggers that spend most of their life in deep sleep. Hardware V3 (2024-09).
Used by: no project found.

## Key specs (project readme and V3 schematic)

| | |
|---|---|
| Size | 21 × 17.75 mm, castellated headers, same footprint as a XIAO |
| Supply | 2.4–3.6 V |
| Current | ~500 µA active, **~0.25 µA idle** (RTC only) |
| Temp/humidity | Sensirion **SHT40**, I2C 0x44, ~2 ms read |
| Ambient light | **BH1750FVI**, I2C 0x23, ~120 ms read |
| RTC | **PCF8563**, I2C 0x51, 32.768 kHz crystal, programmable interrupt |
| Battery sense | 100 kΩ / 100 kΩ divider behind a MOSFET, read on A3 |
| Operating temp | −40 °C to 85 °C |

## Pinout (XIAO pads)

| Function | Pad |
|---|---|
| I2C SDA / SCL (all three chips) | D4 / D5 |
| Sensor + divider power gate | **D10** — drive HIGH to power the sensors and the divider, LOW to sleep |
| RTC interrupt (wake from deep sleep) | D0 |
| Battery voltage (ADC) | A3 |

On a XIAO ESP32-C3 those map to GPIO 6/7 (I2C), GPIO 10 (power gate) and GPIO 5 (ADC), which is what the MicroPython example uses.

> The project readme's spec table lists the ADC as "D3/D3" while its prose says A3. A3 and D3 are the same pad on the XIAO footprint, so both refer to one pin.

## Compatibility (from the project readme)

- **All features:** XIAO ESP32-C3, nRF54820, RP2350, MG24, ESP32-C6
- **No battery monitoring:** XIAO SAMD21, XIAO RP2040

## Software

`reference/xiaohat.py` is the MicroPython driver for the whole board: power the rail with `Pin(10).on()`, read the PCF8563 BCD registers from 0x51 (with per-field masks), the SHT40 with command `0xFD` (hi-res), the BH1750 with `0x01`/`0x07`/`0x20`, then drop the rail and `machine.deepsleep()`. `reference/set_rtc.py` seeds the clock; `reference/esphome-xiaohat.yaml` is a Home Assistant/ESPHome configuration.

## Operational notes

- **Nothing reads until D10 is high.** Sensors and the divider are gated, so an I2C scan straight after boot finds only the RTC at 0x51.
- **Only the RTC is always on** (~250 nA per the project readme). That is what makes the 0.25 µA idle figure possible, and it is also why the RTC keeps time across deep sleep while the sensors do not.
- **Retrieving the log over USB requires a manual sequence.** the author notes that on an ESP32-C3 in deep sleep the only way in is to reset the board and hit "restart backend" inside the 10-second window before it sleeps again.
- **SAMD21 and RP2040 lose battery monitoring** — their ADC pad does not line up with the divider.
- **Three hardware revisions exist** (V1 and V2 are named `XIAO-log^2`, V3 is `XIAO-HAT-3`); the pin map above is read from the V3 schematic, which is what Seeed sells.

## Applications

- **Long-duration environmental logger.** PCF8563 wakes the host on D0, D10 powers the sensors, sample, then return to deep sleep. Idle current is approximately 0.25 µA with only the RTC running.
- **Light and humidity survey.** SHT40 and BH1750 on the same bus, logged with timestamps, powered from a single cell.
- **Battery-life measurement.** The 100 kΩ/100 kΩ divider on A3 records supply voltage over the run.
- **Constraint:** XIAO SAMD21 and RP2040 hosts lose battery monitoring; their ADC pad does not align with the divider.

## Files

- `hardware/schematic-v3.pdf`, `layout-v3.pdf`, `altium-v3.zip`: the current revision
- `hardware/schematic-v2.pdf`, `schematic-v1.pdf`: earlier revisions, for boards bought before the Seeed run
- `reference/xiaohat.py`, `set_rtc.py`, `esphome-xiaohat.yaml`
- `wiki/xiao-log-repo-readme.md`: the project readme (specs, compatibility, programming notes)
