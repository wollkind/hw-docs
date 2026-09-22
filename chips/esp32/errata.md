<!-- source: https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/03-errata-description/index.html | fetched: 2026-09-22 -->
# All Errata Descriptions - ESP32 -  — ESP Chip Errata latest documentation

# All Errata Descriptions

[[中文]](https://docs.espressif.com/projects/esp-chip-errata/zh_CN/latest/esp32/03-errata-description/index.html)

## [CPU-3.5] The CPU Crashes When the Clock Frequency Switches

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v0-0.html)

### Description

The CPU crashes when the clock frequency switches directly from 240 MHz to 80/160 MHz

### Workarounds

When switching frequencies, use intermediate frequencies as follows:

> 1. 2 MHz <-> 40 MHz <-> 80 MHz <-> 160 MHz
> 2. 2 MHz <-> 40 MHz <-> 240 MHz

### Solution

Fixed in chip revision v1.0.

## [CPU-3.18] CPU Has Limitations When Accessing Peripherals in Chips

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v0-0.html) [v1.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-0.html) [v1.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-1.html) [v3.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-0.html) [v3.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-1.html)

### Description

As described in [[CPU-3.3] When the CPU Accesses Peripherals and Writes a Single Address Repeatedly, Some Writes May Be Lost](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/03-errata-description/esp32/cpu-writes-lost.html), [[CPU-3.10] When Each CPU Reads Certain Different Address Spaces Simultaneously, a Read Error May Occur](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/03-errata-description/esp32/cpu-read-error-of-dual-core-cpu.html), [[CPU-3.16] There Are Limitations to the CPU Access to 0x3ff0\_0000 ~ 0x3ff1\_efff and 0x3ff4\_0000 ~ 0x3ff7\_ffff Address Spaces](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/03-errata-description/esp32/cpu-limited-access-to-address-spaces.html), CPU has limitations when accessing peripherals in chips of different revisions using 0x3FF0\_0000 ~ 0x3FF1\_EFFF, 0x3FF4\_0000 ~ 0x3FF7\_FFFF, and 0x6000\_0000 ~ 0x6003\_FFFF.

| Address space (Bus) | Register type | Operation | Chip Revision | | | | |
| --- | --- | --- | --- | --- | --- | --- | --- |
| v0.0 | v1.0 | v1.1 | v3.0 | v3.1 |
| 0x3FF0\_0000 ~ 0x3FF1\_EFFF and 0x3FF4\_0000 ~ 0x3FF7\_FFFF (DPORT) | Non- FIFO | Write | Yes | | | Yes | |
| Read | No (refer to [[CPU-3.10] When Each CPU Reads Certain Different Address Spaces Simultaneously, a Read Error May Occur](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/03-errata-description/esp32/cpu-read-error-of-dual-core-cpu.html)) | | | Yes | |
| FIFO | Write | No (refer to [[CPU-3.3] When the CPU Accesses Peripherals and Writes a Single Address Repeatedly, Some Writes May Be Lost](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/03-errata-description/esp32/cpu-writes-lost.html)) | Yes | | | |
| Read | Yes | Yes | | | |
| 0x6000\_0000 ~ 0x6003\_FFFF (AHB) | Non- FIFO | Write | Yes | | | | |
| Read | Yes | | | | |
| FIFO | Write | Yes | | | | |
| Read | No (No such feature, unpredictable results) | | | | |

Note

- Yes: operation is executed correctly
- No: operation fails

## [CPU-3.16] There Are Limitations to the CPU Access to 0x3ff0\_0000 ~ 0x3ff1\_efff and 0x3ff4\_0000 ~ 0x3ff7\_ffff Address Spaces

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v0-0.html) [v1.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-0.html) [v1.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-1.html) [v3.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-0.html) [v3.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-1.html)

### Description

1. The CPU read operations that fall in these two address spaces are speculative. Speculative read operations can cause the behavior described by the program to be inconsistent with the actual behavior of the hardware.
2. If the two CPUs continuously access address space 0x3FF0\_0000 ~ 0x3FF1\_EFFF at the same time, some of the access may be lost.
3. When the CPU reads FIFO through the address space 0x3FF4\_0000 ~ 0x3FF7\_0000, the FIFO read pointer is updated with delays. As the CPU frequency increases, the interval between two consecutive FIFO reads initiated by the CPU is shortened. When a new FIFO read request arrives, the FIFO read pointer has not been updated, causing the CPU to read the value of the previous FIFO read operation.

