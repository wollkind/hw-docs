# XY-SK120 ("SK-120") 120 W buck-boost converter, CC/CV

Programmable DC-DC buck-boost module with a colour LCD, rotary encoder and a TTL serial port speaking Modbus RTU. Bought as [amazon.com/dp/B0D9H3Z637](https://www.amazon.com/dp/B0D9H3Z637); the manufacturer's family name is **XY-SK120** (XY-SK60 is the 60 W sibling, XY-SK120X and XY-SK150 are near-identical variants).
Used by: no project.

## Key specs

| | |
|---|---|
| Input | 6–36 V DC `(from the listing, not a vendor document)` |
| Output | 0–36 V DC, CC/CV `(same)` |
| Power | 120 W `(same)` |
| Display | colour LCD with rotary encoder and keypad |
| Serial | TTL UART, Modbus RTU, 8N1 (1 start, 8 data, no parity, 1 stop) |
| Default address / baud | slave address 1, baud code 6 = 115200 |
| Memory groups | M0–M9; M0 loads at power-on, M1/M2 are the front-panel shortcuts |
| Extra functions | MPPT solar charging, constant-power mode, battery-full cutoff current, timed/Ah/Wh cutoffs, key lock, buzzer |

**Variant caution:** the listing was not fetchable, so which exact build is in hand (SK120, SK120X, SK120D) is unconfirmed. The Modbus map below is what the vendor ships for the SK120 family; the `0x0030`–`0x0034` Wi-Fi registers only do something on units carrying the Sinilink ESP8285 Wi-Fi module.

## Modbus interface

- Function codes supported: **0x03** (read), **0x06** (write single), **0x10** (write multiple) — nothing else.
- Frames need ≥3.5 character times of idle before and between messages (≈5 ms at 9600 baud).
- CRC-16 with polynomial 0xA001, seed 0xFFFF, low byte transmitted first.
- Wiring to an MCU: MCU TX → module RX, MCU RX → module TX, common GND.

Baud codes for `0x0019`: 0 = 9600, 1 = 14400, 2 = 19200, 3 = 38400, 4 = 56000, 5 = 57600, 6 = 115200 (default), 7 = 2400, 8 = 4800.

### Live registers

| Addr | Name | Unit | Scale | R/W |
|---|---|---|---|---|
| 0x0000 | V-SET | V | ÷100 | R/W |
| 0x0001 | I-SET | A | ÷1000 | R/W |
| 0x0002 | VOUT | V | ÷100 | R |
| 0x0003 | IOUT | A | ÷1000 | R |
| 0x0004 | POWER | W | ÷100 | R |
| 0x0005 | UIN (input voltage) | V | ÷100 | R |
| 0x0006 / 0x0007 | output Ah, low / high word | mAh | — | R |
| 0x0008 / 0x0009 | output Wh, low / high word | mWh | — | R |
| 0x000A–0x000C | on-time hours / minutes / seconds | — | — | R |
| 0x000D / 0x000E | internal / external temperature | °C or °F | ÷10 | R |
| 0x000F | LOCK (0 unlocked, 1 locked) | — | — | R/W |
| 0x0010 | PROTECT status | — | — | R/W |
| 0x0011 | CVCC (0 = CV, 1 = CC) | — | — | R |
| 0x0012 | ONOFF (0 off, 1 on) | — | — | R/W |
| 0x0013 | temperature unit (°C/°F) | — | — | R/W |
| 0x0014 | backlight level 0–5 | — | — | R/W |
| 0x0015 | screen-off timeout | min | — | R/W |
| 0x0016 / 0x0017 | model / firmware version | — | — | R |
| 0x0018 / 0x0019 | slave address / baud code | — | — | R/W |
| 0x001A / 0x001B | internal / external temperature offset | — | ÷10 | R/W |
| 0x001C | buzzer | — | — | R/W |
| 0x001D | recall data group 0–9 | — | — | R/W |
| 0x001E | device status | — | — | R/W |
| 0x001F / 0x0020 | MPPT enable / MPPT coefficient | — | — | R/W |
| 0x0021 | battery-full cutoff current | A | ÷1000 | R/W |
| 0x0022 / 0x0023 | constant-power enable / setpoint | W | ÷10 | R/W |
| 0x0030–0x0034 | Wi-Fi module: master type, pairing, status, IPv4 high/low | — | — | R/W |
| 0x0100–0x0103 | RTC: year, month/day, hour/minute, second/weekday | — | — | R/W |
| 0x0110–0x011D | weather display (today plus three days) | — | — | R/W |
| 0x1000–0x100E | calibration block, guarded by a safety code at 0x1000 | — | — | R/W |

`PROTECT` (0x0010) values: 0 normal, 1 OVP, 2 OCP, 3 OPP, 4 LVP, 5 OAH, 6 OHP, 7 OTP, 8 OEP, 9 OWH, 10 ICP.

### Memory groups

Each group is 14 registers wide. Group *n* starts at **0x0050 + n × 0x0010** (M0 = 0x0050, M3 = 0x0080): V-SET, I-SET, LVP, OVP, OCP, OPP, max-output hours/minutes, max Ah low/high, max Wh low/high, OTP, power-on output state, external over-temperature.

## Operational notes

- **The vendor's own docs contradict each other on the group base address.** `xy-sk120-modbus-protocol.pdf` note 1 writes the formula as `0x0020 + group × 0x0010` but then works its own example as `0x0050 + 3 × 0x0010 = 0x0080`; `xy-sk120-modbus-address.pdf` lists M0 at 0x0050. 0x0050 is the one that matches the register listing.
- **Only 0x03/0x06/0x10.** Libraries that reach for 0x01/0x02/0x04 get an exception.
- **Scaling differs per register:** voltage ÷100, current ÷1000, power ÷100 — but the constant-power setpoint at 0x0023 is ÷10 and the Wh registers count 10 mWh units in the protection block.
- **Wi-Fi, RTC and weather registers** are for the Sinilink ESP8285 add-on and the on-screen clock. They answer on units without the module, but nothing happens.
- **Undocumented registers** found by probing (in `reference/XY-SKxxx.h`, from the library author, so `(unverified)` against the vendor): 0x0025 factory reset (write 1), 0x005E/0x005F external-temperature protection — 0x005E accepts writes with no visible effect. The FET, CLOF and POFF menu items on the OSD have no register anyone has located.
- **Model register:** 0x0016 reportedly returns 22873 on an XY-SK120 `(unverified)`.

## Applications

- **Programmable bench supply.** 6 to 36 V in, 0 to 36 V out at up to 120 W with CC/CV, set from the front panel or over Modbus.
- **Battery charging profile.** Constant current to a voltage limit, with the battery-full cutoff current at register 0x0021 and protection limits per memory group.
- **Automated test rail.** Function codes 0x03, 0x06 and 0x10 over TTL serial permit a host to set voltage and current and read back output, energy and protection state during a test sequence.
- **Solar input.** MPPT is enabled at register 0x001F with the coefficient at 0x0020.

## Files

- `datasheets/xy-sk120-modbus-protocol.pdf`: the vendor's Modbus RTU protocol document (Chinese) — frame format, function codes, register table, CRC method, worked examples
- `datasheets/xy-sk120-modbus-address.pdf`: the vendor's register address table (Chinese), including the calibration block
- `reference/XY-SKxxx.h`: register defines with per-register notes from the community Arduino library
- `reference/data-group-osd-notes.md`: what the on-screen data-group abbreviations mean
