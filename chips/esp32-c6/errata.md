<!-- source: https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c6/03-errata-description/index.html | fetched: 2026-09-23 -->
# All Errata Descriptions - ESP32-C6 -  — ESP Chip Errata latest documentation

# All Errata Descriptions

[[中文]](https://docs.espressif.com/projects/esp-chip-errata/zh_CN/latest/esp32c6/03-errata-description/index.html)

## [CPU-206] Possible Deadlock Due to Out-of-Order Execution of Instructions When Writing to LP SRAM Is Involved

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c6/_tags/v0-0.html) [v0.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c6/_tags/v0-1.html)

### Description

When HP CPU executes instructions (instruction A and instruction B successively) in LP SRAM, and instruction A and instruction B happen to follow the following patterns:

- Instruction A involves writing to memory. Examples: **sw**/**sh**/**sb**
- Instruction B involves only accessing the instruction bus. Examples: **nop**/**jal**/**jalr**/**lui**/**auipc**
- The address of instruction B is not 4-byte aligned

The data written by instruction A to memory is only committed after instruction B has completed execution. This introduces a risk where, after instruction A writing to memory, if an infinite loop is executed in instruction B, the writing of instruction A will never complete.

### Workarounds

When you experience this problem, or when you check the assembly code
and see the above mentioned pattern,

- Add a **fence** instruction between instruction A and the infinite loop. This can be achieved by using the *rv\_utils\_memory\_barrier* interface in ESP-IDF.
- Replace the infinite loop with instruction **wfi**. This can be achieved by using the *rv\_utils\_wait\_for\_intr* interface in ESP-IDF.
- Disable the RV32C (compressed) extension when compiling code that to be executed in LP SRAM to avoid instructions with not 4-byte aligned addresses.

### Solution

Fixed in chip revision v0.2.

## [CPU-863] Misaligned Memory Access May Lead to Exception

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c6/_tags/v0-0.html) [v0.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c6/_tags/v0-1.html) [v0.2](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c6/_tags/v0-2.html)

### Description

A misaligned **load** instruction immediately followed by a **store** instruction may raise a load access fault exception (exception code 5) when the load address and the store address lie in regions with different access permissions configured via Physical Memory Protection (PMP) or Physical Memory Attributes (PMA).

For example, the following sequence commonly triggers this issue when copying an unaligned word from flash or ROM into RAM:

```
lw  a0, 0(a1)   # unaligned 32-bit address load from a read-only PMP region (e.g., ROM)
sw  a0, 0(a2)   # store to a read-write PMP region (e.g., RAM)
```

**Root cause:**

A misaligned **load** that crosses a word boundary is split internally into two transactions. Due to a timing alignment issue in the design, the second transaction of the misaligned **load** can incorrectly be checked against the store’s access permissions instead of its own, triggering an exception.

### Workarounds

The RISC-V specification does not guarantee that hardware supports misaligned accesses. General-purpose RISC-V code should not rely on that support. If misaligned accesses cannot be avoided, such as when porting third-party libraries, use the following workarounds:

- Insert one or more **nop** instructions between the misaligned **load** and the following **store**. This prevents the incorrect permission check described above.

  Note

  Linkers that support the `--fix-esp-pmp-misalign` option can insert **nop** instructions between consecutive **load** and **store** instructions automatically. This option is conservative, as it may also insert extra **nop** instructions for pairs that would not trigger this exception, for example, when the accesses are aligned or when both access the same PMP region.
- When copying memory, use misaligned **load**/**store** only for the first and last misaligned words of a data block, and use aligned **load**/**store** for the words in between. This approach requires fewer **nop** instructions and has better performance than inserting **nop** instructions throughout.
- Configure the same PMP/PMA permissions for the memory regions accessed by the misaligned **load** and the following **store**. This may require saving and restoring the permission settings around the affected code.

### Solution

No fix scheduled.

## [CLK-6996] Inaccurate Calibration of RC\_FAST\_CLK Clock

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c6/_tags/v0-0.html)

### Description

In the ESP32-C6 chip, the frequency of the RC\_FAST\_CLK clock source is too close to the reference clock (40 MHz XTAL\_CLK) frequency, making it impossible to calibrate accurately. This may affect peripherals that use RC\_FAST\_CLK and have stringent requirements for its accurate clock frequency.