### Workarounds

1. Insert “MEMW” instruction before the CPU access operation that falls in these two address spaces. That is, in C/C++, software needs to always use the “volatile” attribute when accessing registers in these two address spaces.
2. When the CPU frequency is 160 MHz, add six “nop” between two consecutive FIFO reads. When the CPU frequency is 240 MHz, add seven “nop” between two consecutive FIFO reads.

### Solution

No fix scheduled.

## [CPU-3.9] When the CPU Accesses External Sram in a Certain Sequence, Read and Write Errors May Occur

Affected revisions: [v1.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-0.html) [v1.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-1.html)

### Description

This error may occur when the CPU executes the following instructions to access external SRAM:

```
store.x at0, as0, n
load.y at1, as1, m
```

In the pseudo-assembly instructions above, `store.x` represents an x-bit write operation, while `load.y` represents a y-bit read operation. `as0+n` and `as1+m` represent the same address in external SRAM.

- The instructions can be sequential or contained within the same pipeline (less than four intermediate instructions, and no pipeline flushes.)
- When x >= y, the data write may be lost. (NOTE: when both the `load` and the `store` refer to 32-bit values, the write is only lost if an interrupt occurs between the first and second instructions.)
- When x < y, data writes may be lost and invalid data may be read.

### Workarounds

This bug is automatically worked around when external SRAM use is enabled in ESP-IDF v3.0 and newer.

- When x >= y, insert four nop instructions between `store.x` and `load.y`.
- When x < y, insert a memw instruction between `store.x` and `load.y`.

### Solution

Fixed in chip revision v3.0.

## [CPU-3.2] When the CPU Accesses External Sram Through Cache, Under Certain Conditions Read and Write Errors Occur

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v0-0.html)

### Description

Access to external SRAM through cache will cause read and write errors if these operations are pipelined together by the CPU.

### Workarounds

If accessing external SRAM from chip revision v0.0, users must ensure that access is always one-way—only a write or a read can be in progress at a single time in the CPU pipeline.

The MEMW instruction can be used: insert \_\_asm\_\_(“MEMW”) after any read from external PSRAM that may be followed by a write to PSRAM before the CPU pipeline is flushed.

### Solution

Fixed in chip revision v1.0.

## [CPU-3.10] When Each CPU Reads Certain Different Address Spaces Simultaneously, a Read Error May Occur

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v0-0.html) [v1.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-0.html) [v1.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-1.html)

### Description

Running in dual-core CPU mode, when one CPU bus reads address space A (0x3FF0\_0000 ~ 0x3FF1\_EFFF), while the other CPU bus reads address space B (0x3FF4\_0000 ~ 0x3FF7\_FFFF), an incorrect read may be generated on the CPU reading address space B.

### Workarounds

Either of the following workarounds can be used:

- When either CPU reads address space A, prevent the other CPU bus from reading address space B via locks and interrupts.
- Before reading address space A, disable interrupts and insert a read from address space B on the same CPU (read a non-FIFO register, e.g., 0x3FF40078).

### Solution

Fixed in chip revision v3.0.

## [CPU-3.21] When a CPU Is Interrupted While Accessing Five Specific Fifo Registers, Subsequent CPU Accesses Will Get Halted

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v0-0.html) [v1.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-0.html) [v1.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-1.html) [v3.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-0.html) [v3.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-1.html)

### Description

When the CPU attempts to read five FIFO registers 0x3FF40000 (UART0), 0x3FF50000 (UART1), 0x3FF6E000 (UART2), 0x3FF4F004 (I2S0), and 0x3FF6D004 (I2S1), and if an interrupt occurs, the read request will be interrupted. This will cause the bus bridge to be stuck in a state of waiting for the read request to end. Consequently, the subsequent access to the APB peripheral registers (0x3FF40000 ~ 0x3FF7FFFF or 0x60000000 ~ 0x6003FFFF) by any CPUs will be rejected and halted.

Writing to these five FIFO registers does not have such an issue.

### Workarounds

Disable CPU interrupts before reading these five FIFO registers. Enable CPU interrupts after read access.

### Solution

No fix scheduled.

