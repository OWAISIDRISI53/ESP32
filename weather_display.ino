// OpenWeatherMap API details
const String apiKey = "YOUR_API_KEY";    // Replace with your OpenWeatherMap API key
const String city = "London";            // Replace with your city name
const String country = "UK";             // Replace with your country code (ISO 3166-1 alpha-2)
String url = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "," + country + "&appid=" + apiKey + "&units=metric";

#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// OLED display address and dimensions
#define OLED_ADDR 0x3C
Adafruit_SSD1306 display(128, 64, &Wire, -1);

// WiFi credentials
const char *ssid = "name";          // Replace with your WiFi SSID
const char *password = "password";  // Replace with your WiFi Password

// OpenWeatherMap API details
const String apiKey = "YOUR_API_KEY";    // Replace with your OpenWeatherMap API key
const String city = "Mumbai";           // Replace with your city name
const String country = "India";            // Replace with your country code (ISO 3166-1 alpha-2)

// OpenWeatherMap URL
String url = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "," + country + "&appid=" + apiKey + "&units=metric";

// Setup WiFi
void setup() {
  Serial.begin(115200);
  
  // Initialize OLED
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.setTextColor(WHITE);

  // Set a larger font size
  display.setTextSize(2);  // Increase the font size to 2

  // Connect to WiFi
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.println("IP Address: " + WiFi.localIP().toString());
}

// Fetch and display weather data
void fetchWeather() {
  HTTPClient http;
  http.begin(url);
  int httpCode = http.GET();

  if (httpCode > 0) { // Check if the request was successful
    String payload = http.getString(); // Get the response payload (JSON)
    Serial.println(payload);

    // Parse the JSON data
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, payload);
    
    // Extract data from JSON
    String weatherDescription = doc["weather"][0]["description"]; // Weather condition (e.g., clear sky)
    float temperature = doc["main"]["temp"]; // Temperature in Celsius
    float humidity = doc["main"]["humidity"]; // Humidity percentage

    // Display data on OLED
    display.clearDisplay();
    display.setTextSize(2);  // Use a larger font for better readability
    display.setCursor(0, 0);
    
    display.print("Weather: ");
    display.println(weatherDescription);
    display.print("Temp: ");
    display.print(temperature);
    display.println(" C");
    display.print("Humidity: ");
    display.print(humidity);
    display.println(" %");
    display.display();
  } else {
    Serial.println("Error fetching weather data");
  }

  http.end(); // Close the connection
}

void loop() {
  fetchWeather();  // Fetch weather data
  delay(60000);    // Update every 60 seconds (1 minute)
}