For peripherals using RC\_FAST\_CLK, please refer to *ESP32-C6 Technical Reference Manual > Chapter Reset and Clock* [[PDF](https://www.espressif.com/sites/default/files/documentation/esp32-c6_technical_reference_manual_en.pdf)].

### Workarounds

Use other clock sources instead of RC\_FAST\_CLK.

### Solution

Fixed in chip revision v0.1.

## [CLK-8588] 32 kHz Internal Slow RC Oscillator May Fail to Oscillate

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c6/_tags/v0-0.html) [v0.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c6/_tags/v0-1.html) [v0.2](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c6/_tags/v0-2.html)

### Description

The 32 kHz internal slow RC oscillator (RC32K\_CLK) may fail to oscillate in low-temperature scenarios, leading to malfunction in modules that rely on this clock.

For modules using RC32K\_CLK, please refer to the *ESP32-C6 Technical Reference Manual > Chapter Reset and Clock* [[PDF](https://www.espressif.com/sites/default/files/documentation/esp32-c6_technical_reference_manual_en.pdf)].

### Workarounds

Use the 136 kHz internal slow RC oscillator (RC\_SLOW\_CLK). For more information, please refer to [AR2024-011 Usage Instructions for Internal 32kHz RC Oscillator Clock Source in ESP32-C6 and Precautions for Changing the System Slow Clock Source via OTA](https://www.espressif.com/sites/default/files/advisory_downloads/AR2024-011_Usage_Instructions_for_Internal_32kHz_RC_Oscillator_Clock_Source_in_ESP32-C6_and_Precautions_for_Changing_the_System_Slow_Clock_Source_via_OTA_en.pdf).

### Solution

No fix scheduled.

## [RES-7080] System Reset Triggered by RTC Watchdog Timer Cannot Be Correctly Reported

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c6/_tags/v0-0.html)

### Description

When the RTC watchdog timer (RWDT) triggers a system reset, the reset source code can not be latched correctly. As a result, the reset cause reported is indeterminate and might be wrong.

### Workarounds

No workaround.

### Solution

Fixed in chip revision v0.1.

## [SPI-304] Enabling Flash Auto Suspend May Cause Abnormalities in Data Read

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c6/_tags/v0-0.html) [v0.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c6/_tags/v0-1.html)

### Description

After the flash auto suspend feature is enabled, read operations on the SPI0 bus and erase/program operations on the SPI1 bus can be executed concurrently. When software performs erase or program operations on flash via SPI1, and the cache reads flash via SPI0 from time to time, if the erase or program operation is executed first, the expected request sequence is: **ERASE or PROGRAM > SUSPEND or WFI (wait for idle) > READ**.

In practice, when the erase or program operation is executed first, the request sequence is: **ERASE or PROGRAM > READ**, which may cause data read abnormalities and program execution issues.

### Workarounds

Disable the auto suspend feature.

### Solution

Fixed in chip revision v0.2.

## [RMT-176] The Idle State Signal Level Might Run into Error in RMT Continuous TX Mode

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c6/_tags/v0-0.html) [v0.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c6/_tags/v0-1.html) [v0.2](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c6/_tags/v0-2.html)

### Description

In ESP32-C6’s RMT module, if the continuous TX mode is enabled, it is expected that the data transmission stops after the data is sent for RMT\_TX\_LOOP\_NUM\_CHn rounds, and after that, the signal level in idle state should be controlled by the “level” field of the end-marker.

However, in real situation, after the data transmission stops, the channel’s idle state signal level is not controlled by the “level” field of the end-marker, but by the level in the data wrapped back, which is indeterminate.

### Workarounds

Users are suggested to set RMT\_IDLE\_OUT\_EN\_CHn to 1 to only use registers to control the idle level.

This issue has been bypassed since the first ESP-IDF version that supports continuous TX mode (v5.1). In these versions of ESP-IDF, it is configured that the idle level can only be controlled by registers.

### Solution

No fix scheduled.

## [ADC-305] Data Duplication May Occur When SAR ADC Accessing GDMA

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c6/_tags/v0-0.html) [v0.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c6/_tags/v0-1.html)

### Description

When the SAR ADC accesses the DMA, if the clock frequency of AHB\_CLK and APB\_CLK are different, multiple DMA access will be triggered. The number of repeated access is directly proportional to the frequency ratio, resulting in the same data being stored repeatedly and wasting storage space.

### Workarounds

When using the SAR ADC, divide AHB\_CLK by 1 to generate APB\_CLK (configure the PCR\_APB\_DIV\_NUM field to 0, which is the default value).

### Solution

Fixed in chip revision v0.2.

## [ADC-1477] Loss of Precision in Lower Four Bits of SAR ADC

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c6/_tags/v0-0.html) [v0.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c6/_tags/v0-1.html)

### Description

The lower four bits of the SAR ADC data bits are missing, causing a loss of precision in the corresponding bits.

### Workarounds

No workaround.

### Solution

Fixed in chip revision v0.2.

## [WIFI-9686] ESP32-C6 Cannot Be 802.11mc FTM Initiator

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c6/_tags/v0-0.html) [v0.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32c6/_tags/v0-1.html)

### Description

The time of T3 (i.e., time of departure of ACK from Initiator) used in 802.11mc Fine Time Measurement (FTM) cannot be acquired correctly, and as a result ESP32-C6 cannot be the FTM Initiator.

### Workarounds

No workaround.

### Solution

Fixed in chip revision v0.2.