## [CPU-3.3] When the CPU Accesses Peripherals and Writes a Single Address Repeatedly, Some Writes May Be Lost

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v0-0.html)

### Description

Some ESP32 peripherals are mapped to two internal memory buses (AHB & DPORT). When written via DPORT, consecutive writes to the same address may be lost.

### Workarounds

When writing the same register address (i.e., FIFO-like addresses) in sequential instructions, use the equivalent AHB address not the DPORT address. (For other kinds of register writes, using DPORT registers will give better write performance.)

| Registers | DPORT Addresses | AHB (Safe) Addresses |
| --- | --- | --- |
| UART\_FIFO\_REG | 0x3FF40000 | 0x60000000 |
| UART1\_FIFO\_REG | 0x3FF50000 | 0x60010000 |
| UART2\_FIFO\_REG | 0x3FF6E000 | 0x6002E000 |
| I2S0\_FIFO\_RD\_REG | 0x3FF4F004 | 0x6000F004 |
| I2S1\_FIFO\_RD\_REG | 0x3FF6D004 | 0x6002D004 |
| GPIO\_OUT\_REG | 0x3FF44004 | 0x60004004 |
| GPIO\_OUT\_W1TS\_REG | 0x3FF44008 | 0x60004008 |
| GPIO\_OUT\_W1TC\_REG | 0x3FF4400C | 0x6000400C |
| GPIO\_OUT1\_REG | 0x3FF44010 | 0x60004010 |
| GPIO\_OUT1\_W1TS\_REG | 0x3FF44014 | 0x60004014 |
| GPIO\_OUT1\_W1TC\_REG | 0x3FF44018 | 0x60004018 |
| GPIO\_ENABLE\_REG | 0x3FF44020 | 0x60004020 |
| GPIO\_ENABLE\_W1TS\_REG | 0x3FF44024 | 0x60004024 |
| GPIO\_ENABLE\_W1TC\_REG | 0x3FF44028 | 0x60004028 |
| GPIO\_ENABLE1\_REG | 0x3FF4402C | 0x6000402C |
| GPIO\_ENABLE1\_W1TS\_REG | 0x3FF44030 | 0x60004030 |
| GPIO\_ENABLE1\_W1TC\_REG | 0x3FF44034 | 0x60004034 |

### Solution

Fixed in chip revision v1.0.

Note

Software cannot use AHB addresses to read FIFO.

## [ULP-3.19] ULP Coprocessor And Touch Sensors Can Not Be Used In Deep-sleep Mode If RTC\_PERIPH Power Domain Is Powered Up

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v0-0.html) [v1.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-0.html) [v1.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-1.html) [v3.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-0.html) [v3.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-1.html)

### Description

The main operating clock for the ULP coprocessor and touch sensor is **FAST\_CLK**. In **Deep-sleep** mode, if the **RTC\_PERIH** power domain (RTC Peripherals) remains powered up, the ULP coprocessor and touch sensor will receive the wake-up signal earlier than the clock management module. This causes them to operate under **SLOW\_CLK** for a period before switching to **FAST\_CLK**, leading to inaccuracies in the operating clock. Therefore, in Deep-sleep mode, if RTC\_PERIH is powered up, the ULP co-processor and touch sensor cannot be used.

### Workarounds

If the user wants to utilize the ULP coprocessor and touch sensor functionalities, the RTC\_PERIPH must remain powered down in Deep-sleep mode. Note that during this time, the **EXT0** wake-up is not available, as it only operates when RTC\_PERIPH is powered up.

Users need to make a trade-off between using the EXT0 wake-up function and the ULP coprocessor and touch sensor functionalities:

- **If the EXT0 wake-up function is needed**: The RTC\_PERIPH power domain must remain powered up, and the ULP coprocessor and touch sensor functionalities will not be available.
- **If the ULP coprocessor and touch sensor functionalities are needed**: The RTC\_PERIPH must remain powered down, and the EXT0 wake-up function will not be available.

### Solution

No fix scheduled.

## [GPIO-3.6] For Pads With Both GPIO and RTC\_GPIO Functionality, the GPIO Pull-up and Pull-down Configuration Register Fields Are Nonfunctional

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v0-0.html) [v1.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-0.html) [v1.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-1.html) [v3.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-0.html) [v3.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-1.html)

### Description

GPIO pull-up and pull-down resistors for pads with both GPIO and RTC\_GPIO functionality can only be controlled via RTC\_GPIO registers.

