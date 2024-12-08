# ESP32

# ESP32 Weather and Counter Display

This project displays real-time weather information, a clock, and a counter on an OLED screen using an ESP32.

## Features:
- Fetch weather data from OpenWeatherMap API and display it on an OLED screen.
- Show real-time clock using NTP (Network Time Protocol).
- Counter that can be incremented and decremented using buttons.

## Components:
- **ESP32**
- **OLED Display (SSD1306)**
- **Buttons for counter increment/decrement**
- **Wi-Fi connection**
- **OpenWeatherMap API Key**

## Setup:
1. Clone this repository.
2. Install the necessary libraries:
   - Adafruit SSD1306
   - Adafruit GFX
   - HTTPClient
   - ArduinoJson
   - NTPClient
3. Enter your Wi-Fi credentials, OpenWeatherMap API key, and city information in the `main.ino` file.
4. Upload the code to your ESP32 board.
5. The ESP32 will display the weather, time, and counter on the OLED screen.

## Libraries:
- Adafruit SSD1306: https://github.com/adafruit/Adafruit_SSD1306
- Adafruit GFX: https://github.com/adafruit/Adafruit-GFX-Library
- ArduinoJson: https://github.com/bblanchon/ArduinoJson
- NTPClient: https://github.com/arduino-libraries/NTPClient
