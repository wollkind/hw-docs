<!-- source: https://docs.waveshare.com/ESP32-S3-RLCD-4.2 | fetched: 2026-09-22 -->
# ESP32-S3-RLCD-4.2 | WaveShare Documentation

[![ESP32-S3-RLCD-4.2](img/ESP32-S3-RLCD-4.2-DocHeader-fc9cf7209028a9fad948c565b694bd6b-bbe924.webp)](https://www.waveshare.com/esp32-s3-rlcd-4.2.htm)

This product is a fully reflective screen AIoT development board based on the ESP32-S3, supporting dual-mode communication with Wi-Fi and BLE. It features a 4.2inch fully reflective display (RLCD), low power consumption, display performance close to that of an e-Paper screen, and faster refresh response. It includes onboard audio codec circuitry, dual microphones, speaker, SHTC3 high-precision temperature and humidity sensor, TF card slot, RTC interface, and battery charge and discharge management circuit, etc. It also reserves USB, UART, I2C, and multiple GPIO interfaces for convenient expansion. It supports AI voice, temperature and humidity monitoring, and IoT control, and is suitable for DIY desktop smart ornaments, electronic calendars, AI agents, etc., and can also be used for product prototype development.

Caution

1. When connecting the Type-C cable or inserting/removing an 18650 battery, do not use the screen as a stress point.

   ![Stress point diagram 1](img/ESP32-S3-RLCD-4.2-Attention-1-3f6e997599115e064af3dee7d9aff8-ad7829.webp)

   ![Stress point diagram 2](img/ESP32-S3-RLCD-4.2-Attention-2-b9c8210d81d56983306d4f8e24b00f-16871e.webp)
2. The screen is a precision fragile component. Handle with care during assembly and transport; do not drop or strike it.
3. Damage such as screen cracking or display abnormalities caused by improper handling as described above is not covered by the product warranty.

**If you are looking for:**

- **Coding with AI tools**: Click **Ask AI** and select an AI tool to ask questions about this page, or choose **Copy page** to copy its content and paste it into an AI tool for coding assistance.
- **Schematics, datasheets, and example code**: See [Resources](https://docs.waveshare.com/ESP32-S3-RLCD-4.2/Resources-And-Documents)
- **Arduino development**: See [Working with Arduino](https://docs.waveshare.com/ESP32-S3-RLCD-4.2/Arduino)
- **ESP-IDF development**: See [Working with ESP-IDF](https://docs.waveshare.com/ESP32-S3-RLCD-4.2/ESP-IDF)
- **Troubleshooting**: See [Product FAQ](https://docs.waveshare.com/ESP32-S3-RLCD-4.2/FAQ) or contact [Technical Support](https://docs.waveshare.com/ESP32-S3-RLCD-4.2/Technical-Support)

| SKU | Product |
| --- | --- |
| 33298 | ESP32-S3-RLCD-4.2 |
| 33507 | ESP32-S3-RLCD-4.2-EN |

## Development Board Setup Tutorial

## Features

- Powered by a high-performance Xtensa 32-bit LX7 dual-core processor, with a main frequency of up to 240MHz
- Supports 2.4GHz Wi-Fi and Bluetooth 5 (LE), with built-in antenna
- Built-in 512KB SRAM, 384KB ROM, stacked with 16MB Flash and 8MB PSRAM integrated
- Equipped with a 4.2inch fully reflective screen with a resolution of 300 × 400, featuring characteristics of reflection imaging and no backlight required
- Equipped with a dual-microphone array for audio algorithms such as noise reduction and echo cancellation, suitable for accurate speech recognition and near-field/far-field wake-up applications
- Onboard PCF85063 RTC real-time clock and SHTC3 temperature and humidity sensor enable precise RTC time management and environmental monitoring
- Onboard 18650 lithium battery holder and RTC backup battery holder (requires a rechargeable RTC battery), supporting dual modes of main power supply and independent RTC power backup
- Built-in TF card slot, supports external storage of images or files
- Onboard KEY and BOOT two side buttons with customizable functions, allowing for custom function development
- Reserved 2 × 8 female header interface (2.54mm pitch) for convenient external expansion

## Onboard Resources

![ESP32-S3-RLCD-4.2 Resource Overview](img/ESP32-S3-RLCD-4.2-HW-05480c2dafaac9451f2293edabeaeafb-916550.webp)

1. **ESP32-S3-WROOM-1-N16R8** Wi-Fi and Bluetooth SoC, up to 240MHz operating frequency, stacked with 16MB Flash and 8MB PSRAM
2. **ES7210** ADC chip implements echo cancellation circuit
3. **ES8311** Low-power audio codec chip
4. **BOOT Button** Press and hold the BOOT button to power on again to enter download mode
5. **PWR Button** Long press to power off, single click to power on
6. **KEY Button** Customizable function button
7. **SHTC3 Temperature and Humidity Sensor** Provides ambient temperature and humidity measurement, enabling environmental monitoring function
8. **PCF85063** RTC clock chip, supporting time-keeping functionality
9. **MX1.25 2PIN Speaker Header** Audio signal output, for connecting external speaker
10. **RTC Independent Power Interface** Supports only PH1.0 rechargeable RTC battery
11. **2 × 8PIN 2.54mm Pitch Female Header**
12. **18650 Battery Holder**
13. **Dual Microphone Array Design** Dual microphone array with ES7210 for echo cancellation
14. **CHG Charging Indicator Light** The light turns off when the battery is fully charged
15. **WRN Warning Indicator Light** The light stays on if the battery is reverse-connected
16. **Type-C Interface** Used for program flashing and log printing
17. **TF Card Slot** Supports FAT32-formatted TF card for data expansion

## Interface Introduction

![ESP32-S3-RLCD-4.2 Interface Introduction](img/ESP32-S3-RLCD-4.2-IntfIntro-e8c3e55b4a4e70e8df616f3c7682ae6a-bcc8eb.webp)

## Dimensions

![ESP32-S3-RLCD-4.2 Product Dimensions](img/ESP32-S3-RLCD-4.2-ProductSize-15ee5bf4861e7963ca32409a7fdb4d-4c0725.webp)

## Development Methods

The ESP32-S3-RLCD-4.2 supports two development frameworks: Arduino IDE and ESP-IDF, offering flexibility for developers. You can choose the appropriate development tool based on project requirements and personal preferences.

Arduino generally offers a gentler learning curve and may be more approachable for beginners and hobbyists. ESP-IDF provides advanced tooling and finer control over system behavior, making it better suited to complex projects and applications with demanding performance requirements.

- **Arduino IDE** is a convenient, flexible, and easy-to-use open-source electronics prototyping platform. It requires minimal foundational knowledge, allowing for rapid development after a short learning period. Arduino has a huge global user community, providing a vast amount of open-source code, project examples, and tutorials, as well as a rich library ecosystem that encapsulates complex functions, enabling developers to implement various features rapidly. You can refer to the **[Working with Arduino](https://docs.waveshare.com/ESP32-S3-RLCD-4.2/Arduino)** to complete the initial setup, and the tutorial also provides related example programs for reference.
- **ESP-IDF**, short for Espressif IoT Development Framework, is a professional development framework launched by Espressif Systems for its ESP series of chips. It is based on C language development and includes compilers, debuggers, flashing tools, etc. It supports development via command line or integrated development environments (such as Visual Studio Code with the Espressif IDF plugin), which provides features like code navigation, project management, and debugging. We recommend using VS Code for development. For the specific configuration process, please refer to the **[Working with ESP-IDF](https://docs.waveshare.com/ESP32-S3-RLCD-4.2/ESP-IDF)**. The tutorial also provides relevant example programs for reference.

[Give Feedback](https://docs.google.com/forms/d/e/1FAIpQLSfayJEZ5J-dp-3Wq_dkWsVRhNuQ6C79_GNV62mYuFW8Mj6U8Q/viewform)