### Workarounds

Use RTC\_GPIO registers for both GPIO and RTC\_GPIO functions.

### Solution

This issue is automatically worked around when using GPIO drivers in ESP-IDF v2.1 or newer.

## [GPIO-3.14] Within the Same Group of GPIO Pins, Edge Interrupts Cannot Be Used Together With Other Interrupts

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v0-0.html) [v1.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-0.html) [v1.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-1.html) [v3.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-0.html) [v3.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-1.html)

### Description

GPIO0 ~ GPIO31 share a set of interrupt configuration registers and belong to one group, GPIO32 ~ GPIO39 share another set of registers and belong to another group, and RTC GPIO0 ~ GPIO17 share yet another set of registers and belong to yet another group. If one GPIO pad within a group is configured with edge-triggered interrupt, then other interrupts (including both edge-triggered and level-triggered interrupts within that group cannot be configured.

There is no such limitation for level-triggered interrupts, which means, if there are no edgetriggered interrupts configured within a group, then there can be any number of leveltriggered interrupts in that group.

### Reason

When the following three sets of STATUS/W1TS/W1TC registers for GPIOs are being operated, edge-triggered interrupts may not be properly triggered within the same group.

- When the following registers are being operated, edge-triggered interrupts for GPIO\_STATUS\_REG may not be properly triggered:

  > - GPIO\_STATUS\_W1TS\_REG
  > - GPIO\_STATUS\_W1TC\_REG
  > - GPIO\_STATUS\_REG
- When the following registers are being operated, edge-triggered interrupts for GPIO\_STATUS1\_REG may not be properly triggered:

  > - GPIO\_STATUS1\_W1TS\_REG
  > - GPIO\_STATUS1\_W1TC\_REG
  > - GPIO\_STATUS1\_REG
- When the following registers are being operated, edge-triggered interrupts for RTCIO\_RTC\_GPIO\_STATUS\_REG may not be properly triggered:

  > - RTCIO\_RTC\_GPIO\_STATUS\_W1TS\_REG
  > - RTCIO\_RTC\_GPIO\_STATUS\_W1TC\_REG
  > - RTCIO\_RTC\_GPIO\_STATUS\_REG

### Workarounds

Simulate edge-triggered interrupts using level-triggered interrupts, as outlined below.

To trigger a GPIO interrupt on a rising edge, follow the steps:

1. Set the GPIO interrupt type to high.
2. After the CPU services the interrupt, change the GPIO interrupt type to low. A second interrupt occurs at this time, and the CPU needs to ignore the interrupt service routine.

To trigger a GPIO interrupt on a falling edge, follow the steps:

1. Set the GPIO interrupt type to low.
2. After the CPU services the interrupt, change the GPIO interrupt type to high. A second interrupt occurs at this time, and the CPU needs to ignore the interrupt service routine.

### Solution

No fix scheduled.

## [GPIO-3.11] When Certain RTC Peripherals Are Powered on, the Inputs of GPIO36 and GPIO39 Will Be Pulled Down for Approximately 80 ns

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v0-0.html) [v1.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-0.html) [v1.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-1.html) [v3.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-0.html) [v3.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-1.html)

### Description

Powering on the following RTC peripherals will trigger this issue:

- SAR ADC1
- SAR ADC2
- AMP

### Workarounds

When enabling power for any of these peripherals, ignore input from GPIO36 and GPIO39.

### Solution

No fix scheduled.

## [RES-3.4] The Brown-out Reset (BOR) Function Does Not Work

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v0-0.html)

### Description

The Brown-out Reset (BOR) function does not work. The system fails to boot up after BOR.

### Workarounds

There is no workaround for this issue.

### Solution

Fixed in chip revision v1.0.

## [RES-3.1] A Spurious Watchdog Reset Occurs When ESP32 Is Powered up or Wakes up From Deep-sleep

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v0-0.html)

### Description

A spurious watchdog reset occurs when ESP32 is powered up or wakes up from Deep-sleep.

### Workarounds

To work around the watchdog reset when waking from Deep-sleep, the CPU can execute a program from RTC fast memory. This program must clear the illegal access flag in the cache MMU as follows:

> 1. Set the PRO\_CACHE\_MMU\_IA\_CLR bit in DPORT\_PRO\_CACHE\_CTRL1\_REG to 1.
> 2. Clear this bit.

