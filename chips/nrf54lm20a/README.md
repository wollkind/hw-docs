# Nordic nRF54LM20A

Wireless SoC: Cortex-M33 @ 128 MHz with a 128 MHz RISC-V coprocessor, 512 KB RAM, 2 MB non-volatile memory, multiprotocol 2.4 GHz radio (BLE 6.0 including Channel Sounding, BLE Mesh, Thread, Zigbee, Matter, Amazon Sidewalk, proprietary 2.4 GHz up to 4 Mbps) and NFC.

Boards: [../../boards/seeed-xiao-nrf54lm20a-sense](../../boards/seeed-xiao-nrf54lm20a-sense/README.md).

All of the above comes from Seeed's wiki for the XIAO nRF54LM20A Sense, not from Nordic. **No Nordic datasheet or product specification is in this entry** — see `sources.md`.

Peripheral naming as used by Zephyr on this part: `i2c30`, `spi00`, `pdm20`, `gpio0`–`gpio3`, GRTC for the low-power real-time counter, `RESET_LOW_POWER_WAKE` as the System OFF wake reason.

## Files

- `reference/nrf54lm20a.svd.gz`: CMSIS-SVD register description shipped by Seeed's PlatformIO platform. Gunzip it to feed a debugger or to look up register layouts while the datasheet is missing.
