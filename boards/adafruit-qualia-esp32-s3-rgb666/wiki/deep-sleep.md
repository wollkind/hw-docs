<!-- source: https://learn.adafruit.com/adafruit-qualia-esp32-s3-for-rgb666-displays/deep-sleep | fetched: 2026-09-23 -->
# Deep Sleep | Adafruit Qualia ESP32-S3 for RGB-666 Displays | Adafruit Learning System

33

Intermediate

Product guide

## Deep Sleep

The Qualia ESP32-S3 can be put into deep sleep to dramatically reduce power consumption for battery-powered projects. When the display, backlight, and ESP32-S3 core are all properly shut down in the correct order, the board draws less than 1mA from a battery or dumb USB power supply.

**Note:** Deep sleep current cannot be measured accurately over a USB-C connection to a computer with a USB host running. The USB stack and serial REPL add significant quiescent current. Use a battery or a basic “dumb” USB power supply (with no data lines active) when measuring sleep current.

## Order of Operations

Getting the backlight to actually turn off during sleep requires a specific sequence. The most common issue — the backlight staying on or turning back on when the sleep-in command is sent — is caused by the TCA9534 I/O expander having the backlight pin configured as an **input** rather than an **output**. You must explicitly reconfigure it as an output and drive it low as part of the shutdown sequence.

The correct order is:

1. Send the **ST7701S Sleep In** command (`0x10`) via `ioexpander_send_init_sequence`
2. Call `displayio.release_displays()` to stop the dot clock signals from the ESP32-S3
3. Reconfigure the **backlight pin as an OUTPUT** on the TCA9534 expander, then drive all outputs low
4. Enter **ESP32-S3 deep sleep** with a pin alarm

Reversing steps 2 and 3, or skipping the output-register reconfiguration, will result in the backlight remaining on and current draw staying around 170–200mA.