During initial power-up the spurious watchdog reset cannot be worked around, but ESP32 will boot normally after this reset.

### Solution

Fixed in chip revision v1.0.

## [RES-3.8] Due to the Flash Start-up Time, a Spurious Watchdog Reset Occurs When ESP32 Is Powered up or Wakes up From Deepsleep

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v0-0.html) [v1.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-0.html) [v1.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-1.html)

### Description

If the ESP32 reads from the flash chip before it is ready, invalid data can cause booting to fail until a Watchdog Timer reset occurs. This can occur on power-on and on wake from Deep-sleep, if the ESP32 VDD\_SDIO is used to power the flash chip.

### Workarounds

1. Replace the flash chip with one with a fast start-up time (<800 μs from power-on to ready to read). This works around the issue for both power-on and wake from Deepsleep.
2. When waking from Deep-sleep, this issue is automatically worked around in ESP-IDF v2.0 and newer (the delay to wait can be configured if necessary). In this workaround, the CPU executes from RTC fast memory immediately after waking and a delay is added before continuing to read the program from flash.

### Solution

Fixed in chip revision v3.0.

## [CLK-3.7] Audio Pll Frequency Range Is Limited

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v0-0.html)

### Description

When configuring the Audio PLL, configuration registers sdm0 & sdm1 are not used. This limits the range and precision of PLL frequencies which can be configured.

For chip revision v0.0, the Audio PLL frequency is calculated in hardware as follows:

\[f\_{out} = \frac{f\_{xtal} \times (sdm2 + 4)}{2 \times (odiv + 2)}\]

For chip revision v1.0 onwards this bug is fixed and the Audio PLL frequency is calculated in hardware as follows:

\[f\_{out} = \frac{f\_{xtal} \left(sdm2 + \frac{sdm1}{2^8} + \frac{sdm0}{2^{16}} + 4 \right)}{2 \times (odiv + 2)}\]

### Workarounds

The particular hardware frequency calculation is automatically accounted for when setting Audio PLL frequency via the I2S driver in ESP-IDF v3.0 and newer. However, the range and precision of available Audio PLL frequencies is still limited when using chip revision v0.0.

### Solution

Fixed in chip revision v1.0.

## [CLK-3.22] ESP32 Cannot Be Used as the PHY Clock Source If Wi-fi and Ethernet Are Used at the Same Time

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v0-0.html) [v1.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-0.html) [v1.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-1.html) [v3.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-0.html) [v3.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-1.html)

### Description

In RMII working mode, the Ethernet MAC and PHY require a common 50 MHz reference clock (i.e., the RMII clock). If Wi-Fi and Ethernet are used simultaneously, the RMII clock cannot be generated by the internal APLL clock, as it would result in clock instability.

### Workarounds

1. If you want to use the internal APLL to generate the reference clock, you need to disable Wi-Fi.
2. If you want to use both Ethernet and Wi-Fi simultaneously, you need to use an external PHY or external clock source to provide the reference clock.

### Solution

No fix scheduled.

## [RTC-126] RTC Register Read Error After Wake-up from Light-sleep Mode

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v0-0.html) [v1.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-0.html) [v1.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-1.html) [v3.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-0.html) [v3.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-1.html)

### Description

If an RTC peripheral is turned off in Light-sleep mode, there is a certain probability that after waking up from Light-sleep, the CPU of ESP32 will read the registers in the RTC power domain incorrectly.

### Workarounds

Users are suggested not to power down RTC peripherals in Light-sleep mode. There will be no impact on power consumption.

### Solution

No fix scheduled.

## [WDT-3.15] {idf\_target\_name} Chip May Have A Live Lock Under Certain Conditions That Will Cause Interrupt Watchdog Issue

Affected revisions: [v3.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-0.html) [v3.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-1.html)

### Description

On ESP32 chip revision v3.0, when the following conditions are met at the same time, a live lock will occur, causing the CPUs to get stuck in the state of memory access and stop executing instructions.

1. Dual-core system.
2. Of the four Instruction/Data buses (IBUS/DBUS) that access external memory, three simultaneously initiate access requests to the same cache set, and all three requests result in cache misses.

### Workarounds

