# Sources (fetched 2026-09-22)

- https://datasheets.raspberrypi.com/pico/pico-datasheet.pdf → `hardware/pico-datasheet.pdf` (18 MB; it carries the board schematic in Appendix B)
- https://datasheets.raspberrypi.com/pico/Pico-R3-A4-Pinout.pdf → `hardware/pinout.pdf`
- https://raw.githubusercontent.com/maxgerhardt/platform-raspberrypi/develop/boards/pico.json → `reference/platformio-pico.json`. `maxgerhardt/platform-raspberrypi` `develop` @ `5d4561a05e3b212660ac6fdd3fbfb328d1988aa1` — the platform `pio-feather` pins by git URL.

Project files: `wollkind/pio-feather` `platformio.ini` (`[env:pico]`).

The RP2040 datasheet is in `chips/rp2040/`.

Not fetched: the Pico W datasheet (20.2 MB, and no project targets a Pico W).
