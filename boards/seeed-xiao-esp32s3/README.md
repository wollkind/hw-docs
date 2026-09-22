# Seeed Studio XIAO ESP32-S3 / S3 Sense / S3 Plus

A 21 × 17.8 mm ESP32-S3R8 module board. There are three variants; **Plus** is the one inside the [XIAO 1.14" display](../seeed-xiao-1.14in-display-esp32s3/README.md). Chip docs: [../../chips/esp32-s3](../../chips/esp32-s3/README.md).
Used by: none in `PlatformIO/Projects` yet.

## Variants

| | XIAO ESP32-S3 | S3 Sense | S3 Plus |
|---|---|---|---|
| Chip | ESP32-S3R8 (8 MB octal PSRAM) | same | same |
| Flash | 8 MB | 8 MB | **16 MB** |
| Extras | none | OV3660 camera, PDM mic, SD slot (expansion board) | 18 GPIO (bottom pads D11–D19), 2nd UART and SPI, B2B connector |
| Deep sleep @3.8 V | 14 µA | 3 mA (with expansion board) | 33.5 µA |
| Charge current | 50 mA fast / 3.8 mA trickle (S3 and Sense) | | 100 mA / 0.9 mA |

- Power input: USB-C 5 V, or a 3.7 V LiPo on the BAT pads.
- The 3V3 pin supplies up to 700 mA.
- The 5V pin carries no voltage when running on battery.

## Pinout: Plus (`variants/XIAO_ESP32S3_Plus/pins_arduino.h`)

| D | GPIO | Default role | | D | GPIO | Default role |
|---|---|---|---|---|---|---|
| D0 | 1 | A0 | | D10 | 9 | MOSI |
| D1 | 2 | A1 | | D11 | 38 | I2S_SD |
| D2 | 3 | A2 (JTAG strap) | | D12 | 39 | I2S_SCK / MTCK |
| D3 | 4 | A3 | | D13 | 40 | I2S_WS / MTDO |
| D4 | 5 | SDA | | D14 | 41 | RX1 / MTDI |
| D5 | 6 | SCL | | D15 | 42 | TX1 / MTMS |
| D6 | 43 | TX (UART0) | | D16 | 10 | ADC_BAT (battery divider) |
| D7 | 44 | RX (UART0) | | D17 | 13 | SCK1 |
| D8 | 7 | SCK | | D18 | 12 | MISO1 |
| D9 | 8 | MISO | | D19 | 11 | MOSI1 |

The user LED is on GPIO21 and BOOT is GPIO0. The pin headers for the plain S3 and Sense are in `reference/pins_arduino-XIAO_ESP32S3.h`. D0–D10 are the same on all three variants; D11/D12 there are GPIO42/41 (the PDM mic on Sense).

### Sense camera and microphone

From the net labels in Seeed's own KiCad source for the Sense v1.5 (`hardware/sense-v1.5-sch-pcb.zip`, sheet `03 XIAO ESP32-S3-Sense.kicad_sch`):

| Signal | GPIO |
|---|---|
| Camera XMCLK | 10 |
| DVP_Y2 / Y3 / Y4 / Y5 / Y6 / Y7 / Y8 / Y9 | 15 / 17 / 18 / 16 / 14 / 12 / 11 / 48 |
| DVP_PCLK | 13 |
| DVP_VSYNC | 38 |
| DVP_HREF | 47 |
| Camera SCCB SCL / SDA | 39 / 40 |
| PDM microphone DATA / CLK | 41 / 42 |
| User LED | 21 |

The camera control bus (GPIO39/40) and the PDM pins (41/42) are the chip's JTAG pins MTCK, MTDO, MTDI and MTMS, which is why hardware JTAG debugging and the Sense peripherals cannot both be used.

## PlatformIO

`board = seeed_xiao_esp32_s3_plus` is in the pioarduino platform (55.03.x) but not in stock `espressif32`. Its board JSON sets `memory_type = qio_opi`, `BOARD_HAS_PSRAM`, `USB_CDC_ON_BOOT=1` and upload `flash_size = 16MB`. From the board JSON; untested.

```ini
platform = https://github.com/pioarduino/platform-espressif32/releases/download/55.03.311/platform-espressif32.zip
board = seeed_xiao_esp32_s3_plus
framework = arduino
board_build.partitions = default_16MB.csv   ; the JSON defaults to default_8MB.csv, wasting half the flash
```

For the plain S3 or Sense, use `board = seeed_xiao_esp32s3`.

## Operational notes

- **Upload fails / no port:** hold BOOT while plugging in USB, then release it.
- **A11/A12 (GPIO41/42)** have no ADC, despite the labels.
- **Battery voltage:** the Plus reads it through the divider on D16 (GPIO10). The plain S3 has no battery ADC.
- **Strapping pins:** GPIO0 and GPIO46 set boot mode, GPIO45 sets VDD_SPI, GPIO3 sets the JTAG source (that's D2).
- **Flash/PSRAM pins:** GPIO33–37 are used by the octal PSRAM and are not broken out.
- **Plus B2B connector:** fits the Wio-SX1262 board, but **not** the Sense camera board.
- **5V pin as input:** needs a diode between your source and the pin.

## Applications

- **Camera node (Sense variant only).** OV3660 plus PDM mic plus SD slot on the expansion board. Deep sleep rises to 3 mA with the expansion board attached, so this variant is unsuitable for long battery operation.
- **Compact Wi-Fi/BLE controller (base variant).** 14 µA deep sleep, 700 mA available on the 3V3 pin for peripherals.
- **Dense I/O work (Plus variant).** 18 additional GPIO on the bottom pads, a second UART and SPI, 16 MB flash.
- **Constraint for all variants:** the 5V pin carries no voltage when running from battery.

## Files

- `wiki/getting-started.md` (+ `img/`)
- `hardware/plus-schematic-v1.1.pdf`, `plus-kicad-v1.1.zip`, `plus-top.dxf`, `plus-bottom.dxf`
- `hardware/xiao-esp32s3-schematic-v1.4.pdf`, `dimensions-v1.1.dxf`
- `hardware/plus-pinout.xlsx`: despite the name, this sheet lists the base/Sense mapping (camera and PDM columns), not the Plus D11–D19. Use the variant header above for the Plus.
- `hardware/sense-pinout.xlsx`
- `hardware/sense-v1.5-sch-pcb.zip`: Seeed's KiCad source for the **Sense v1.5** — schematic sheets, PCB and a block diagram. This is the Sense schematic; the PDF Seeed links for it serves the plain-S3 file instead (see `sources.md`).
- `reference/pins_arduino-*.h`: arduino-esp32 variant files