When a live lock occurs, software proactively or passively recognizes and unlocks the cache line contention, and then the two cores complete their respective cache operations one after another, following a first-come, first-served policy, to resolve the live lock. The detailed process is as follows:

1. If the live lock occurs when the instructions executed by the two cores are not in the critical section of the code, the various types of system interruptions will proactively release the cache line competition and resolve the live lock.
2. If the live lock occurs when the instructions executed by the two cores are located in the critical section of the code, the system will mask interrupts at level 3 and below. Therefore, software needs to set up a high priority (level 4 or 5) interrupt for each core in advance, connect the interrupts to the same timer, and configure an appropriate timeout threshold. The timer timeout interrupt generated by the live lock will force both cores to enter the high-priority interrupt handler, thereby releasing the IBUS of both cores to resolve the live lock. The live lock resolution process is completed in three stages:

   > 1. In the first stage, both cores wait for the CPU write buffer to be cleared.
   > 2. In the second stage, one core (Core 0) waits and the other core (Core 1) executes instructions.
   > 3. In the third stage, Core 1 waits and Core 0 executes instructions.

### Solution

No fix scheduled.

## [UART-3.17] UART fifo\_cnt Does Not Indicate the Data Length In Fifo Correctly

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v0-0.html) [v1.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-0.html) [v1.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-1.html) [v3.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-0.html) [v3.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-1.html)

### Description

When software uses DPORT to read UART fifo\_cnt, and such operation is interrupted, then fifo\_cnt will decrement by 1 erroneously.

### Workarounds

When using DPort to read fifo, calculate the real count based on the FIFO read and write offset address. For example:

```
if (wr_addr > rd_addr) {
    len = wr_addr - rd_addr;
} else if (wr_addr < rd_addr){
    len = (wr_addr + 128) - rd_addr;
} else {
    len = fifo_cnt > 0 ? 128 : 0;
}
```

In the above code snippet, `wr_addr` represents the FIFO write offset address, `rd_addr` represents the FIFO read offset address, `fifo_cnt` represents the number of valid bytes in the FIFO, `len` represents the correct number of valid bytes after calculation.

### Solution

No fix scheduled.

## [TWAI-3.13.6] After Losing Arbitration, a Dominant Bit on the 3rd Bit of Intermission Is Not Interpreted as an SOF

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v0-0.html) [v1.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-0.html) [v1.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-1.html) [v3.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-0.html) [v3.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-1.html)

### Description

The CAN2.0B protocol stipulates that a dominant bit on the 3rd bit of intermission shall be interpreted as a Start of Frame (SOF). Therefore, nodes shall begin receiving or transmitting (i.e., competing for arbitration) the ID field on the next bit.

When the TWAI controller loses arbitration and the following intermission’s 3rd bit is dominant, the TWAI controller will not interpret this as an SOF and will make no attempt to compete for arbitration (i.e., does not retransmit its frame).

### Workarounds

There is no workaround for this issue.

### Solution

No fix scheduled.

## [TWAI-3.13.3] Message Transmitted After Bus-off Recovery Is Erroneous

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v0-0.html) [v1.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-0.html) [v1.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-1.html) [v3.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-0.html) [v3.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-1.html)

### Description

Upon completion of bus-off recovery, the next message that the TWAI controller transmits may be erroneous (i.e., does not adhere to TWAI frame format).

### Workarounds

Upon detecting the completion of bus-off recovery (via the error warning interrupt), the TWAI controller should enter then exit reset mode so that the controller’s internal signals are reset.

### Solution

No fix scheduled.

## [TWAI-3.13.7] When the 8th Bit of the Error Delimiter Is Dominant, the Error Passive State Is Not Entered

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v0-0.html) [v1.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-0.html) [v1.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-1.html) [v3.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-0.html) [v3.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-1.html)

### Description

When the TWAI controller is the transmitter and has a TEC value between 120 and 127, transmitting an error frame will increment its TEC by 8 thus make the controller error passive (due to TEC becoming >= 128). However, if the 8th bit of the error delimiter is dominant, the TEC will still increment by 8 but the controller will not become error passive. Instead, the controller will become error passive when another error frame is transmitted. Note that the controller will still generate the required overload frame due to the dominant 8th bit.

### Workarounds

There is no workaround for this issue.

### Solution

No fix scheduled.

## [TWAI-3.13.2] Error Status Bit Is Not Frozen During Bus-off Recovery

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v0-0.html) [v1.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-0.html) [v1.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-1.html) [v3.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-0.html) [v3.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-1.html)

