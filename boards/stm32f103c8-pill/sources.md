# Sources (fetched 2026-09-22)

- https://raw.githubusercontent.com/platformio/platform-ststm32/develop/boards/blackpill_f103c8.json → `reference/platformio-blackpill_f103c8.json`. `platformio/platform-ststm32` `develop` @ `c7fe5b923c22b9d0bf3304cc1a1fdbe9963f822e`.
- https://raw.githubusercontent.com/stm32duino/Arduino_Core_STM32/main/variants/STM32F1xx/F103C8T_F103CB(T-U)/variant_PILL_F103Cx.h → `reference/variant_PILL_F103Cx.h`. `stm32duino/Arduino_Core_STM32` `main` @ `cf59c7d0658abdcfa786970b84cc1a2baf67348f`. Source for the pin table, the peripheral defaults and the LED-pin conditional.
- `WeActStudio/BluePill-Plus` @ `33dd592dba88d8aec6ec41726f38fefc7e1128e6`: `HDK/BluePillPlus_V11_SchDoc.pdf` → `hardware/weact-bluepill-plus-v11-schematic.pdf`, `HDK/BluePillPlus_V11 Board Shape 外形.pdf` → `hardware/weact-bluepill-plus-v11-board-shape.pdf`. The board's LED (PB2, active high), KEY (PA0), crystals, size and the GD32F303CCT6 alternative come from that repository's `README.md`.

Not copied from the WeAct repository (357 MB checked out): the 3D STEP model, the Altium `IntLib`, the `SDK/`, `Soft/` and `Doc/` trees, and the board photographs.

**Missing: ST's own documents.** `https://www.st.com/resource/en/datasheet/stm32f103c8.pdf` and RM0008 both fail — over HTTP/2 the connection is reset (`stream not closed cleanly, INTERNAL_ERROR`), and over HTTP/1.1 the server sends an empty reply, with a browser user agent either way. This was retried on 2026-09-22 at the Full network access level; the same host also refused the LSM6DS3TR-C datasheet for `boards/seeed-xiao-nrf52840-sense`. A browser download is the only route, and until then there is no `chips/stm32f103` entry.

**Identification:** `pio-feather`'s `[env:stm]` names only `board = blackpill_f103c8`. Nothing in the project identifies the physical board, and the id itself is generic — see the opening of `README.md`.
