# Nordic nRF54LM20A

Wireless SoC: Cortex-M33 @ 128 MHz with a 128 MHz RISC-V coprocessor, 512 KB RAM, 2036 KB non-volatile memory (RRAM), multiprotocol 2.4 GHz radio (Bluetooth LE with Channel Sounding, 802.15.4-2020 for Thread/Matter/Zigbee, proprietary 2.4 GHz up to 4 Mbps), high-speed USB and NFC.

Boards: [seeed-xiao-nrf54lm20a-sense](../../boards/seeed-xiao-nrf54lm20a-sense/README.md).

- `nrf54lm20a-nrf54lm20b-datasheet-v1.0.pdf`: Nordic's datasheet v1.0, covering both variants.

## Specs from the datasheet

| | |
|---|---|
| CPU | 128 MHz Cortex-M33 with FPU, DSP, MPU and TrustZone; SWD, ETM, ITM, DWT, CTI and TPIU debug |
| Coprocessor | 128 MHz RISC-V (VPR). sQSPI is available to it as a SoftPeripheral |
| Memory | **2036 KB NVM (RRAM)** and 512 KB RAM |
| Radio | Bluetooth LE (LE 1M/2M/Coded, Channel Sounding), IEEE 802.15.4-2020 at 250 kbps, 2.4 GHz proprietary GFSK at 1/2/4 Mbps. On-chip balun, single-ended antenna. TX power in 1 dBm steps from −10 dBm |
| Serial | Seven EasyDMA serial instances: one HS-SPI to 32 MHz plus six SPI to 8 MHz; six TWI to 400 kHz; one HS-UART to 4 Mbps plus six UART to 1 Mbps |
| ADC | SAADC, eight programmable-gain channels, 14-bit at 62.5 ksps or 12-bit at 125 ksps oversampled |
| Other | High-speed USB, TDM, PDM, NFC, PWM, QDEC, Global RTC that keeps running in System OFF |
| Security | TrustZone isolation, tamper detection, cryptographic engine with side-channel leakage protection |
| GPIO | up to 66 |
| Packages | CSP and QFN |

Current at 3.0 V: BLE TX 1 Mbps 5.0 mA at 0 dBm, 7.1 mA at +4 dBm, 10.9 mA at +8 dBm; BLE RX 3.3 mA; CoreMark from RRAM with cache 2.6 mA; System ON idle with GRTC and 512 KB RAM retained **4.3 µA**; System OFF with GRTC wakeup 1.0 µA; System OFF 0.7 µA.

**Variants:** the nRF54LM20A and nRF54LM20B are identical except that the B adds the **Axon NPU**, an edge-AI accelerator (3.0 mA running a DS-CNN keyword-spotting model). The XIAO board carries the A, so there is no NPU on it.

Peripheral naming as used by Zephyr on this part: `i2c30`, `spi00`, `pdm20`, `gpio0`–`gpio3`, GRTC for the low-power real-time counter, `RESET_LOW_POWER_WAKE` as the System OFF wake reason.

## Files

- `nrf54lm20a-nrf54lm20b-datasheet-v1.0.pdf`: Nordic's datasheet, v1.0
- `reference/nrf54lm20a.svd.gz`: CMSIS-SVD register description shipped by Seeed's PlatformIO platform. Gunzip it to feed a debugger or to look up register layouts.