### Description

When the TWAI controller undergoes the bus-off recovery process, the controller must monitor 128 occurrences of the bus free signal (11 consecutive recessive bits) before it can become error active again. The number of bus-free signals remaining is indicated by the transmit error counter (TEC). Because the error status bit is not frozen during bus-off recovery, its value will change when the transmit error counter drops below the user-defined transmit error warning limit (96 by default) thus trigger the error warning limit interrupt before bus-off recovery has completed.

### Workarounds

When undergoing bus-off recovery, an error warning interrupt does not necessarily indicate the completion of recovery. Users should check the STATUS\_NODE\_BUS\_OFF bit to verify whether bus-off recovery has completed.

### Solution

No fix scheduled.

## [TWAI-3.13.5] Receiving an Erroneous Data Frame Can Cause the Data Bytes of the Next Received Data Frame to Be Invalid

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v0-0.html) [v1.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-0.html) [v1.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-1.html) [v3.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-0.html) [v3.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-1.html)

### Description

When the TWAI controller is receiving a data frame and a bit or stuff error occurs in the data or CRC fields, some data bytes of the next received data frame may be shifted or lost. Therefore, the next received data frame (including those filtered out by the acceptance filter) should be considered invalid.

### Workarounds

Users can detect the errata triggering condition (i.e., bit or stuff error in the data or CRC field) by setting the INTERRUPT\_BUS\_ERR\_INT\_ENA and checking the ERROR\_CODE\_CAPTURE\_REG when a bus error interrupt occurs. If the errata condition is met, the following workarounds are possible:

- The TWAI controller can transmit a dummy frame with 0 data bytes to reset the controller’s internal signals. It is advisable to select an ID for the dummy frame that can be filtered out by all nodes on the TWAI bus.
- Hardware reset the TWAI controller (will require saving and restoring the current register values).

### Solution

No fix scheduled.

## [TWAI-3.13.10] A Negative Phase Error Where |e| > SJW (N) Will Cause the Remaining Transmitted Bits to Be Left Shifted

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v0-0.html) [v1.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-0.html) [v1.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-1.html) [v3.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-0.html) [v3.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-1.html)

### Description

When the TWAI controller encounters a recessive to dominant edge with a negative phase error (i.e., the edge is early), it will correct for the phase error using resynchronization as required by the CAN2.0B protocol. However, if the TWAI controller is acting as transmitter and encounters a negative phase error where e < 0 and |e| > SJW, the bits transmitted following the phase error will be left shifted by one bit. Thus, the transmitted frame’s contents (i.e., DLC, data bytes, CRC sequence) will be corrupted.

### Workarounds

There is no workaround for this issue.

### Solution

No fix scheduled.

## [TWAI-3.13.1] Receive Error Counter (REC) Is Allowed to Change Whilst in Reset Mode or Bus-off Recovery

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v0-0.html) [v1.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-0.html) [v1.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-1.html) [v3.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-0.html) [v3.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-1.html)

### Description

When the TWAI controller enters reset mode (e.g., by setting the RESET\_MODE bit or due to a bus-off condition) or when the TWAI controller undergoes bus-off recovery, the REC is still permitted to change. This can lead to the following cases:

- Whilst in reset mode or bus-off recovery, a changing REC can lead to the error status bit changing which in turn could trigger the error warning limit interrupt.
- During bus-off recovery, an REC > 0 can prevent the bus-off recovery process from completing.

### Workarounds

When entering reset mode, the TWAI controller should set the LISTEN\_ONLY\_MODE to freeze the REC. The desired mode of operation should be restored before exiting reset mode or when bus-off recovery completes.

### Solution

No fix scheduled.

## [TWAI-3.13.11] When the RX Fifo Overruns With 64 or More Messages, the RX Fifo Becomes Unrecoverable

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v0-0.html) [v1.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-0.html) [v1.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-1.html) [v3.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-0.html) [v3.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-1.html)

### Description

When the RX FIFO overruns with multiple messages, and the RX message counter reaches 64, the RX FIFO will become unrecoverable. Any message read from the RX FIFO will be invalid. Attempting to release a message from the RX FIFO will have no effect.

### Workarounds

The TWAI controller must be reset by software in order to recover the RX FIFO.

