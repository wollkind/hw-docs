<!-- source: https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c5/03-errata-description/index.html | fetched: 2026-09-22 -->
# All Errata Descriptions - ESP32-C5 -  — ESP Chip Errata latest documentation

# All Errata Descriptions

[[中文]](https://docs.espressif.com/projects/esp-chip-errata/zh_CN/latest/esp32c5/03-errata-description/index.html)

## [CPU-718] PSRAM Read-After-Write Consistency

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c5/_tags/v0-0.html) [v0.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c5/_tags/v0-1.html) [v1.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c5/_tags/v1-0.html)

### Description

When the CPU performs random read or write accesses to PSRAM through CACHE or DMA, and one of the following conditions is true:

- PSRAM encryption or decryption is enabled, or
- When accessing PSRAM via DMA, AHB\_DMA\_OUT\_DATA\_BURST\_MODE\_SEL\_CHn is set to 0 or 1.

Data-consistency issues may occur for CPU accesses to PSRAM.

#### Cause

The MSPI hardware handles CPU read or write requests to PSRAM and uses an internal buffer or cache. Because of this buffering (and encryption or decryption latency), CPU read or write requests received by MSPI are not always executed on the SPI bus immediately.

If the CPU performs a write to a PSRAM address and then quickly issues a read to the same physical address, the write may still be delayed inside MSPI. In that case, MSPI can execute the read before the earlier write has actually completed on the PSRAM, leading to stale or inconsistent data being returned.

#### Examples

- If CACHE reads from an encrypted or decrypted PSRAM region and a cache miss occurs, the data written back can be inconsistent.
- After a DMA write to PSRAM completes, a subsequent DMA read or CACHE read of the same PSRAM region may return inconsistent data.

### Workarounds

- For consistency problems caused by cache misses during encryption or decryption: Avoid enabling PSRAM encryption in workloads that perform random read or write access.
- For consistency problems when the CPU accesses PSRAM via DMA: Insert a short delay after the DMA write finishes, or before the CPU reads the same physical address, to ensure MSPI has completed the actual PSRAM write.

### Solution

Fixed in chip revision v1.2.

## [SRAM-436] Internal SRAM Contents May Be Corrupted After Digital Peripheral Power Domain Power-Down

Affected revisions: [v1.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c5/_tags/v1-0.html)

### Description

On some ESP32-C5 v1.0 chips, when the power-down feature of the digital peripheral power domain is enabled, part of the internal SRAM contents may be corrupted. This may trigger a CPU\_LOCKUP reset or cause the system to hang.

### Workaround

Starting from ESP-IDF v5.5, the power-down feature of the digital peripheral power domain is disabled for ESP32-C5 v1.0 chips.

### Solution

Fixed in hardware starting from chip revision v1.2.

## [HUK-576] HUK Is Unavailable

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c5/_tags/v0-0.html) [v0.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c5/_tags/v0-1.html) [v1.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c5/_tags/v1-0.html)

### Description

On ESP32-C5 chips, inrush current during power-on can cause the first HUK recovery attempt to fail with a certain probability.

In the affected chip revisions, the ROM uses the HUK data immediately after power-on to derive flash encryption and decryption keys through the key manager (introduced in ESP-IDF v5.5.2). When HUK recovery fails, the ROM may fail to derive these keys.

### Workaround

No workaround.

### Solution

Fixed in chip revision v1.2.

The updated ROM re-powers the HUK and retries recovery if the initial attempt fails.

## [FLASH-938] Flash Manual Encryption May Fail When CPU Runs at 240 MHz

Affected revisions: [v1.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c5/_tags/v1-0.html) [v1.2](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c5/_tags/v1-2.html)

### Description

On ESP32-C5 chips, flash manual encryption may fail when the CPU frequency is set to 240 MHz due to internal power consumption fluctuations.

### Workaround

When performing flash manual encryption, configure the CPU frequency to 160 MHz or lower.

### Solution

No fix scheduled.

## [ECC-833] Forcing ECC Memory Power-Down Bypasses ECDSA\_DS Signature Verification

Affected revisions: [v1.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c5/_tags/v1-0.html) [v1.2](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c5/_tags/v1-2.html)

### Description

On ESP32-C5 chips, if ECC memory is force-powered down via the system register, ECDSA\_DS reports any submitted signature as valid.

### Workaround

Use RSA\_DS instead of ECDSA\_DS for signature verification.

### Solution

To be fixed in the next chip revision.
