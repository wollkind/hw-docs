<!-- source: https://docs.waveshare.com/ESP32-S3-RGB-Matrix/FAQ | fetched: 2026-09-21 -->
# ESP32-S3-RGB-Matrix FAQ | WaveShare Documentation

Q: Why is the displayed image misaligned or incomplete?

- The driver board is configured for 64x64 resolution by default. If you need a different resolution, modify the configuration option and use the second example to display content.

 Q: The board keeps resetting after program upload?

- Check whether the configuration options are mismatched, and verify that the additional screen power supply is connected.

 Q: After downloading a program to the module, when trying to download again, sometimes it fails to connect to the serial port or the flashing fails?

- You can hold down the BOOT button, press RESET, then release RESET, and finally release the BOOT button. This will put the module into download mode, which resolves most programming issues.

 Q: After powering on, the detected USB port keeps resetting and restarting?

- Check the logs to determine whether the reset is caused by insufficient power supply. If so, verify that the USB port's supply voltage is above 5V. In general, the USB supply voltage should be above 4.9V. If it is below 4.9V, insufficient power may cause the USB port to disconnect. In that case, use a USB port that provides adequate voltage. If the issue is program-related, check whether the code has been modified or configured incorrectly. For other issues, inspect the other hardware.

 Q: Q: When performing JTAG debugging, the debug page never appears?

- Close the OpenOCD instance below, then restart OpenOCD.

[Give Feedback](https://docs.google.com/forms/d/e/1FAIpQLSfayJEZ5J-dp-3Wq_dkWsVRhNuQ6C79_GNV62mYuFW8Mj6U8Q/viewform)