### Solution

This issue is automatically worked around in ESP-IDF v4.3 and newer.

## [TWAI-3.13.8] Suspend Transmission Is Included Even After Losing Arbitration

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v0-0.html) [v1.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-0.html) [v1.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-1.html) [v3.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-0.html) [v3.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-1.html)

### Description

The CAN2.0B protocol stipulates that an error passive node that was the transmitter of a message shall add a suspend transmission field within the subsequent interframe space. However, error passive receivers shall not add a suspend transmission field.

When the TWAI controller is error passive and loses arbitration (hence becomes a receiver), it will still add a suspend transmission field in the subsequent interframe space. This results in the TWAI controller being late to start retransmission. Therefore, if another node transmits immediately after the interframe space is over, the TWAI controller will fail to compete for arbitration due to the other nodes not including a suspend transmission field in their interframe space (as per CAN2.0B specification).

### Workarounds

There is no workaround for this issue.

### Solution

No fix scheduled.

## [TWAI-3.13.9] When a Stuff Error Occurs During Arbitration Whilst Being Transmitter, Any Errors in the Subsequent Error/Overload Frame Will Not Increase the TEC

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v0-0.html) [v1.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-0.html) [v1.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-1.html) [v3.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-0.html) [v3.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-1.html)

### Description

When a stuff error occurs during arbitration whilst being transmitter, the CAN2.0B protocol stipulates that an error frame be transmitted but the TEC should not increase (Exception 2 of Rule 3). The TWAI controller is able to fulfill these requirements without issue.

However, errors within the subsequent error/overload frames themselves will fail to increase the TWAI controller’s TEC. Therefore, when a stuff error occurs during arbitration whilst being transmitter, the TEC will fail to increase in the following cases:

- Bit error in an active error flag or overload flag (Rule 4).
- Detecting too many dominant bits after the transmission of active error, passive error flag, and overload flags (Rule 6).

### Workarounds

There is no workaround for this issue.

### Solution

No fix scheduled.

## [TWAI-3.13.4] Reading the Interrupt Register May Lead to a Transmit Interrupt Being Lost

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v0-0.html) [v1.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-0.html) [v1.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-1.html) [v3.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-0.html) [v3.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-1.html)

### Description

The TWAI controller’s interrupt signals are cleared by reading the INTERRUPT\_REG. However, if a transmit interrupt occurs whilst the INTERRUPT\_REG is being read (i.e., in the same APB clock cycle), the transmit interrupt is lost.

### Workarounds

When a message is awaiting completion of transmission (i.e., transmission has been requested), users should also check the STATUS\_TRANSMIT\_BUFFER bit each time the INTERRUPT\_REG is read. A set STATUS\_TRANSMIT\_BUFFER bit whilst the TWAI\_TRANSMIT\_INT\_ST is not indicates a lost transmit interrupt.

### Solution

No fix scheduled.

## [LEDC-3.12] When the LEDC Is in Decremental Fade Mode, a Duty Overflow Error May Occur

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v0-0.html) [v1.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-0.html) [v1.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v1-1.html) [v3.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-0.html) [v3.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32/_tags/v3-1.html)

### Description

This issue may happen when the LEDC is in decremental fade mode and LEDC\_DUTY\_SCALE\_HSCH*n* is 1. If the duty is 2LEDC\_HSTIMERx\_DUTY\_RES, then the next one should be 2LEDC\_HSTIMERx\_DUTY\_RES – 1, however, the next duty is actually 2LEDC\_HSTIMERx\_DUTY\_RES+1, which indicates a duty overflow error. (HSCH*n* refers to high-speed channel with *n* being 0-7; HSTIMER*x* refers to high-speed timer with *x* being 0-3.)

For low-speed channels, the same issue may also happen.

### Workarounds

When using LEDC, avoid the concurrence of following three cases:

1. The LEDC is in decremental fade mode;
2. The scale register is set to 1;
3. The duty is 2LEDC\_HSTIMERx\_DUTY\_RES or 2LEDC\_LSTIMERx\_DUTY\_RES.

### Solution

This issue is automatically worked around in the LEDC driver since the ESP-IDF commit ID [b2e264e](https://github.com/espressif/esp-idf/commit/b2e264ef52ae368b3b371bf6872fe29bd2b8b5df) and is released in ESP-IDF v3.1.
