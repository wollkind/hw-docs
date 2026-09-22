# Sources (fetched 2026-09-22)

- https://docs.arduino.cc/resources/datasheets/A000066-datasheet.pdf → `hardware/uno-rev3-datasheet.pdf`
- https://docs.arduino.cc/resources/schematics/A000066-schematics.pdf → `hardware/uno-rev3-schematic.pdf`
- https://docs.arduino.cc/resources/pinouts/A000066-full-pinout.pdf → `hardware/uno-rev3-pinout.pdf`
- https://raw.githubusercontent.com/platformio/platform-atmelavr/develop/boards/uno.json → `reference/platformio-uno.json`. `platformio/platform-atmelavr` `develop` @ `5da4930a978700ecc9bffcf56c5fbeb930c25611`.

Project files: `wollkind/pio-lcd2` and `wollkind/pio-feather` `platformio.ini` (`[env:uno]`).

The ATmega328P's own datasheet is not in this library — see `chips/atmega328p/sources.md` for why and where it is.
