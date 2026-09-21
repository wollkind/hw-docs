<!-- source: https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32s3/03-errata-description/index.html | fetched: 2026-09-21 -->
# All Errata Descriptions - ESP32-S3 -  — ESP Chip Errata latest documentation

# All Errata Descriptions

[[中文]](https://docs.espressif.com/projects/esp-chip-errata/zh_CN/latest/esp32s3/03-errata-description/index.html)

## [CACHE-126] Cache Hit Error During Cache Write-Backs

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32s3/_tags/v0-0.html) [v0.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32s3/_tags/v0-1.html) [v0.2](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32s3/_tags/v0-2.html)

### Description

When a cache write-back is in progress, if the CPU accesses other addresses within the same cache line, the access request will be treated as a cache miss. This triggers the miss handling module to reload the cache line from external memory, resulting in two identical cache data entries in the same cache line.

Due to hardware logic issues, the cache hit logic may select incorrect cache data, causing the CPU to return incorrect results. If the CPU also writes to the cache line, it may cause the data being written back to be lost.

For example, the following scenarios may lead to cache hit errors in ESP32-S3:

- Accessing data in a cache line that is being written back to the cache during an interrupt:

  During the cache write-back process, when the CPU is waiting for the write-back completion signal, an interrupt request occurs and the interrupt handler is entered, accessing the memory in the same buffer. If the data accessed by the handler and the write-back address are in the same cache line, cache hit errors may occur.
- Conflicts in a multi-core system:

  In a multi-core system, if CPU0 is waiting for a cache write-back to complete while CPU1 accesses the same cache line address, cache hit errors may occur.

### Workarounds

During a cache write-back, it is recommended that users take the following precautions at the same time:

- Disable interrupts on the current CPU, and re-enable them only after the cache write-back has completed.
- Enable the cache freeze feature to stop another CPU from accessing the cache.

This issue has been automatically bypassed using the above methods in ESP-IDF v4.4.6+, v5.0.4+, v5.1.1+, v5.2, and above versions.

### Solution

No fix scheduled.

## [RTC-126] RTC Register Read Error After Wake-up from Light-sleep Mode

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32s3/_tags/v0-0.html) [v0.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32s3/_tags/v0-1.html) [v0.2](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32s3/_tags/v0-2.html)

### Description

If an RTC peripheral is turned off in Light-sleep mode, there is a certain probability that after waking up from Light-sleep, the CPU of ESP32-S3 will read the registers in the RTC power domain incorrectly.

### Workarounds

Users are suggested not to power down RTC peripherals in Light-sleep mode. There will be no impact on power consumption.

This issue has been bypassed in ESP-IDF v4.4 and above.

### Solution

No fix scheduled.

## [ANALOG-160] Chip Will Be Damaged When BIAS\_SLEEP = 0 and PD\_CUR = 1

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32s3/_tags/v0-0.html) [v0.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32s3/_tags/v0-1.html) [v0.2](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32s3/_tags/v0-2.html)

### Description

If the analog power is configured as BIAS\_SLEEP = 0 and PD\_CUR = 1, the chip will be permanently damaged. This issue might be triggered when ULP and/or touch sensor is used during Light-sleep or Deep-sleep.

### Workarounds

Users are suggested to disable such analog power configuration in sleep mode through software.

This issue has been bypassed by disabling the above configuration in ESP-IDF v4.4.2+, v5.0 and above.

### Solution

No fix scheduled.

## [LCD-239] The LCD Module Exhibits Unreliable Behavior When Certain Clock Dividers Are Used

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32s3/_tags/v0-0.html) [v0.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32s3/_tags/v0-1.html) [v0.2](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32s3/_tags/v0-2.html)

### Description

1. When the RGB format is used, if the clock divider is set to 1, i.e., LCD\_CAM\_LCD\_CLK\_EQU\_SYSCLK = 1:

> - The pixel clock output (LCD\_PCLK) will not be able to be set to falling edge trigger.
> - When frames are continuously sent in this mode (i.e., LCD\_CAM\_LCD\_NEXT\_FRAME\_EN = 1), it might occur that the second frame inserts the last data of the previous frame in the first frame.

2. When the I8080 format is used, if the clock cycle of the LCD core clock (LCD\_CLK) before data transmission is less than or equal to 2, it can result in incorrect value of the first data and the subsequent data quantity.

> Note
>
> Please refer to the following steps to obtain the clock cycle before data transmission with the I8080 format.
>
> The clock cycle before data transmission depends on the following factors:
>
> - VFK cycle length (unit: LCD\_PCLK): The clock cycle length during the VFK phase
> - CMD cycle length (unit: LCD\_PCLK): The clock cycle length during the CMD phase
> - DUMMY cycle length (unit: LCD\_PCLK): The clock cycle length during the DUMMY phase
> - LCD\_CAM\_LCD\_CLK\_EQU\_SYSCLK: Decides if LCD\_PCLK equals LCD\_CLK
> - LCD\_CAM\_LCD\_CLKCNT\_N: Decides the division relationship between LCD\_PCLK and LCD\_CLK
>
> Based on the information above, three variables are defined below:
>
> - **total\_pixels** = VFK cycle length + CMD cycle length + DUMMY cycle length
> - **cycle\_unit** =
>
>   - 1, if LCD\_CAM\_LCD\_CLK\_EQU\_SYSCLK = 1
>   - LCD\_CAM\_LCD\_CLKCNT\_N + 1, if LCD\_CAM\_LCD\_CLK\_EQU\_SYSCLK = 0
> - **ahead\_cycle** = **total\_pixels** \* **cycle\_unit**
>
> **ahead\_cycle** indicates the clock cycle before data transmission, which, if less than or equal to 2, will cause an error.

