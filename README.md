# ESP32 Projects Collection

This repository contains several small projects for the **ESP32** that demonstrate various functionalities such as controlling an LED, reading real-time weather, displaying the current time, using a button to control a counter, and utilizing the built-in button on the ESP32.

## Projects Overview:

1. **LED Blink Control**
2. **Real-time Time Display**
3. **Weather Display**
4. **Counter with Button Increment and Decrement**
5. **Built-In Button to Control LED**

---

## Project 1: LED Blink Control

This project uses the ESP32 to blink the built-in LED at regular intervals.

### Features:
- Blinks the built-in LED on the ESP32.
- Simple delay-based blink pattern.

### Instructions:
1. Open the `blink_led.ino` file in the Arduino IDE.
2. Upload the code to the ESP32.
3. The LED will blink every second.

---

## Project 2: Real-Time Time Display

This project uses the **NTP (Network Time Protocol)** to display the current time on an **OLED display** connected to the ESP32.

### Features:
- Displays the current time from an NTP server on an OLED screen.
- Automatically adjusts for time zone (you can set your time zone offset).

### Instructions:
1. Open the `time_display.ino` file in the Arduino IDE.
2. Update the Wi-Fi credentials.
3. Upload the code to the ESP32.
4. The OLED will display the current time.

---

## Project 3: Weather Display

This project fetches weather data from a **ThingSpeak** channel and displays it on the OLED screen.

### Features:
- Fetches temperature and humidity data from a ThingSpeak channel.
- Displays the current weather data on an OLED screen.

### Instructions:
1. Open the `weather_display.ino` file in the Arduino IDE.
2. Update the Wi-Fi credentials and ThingSpeak API keys.
3. Upload the code to the ESP32.
4. The OLED will display the weather data (temperature and humidity).

---

## Project 4: Counter with Button Increment and Decrement

This project increments and decrements a counter based on button presses. **Button 1** increments the counter, and **Button 2** decrements the counter.

### Features:
- Increments and decrements a counter value with button presses.
- Displays the current counter value on the Serial Monitor.

### Instructions:
1. Open the `counter_button.ino` file in the Arduino IDE.
2. Connect two buttons to the specified pins for increment and decrement.
3. Upload the code to the ESP32.
4. Monitor the serial output to see the updated counter value.

---

## Project 5: Built-In Button to Control LED

This project uses the **built-in button (GPIO 0)** on the ESP32 to turn an LED on and off. The LED will turn on when the button is pressed.

### Features:
- Uses the built-in button to control the state of the built-in LED.
- Simple on/off control based on button press.

### Instructions:
1. Open the `built_in_button_led.ino` file in the Arduino IDE.
2. Upload the code to the ESP32.
3. Press the built-in button to turn the LED on and off.

---

## How to Run Each Project

1. **Clone or Download** the repository.
2. **Open** each `.ino` file in the Arduino IDE or PlatformIO.
3. **Select the correct board** and port in the IDE (e.g., ESP32 Dev Module).
4. **Upload** the code to the ESP32.

## Required Libraries:

You may need to install the following libraries via the Arduino Library Manager or PlatformIO:

- **Adafruit SSD1306** - For OLED displays
- **Adafruit GFX** - Graphics support for the OLED
- **WiFi** - For connecting to Wi-Fi
- **NTPClient** - For getting the current time from the internet
- **ThingSpeak** - For fetching data from ThingSpeak (weather)

---

## Conclusion

This repository contains multiple small but useful projects that utilize different features of the **ESP32**. You can use these as starting points to build more complex applications. Enjoy experimenting with these projects!

If you have any issues or questions, feel free to open an issue in this repository or reach out.

