# Sources (fetched 2026-09-22)

Vendor library (the only authoritative hardware description found):

- `smartpanle/PanelLan_esp32_arduino` @ `2bc0d086c9a55f5288d85da6c16968c22744fe5f` → `reference/sc05x_pin.h`, `reference/sc05x.cpp`, `reference/panellan-readme.md`.
- The same code ships as `smartpanle/PanelLan` 0.0.5 in the PlatformIO registry (`https://dl.registry.platformio.org/download/smartpanle/library/PanelLan/0.0.5/PanelLan-0.0.5.tar.gz`). The registry tarball and the repository HEAD have identical `sc05x_pin.h`, so the pin map is the same in both.
- `src/board/boards.h` in that repo is where `BOARD_SC05_X` is defined as `ZX2D80CE02S-2432`.

Vendor documentation site:

- http://doc.panel-tag.com/ESP32-S3/board.html → `wiki/board-index.md`. Lists five ESP32-S3 boards (ZX3D50CE02S, ZX3D95CE01S-UR, ZX3D95CE01S-AR, ZX2D10GE01R, ZX4D30NE01S-UR) and **not** ZX2D80CE02S. `/_static/espboard/ESP32S3/` returns 403, and the site's search page has no index entry for the model.

Project files:

- `wollkind/pio-strip-com`: `platformio.ini` (the `display` env), `README.md` (hardware table, LVGL configuration) and `src/display/main.cpp` (the `BOARD_SC05_X` header comment and the USB-host detection code).

**Missing source: the vendor datasheet.**

- Web search names this model "WT32S3-28S PRO (ZX2D80CE02S)" and a third-party document host carries a "V1.0 EN Datasheet" under that title, but no vendor-hosted copy was reachable.
- en.wireless-tag.com serves its product catalogue from JavaScript, so the product page for the 28S PRO could not be located by crawling; sibling pages that are reachable (for example `product-item-48.html`, the WT32S3-28S PLUS / `ZX2D80CEC23COF-AIO`) link their datasheets on the `img0*.71360.com` CDN under hashed paths, which cannot be guessed.
- Recovering it needs a browser: find the WT32S3-28S PRO product page on en.wireless-tag.com and take the datasheet link from it.
