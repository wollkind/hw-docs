# Nordic nRF52840

Arm Cortex-M4F @ 64 MHz, 1 MB flash, 256 KB RAM. BLE / 802.15.4 / NFC-A, native USB 2.0 full speed, QSPI. Comes in aQFN73, QFN48 and WLCSP packages.

- `nrf52840-product-spec-v1.5.pdf`: Product Specification v1.5, Seeed's copy. Nordic's current PS (docs.nordicsemi.com) refuses scripted downloads, so get the latest from a browser.

## Pins to know

- P0.09/P0.10 are NFC1/NFC2. They work as GPIO only after UICR register NFCPINS (0x20C) is set to GPIO. In Arduino cores this is `-DCONFIG_NFCT_PINS_AS_GPIOS` (unverified).
- P0.18 can be nRESET. Many pins are "standard drive, low frequency I/O only" (see the pin table), which matters near the radio.
- Keep analog inputs at or below 3.6 V (Seeed XIAO wiki, on P0.31).

Boards: [seeed-xiao-nrf52840-sense](../../boards/seeed-xiao-nrf52840-sense/README.md)
