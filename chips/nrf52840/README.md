# Nordic nRF52840

Arm Cortex-M4F @ 64 MHz, 1 MB flash, 256 KB RAM. BLE 5 / 802.15.4 / NFC-A, native USB 2.0 FS, QSPI, 48 GPIO (aQFN73).

- `nrf52840-product-spec-v1.5.pdf`: Product Specification v1.5, Seeed's copy. Nordic's current PS (docs.nordicsemi.com) refuses scripted downloads, so get the latest from a browser.

## Pins to know

- P0.09/P0.10 are NFC1/NFC2. They work as GPIO only after NFC pins are disabled in UICR (`CONFIG_NFCT_PINS_AS_GPIOS` / `-DCONFIG_NFCT_PINS_AS_GPIOS`).
- P0.18 can be nRESET. Many pins are "standard drive, low frequency I/O only" (see the pin table), which matters near the radio.
- The SAADC input limit is VDD. Don't let an analog pin exceed 3.6 V.

Boards: [seeed-xiao-nrf52840-sense](../../boards/seeed-xiao-nrf52840-sense/README.md)
