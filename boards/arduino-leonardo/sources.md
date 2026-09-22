# Sources (fetched 2026-09-22)

- https://docs.arduino.cc/hardware/leonardo/ → `wiki/product-page.md`. The page inlines its icons as base64 data URIs; those were replaced with `(data-uri-removed)` so the file stays readable. Nothing else was changed.
- https://docs.arduino.cc/resources/schematics/A000057-schematics.pdf → `hardware/leonardo-schematic.pdf`
- https://docs.arduino.cc/resources/pinouts/A000057-full-pinout.pdf → `hardware/leonardo-pinout.pdf`
- https://raw.githubusercontent.com/platformio/platform-atmelavr/develop/boards/leonardo.json → `reference/platformio-leonardo.json`. `platformio/platform-atmelavr` `develop` @ `5da4930a978700ecc9bffcf56c5fbeb930c25611`.
- https://raw.githubusercontent.com/arduino/ArduinoCore-avr/master/variants/leonardo/pins_arduino.h → `reference/pins_arduino.h`. `arduino/ArduinoCore-avr` `master` @ `11b9130371e8447920edb65a75706a6c951e51fc`. This is the source for the A6–A11 to digital-pin mapping in `README.md`; the file's own comment is "A6-A11 share with digital pins".

**No board datasheet:** `https://docs.arduino.cc/resources/datasheets/A000057-datasheet.pdf` returns 404 (Arduino publishes datasheets for its newer boards only). The specs here come from the product page and the board file; the CAD archive at `https://docs.arduino.cc/static/fd50e8f3be44a3217bbfd5d123295bdf/A000057-cad-files.zip` was not fetched.

Project files: `wollkind/pio-lcd` (`[env:uno]`, `board = leonardo`) and `wollkind/pio-radio2` (`[env:feather32u4]`, `board = leonardo`).