### Workarounds

Users are suggested to do the following:

- When using the RGB format, avoid configuring LCD\_CAM\_LCD\_CLK\_EQU\_SYSCLK as 1.
- When using the I8080 format:

  - try to avoid configuring LCD\_CAM\_LCD\_CLK\_EQU\_SYSCLK as 1.
  - ensure that **ahead\_cycle** is larger than 2 if LCD\_CAM\_LCD\_CLK\_EQU\_SYSCLK has to be set as 1.

This issue has been bypassed through the methods described above in ESP-IDF v4.4.5+, v5.0.3+, v5.1 and above.

### Solution

No fix scheduled.

## [USBOTG-4289] The USB-OTG Download Function Is Unavailable

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32s3/_tags/v0-0.html) [v0.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32s3/_tags/v0-1.html) [v0.2](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32s3/_tags/v0-2.html)

### Description

For ESP32-S3 series chips manufactured before the Date Code 2219 and series of modules and development boards with the PW Number before PW-2022-06-XXXX, the EFUSE\_DIS\_USB\_OTG\_DOWNLOAD\_MODE (BLK0 B19[7]) bit of eFuse is set by default and cannot be modified. Therefore, the USB-OTG Download function is unavailable for these products.

Note

For detailed information about the Date Code and the PW Number, please refer to [Chip Revision Identification](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32s3/01-chip-identification/index.html).

### Workarounds

ESP32-S3 also supports downloading firmware through USB-Serial-JTAG. Please refer to [USB Serial/JTAG Controller Console](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/api-guides/usb-serial-jtag-console.html).

### Solution

This issue has been fixed in some batches of chip revision v0.2.

For ESP32-S3 series chips manufactured on and after the Date Code 2219 and ESP32-S3 series modules and development boards with the PW Number of and after PW-2022-06-XXXX, the bit (BLK0 B19[7]) will not be programmed by default and thus is open for users to program. This will enable the USB-OTG Download function.

For more details and recommendations for users, please refer to [Security Advisory for USB\_OTG & USB\_Serial\_JTAG Download Functions of ESP32-S3 Series Products](https://www.espressif.com/sites/default/files/advisory_downloads/AR2022-004%20Security%20Advisory%20for%20USB_OTG%20%26%20USB_Serial_JTAG%20Download%20Functions%20of%20ESP32-S3%20Series%20Products%20EN.pdf).

## [RMT-176] The Idle State Signal Level Might Run into Error in RMT Continuous TX Mode

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32s3/_tags/v0-0.html) [v0.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32s3/_tags/v0-1.html) [v0.2](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32s3/_tags/v0-2.html)

### Description

In ESP32-S3’s RMT module, if the continuous TX mode is enabled, it is expected that the data transmission stops after the data is sent for RMT\_TX\_LOOP\_NUM\_CHn rounds, and after that, the signal level in idle state should be controlled by the “level” field of the end-marker.

However, in real situation, after the data transmission stops, the channel’s idle state signal level is not controlled by the “level” field of the end-marker, but by the level in the data wrapped back, which is indeterminate.

### Workarounds

Users are suggested to set RMT\_IDLE\_OUT\_EN\_CHn to 1 to only use registers to control the idle level.

This issue has been bypassed since the first ESP-IDF version that supports continuous TX mode (v5.0). In these versions of ESP-IDF, it is configured that the idle level can only be controlled by registers.

### Solution

No fix scheduled.

## [TOUCH-100] The TOUCH\_SCAN\_DONE\_INT Interrupt Raw Data Value Is Undefined

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32s3/_tags/v0-0.html) [v0.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32s3/_tags/v0-1.html) [v0.2](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32s3/_tags/v0-2.html)

### Description

For ESP32-S3’s touch sensor, the raw data value is undefined for the first two TOUCH\_SCAN\_DONE\_INT interrupts.

### Workarounds

Users are suggested to skip the first two TOUCH\_SCAN\_DONE\_INT interrupts, then turn them off and stop using them.

### Solution

No fix scheduled.

## [ADC-183] The Digital Controller (DMA) of SAR ADC2 Cannot Work

Affected revisions: [v0.0](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32s3/_tags/v0-0.html) [v0.1](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32s3/_tags/v0-1.html) [v0.2](https://docs.espressif.com/projects/esp-chip-errata/en/latest/esp32s3/_tags/v0-2.html)

### Description

The Digital Controller of SAR ADC2, i.e., DIG ADC2 controller, may receive a false sampling enable signal. In such a case, the controller will enter an inoperative state.

### Workarounds

It is suggested to use RTC controller to control SAR ADC2.

### Solution

No fix scheduled.
