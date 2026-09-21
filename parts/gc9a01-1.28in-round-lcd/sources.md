# Sources (fetched 2026-09-21)

- Amazon listing for the HiLetgo module: not fetched (amazon.com is blocked by the sandbox proxy, and it is a reseller page anyway). No vendor wiki exists for this module.
- Datasheet: https://raw.githubusercontent.com/sbcshop/1.28-Round-LCD-Breakout-Software/main/Documents/GC9A01A%20Datasheet.pdf → `datasheets/gc9a01a.pdf` (GC9A01A Rev 1.0 Preliminary, 2019-07-02, doc id LCD-DST-3014). Galaxycore does not publish it directly; this is the copy in SB Components' repo for their own 1.28" round breakout.
- https://github.com/Bodmer/TFT_eSPI @ `16e37595040eac69cd628e4bffb56fc30cad6299`: `TFT_Drivers/GC9A01_{Init,Defines,Rotation}.h`, `User_Setups/Setup200_GC9A01.h`, `User_Setups/Setup46_GC9A01_ESP32.h` → `reference/`
- https://github.com/adafruit/Adafruit_GC9A01A, branch `master` (fetched via raw, no SHA recorded — api.github.com is blocked): `Adafruit_GC9A01A.h`, `Adafruit_GC9A01A.cpp` → `reference/`
- CircuitPython usage pattern from https://github.com/todbot/CircuitPython_GC9A01_demos `README.md` (not copied).
- Module pin labels (`BLK CS DC RES SDA SCL VCC GND`) come from community sources, not from a vendor document — marked unverified in `README.md`. A photo of the owner's actual module would settle the pin order and whether it is the 7- or 8-pin build.