[![](img/circuitpython_IMG_0162_(1)-7857fa.jpeg)](https://learn.adafruit.com/assets/143447) 

[Download File](https://learn.adafruit.com/elements/3217870/download)

[Copy Code](https://learn.adafruit.com/adafruit-qualia-esp32-s3-for-rgb666-displays/deep-sleep)

```
import time
import alarm
import board
import displayio
import dotclockframebuffer
from adafruit_qualia.graphics import Graphics, Displays

# --- Display init ---
graphics = Graphics(Displays.SQUARE40_480X480, default_bg=None, auto_refresh=False)
# graphics = Graphics(Displays.SQUARE40, default_bg=None, auto_refresh=False)        # 4.0" 720x720 Square (TL040HDS20)
# graphics = Graphics(Displays.SQUARE34, default_bg=None, auto_refresh=False)        # 3.4" 480x480 Square (TL034WVS05)
# graphics = Graphics(Displays.ROUND21, default_bg=None, auto_refresh=False)         # 2.1" 480x480 Round  (TL021WVC02)
# graphics = Graphics(Displays.ROUND28, default_bg=None, auto_refresh=False)         # 2.8" Round          (TL028WVC01)
# graphics = Graphics(Displays.ROUND40, default_bg=None, auto_refresh=False)         # 4.0" 720x720 Round  (HD40015C40)
# graphics = Graphics(Displays.BAR320X820, default_bg=None, auto_refresh=False)      # 3.2" 320x820 Bar    (TL032FWV01)
# graphics = Graphics(Displays.BAR240X960, default_bg=None, auto_refresh=False)      # 3.7" 240x960 Bar    (HD371001C)
# graphics = Graphics(Displays.BAR320X960, default_bg=None, auto_refresh=False)      # 4.58" 320x960 Bar   (HD458002C40)

# Show display is alive for 3 seconds
graphics.display.auto_refresh = True
time.sleep(3)
graphics.display.auto_refresh = False

# --- Sleep sequence ---
i2c = graphics.i2c_bus

# Step 1: Send ST7701S Sleep In command
sleep_in = bytes([0x01, 0x10])
dotclockframebuffer.ioexpander_send_init_sequence(
    i2c, sleep_in, **dict(board.TFT_IO_EXPANDER)
)

# Step 2: Release all display resources (stops dotclock signals)
displayio.release_displays()

# Step 3: Reconfigure backlight pin as OUTPUT on TCA9534, then drive all outputs LOW
while not i2c.try_lock():
    pass
buf = bytearray(1)
i2c.writeto_then_readfrom(0x3F, bytes([0x03]), buf)
i2c.writeto(0x3F, bytes([0x03, buf[0] & ~(1 << board.BACKLIGHT)]))
i2c.writeto(0x3F, bytes([0x01, 0x00]))
i2c.unlock()

# Small delay to let panel settle
time.sleep(0.05)

# --- ESP32-S3 deep sleep ---
pin_alarm = alarm.pin.PinAlarm(pin=board.A0, value=False, pull=True)
print("Entering deep sleep...")
alarm.exit_and_deep_sleep_until_alarms(pin_alarm)
```

```
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
41
42
43
44
45
46
47
48
49
50
51
52
```

```python
import time
import alarm
import board
import displayio
import dotclockframebuffer
from adafruit_qualia.graphics import Graphics, Displays

# --- Display init ---
graphics = Graphics(Displays.SQUARE40_480X480, default_bg=None, auto_refresh=False)
# graphics = Graphics(Displays.SQUARE40, default_bg=None, auto_refresh=False)        # 4.0" 720x720 Square (TL040HDS20)
# graphics = Graphics(Displays.SQUARE34, default_bg=None, auto_refresh=False)        # 3.4" 480x480 Square (TL034WVS05)
# graphics = Graphics(Displays.ROUND21, default_bg=None, auto_refresh=False)         # 2.1" 480x480 Round  (TL021WVC02)
# graphics = Graphics(Displays.ROUND28, default_bg=None, auto_refresh=False)         # 2.8" Round          (TL028WVC01)
# graphics = Graphics(Displays.ROUND40, default_bg=None, auto_refresh=False)         # 4.0" 720x720 Round  (HD40015C40)
# graphics = Graphics(Displays.BAR320X820, default_bg=None, auto_refresh=False)      # 3.2" 320x820 Bar    (TL032FWV01)
# graphics = Graphics(Displays.BAR240X960, default_bg=None, auto_refresh=False)      # 3.7" 240x960 Bar    (HD371001C)
# graphics = Graphics(Displays.BAR320X960, default_bg=None, auto_refresh=False)      # 4.58" 320x960 Bar   (HD458002C40)

# Show display is alive for 3 seconds
graphics.display.auto_refresh = True
time.sleep(3)
graphics.display.auto_refresh = False

# --- Sleep sequence ---
i2c = graphics.i2c_bus

# Step 1: Send ST7701S Sleep In command
sleep_in = bytes([0x01, 0x10])
dotclockframebuffer.ioexpander_send_init_sequence(
    i2c, sleep_in, **dict(board.TFT_IO_EXPANDER)
)

# Step 2: Release all display resources (stops dotclock signals)
displayio.release_displays()

# Step 3: Reconfigure backlight pin as OUTPUT on TCA9534, then drive all outputs LOW
while not i2c.try_lock():
    pass
buf = bytearray(1)
i2c.writeto_then_readfrom(0x3F, bytes([0x03]), buf)
i2c.writeto(0x3F, bytes([0x03, buf[0] & ~(1 << board.BACKLIGHT)]))
i2c.writeto(0x3F, bytes([0x01, 0x00]))
i2c.unlock()

# Small delay to let panel settle
time.sleep(0.05)

# --- ESP32-S3 deep sleep ---
pin_alarm = alarm.pin.PinAlarm(pin=board.A0, value=False, pull=True)
print("Entering deep sleep...")
alarm.exit_and_deep_sleep_until_alarms(pin_alarm)
```

Show all 52 lines

## Expected Current Draw

| State | Current |
| --- | --- |
|  |  |
| --- | --- |
| Normal operation (backlight on) | ~170mA |
| Backlight off only | ~8mA |
| Full deep sleep (display + backlight off, ESP32-S3 sleeping) | <1mA |

Measurements should be taken from a battery or dumb USB supply — not from a computer USB-C connection — to get accurate readings.

Page last edited April 05, 2026

Text editor powered by [tinymce](https://www.tiny.cloud/).

[Backlight Settings](https://learn.adafruit.com/adafruit-qualia-esp32-s3-for-rgb666-displays/backlight-settings) [CircuitPython Display Setup](https://learn.adafruit.com/adafruit-qualia-esp32-s3-for-rgb666-displays/circuitpython-display-setup)
