#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// OLED display settings
#define OLED_ADDR 0x3C
Adafruit_SSD1306 display(128, 64, &Wire, -1);

// WiFi credentials
const char *ssid = "Your_SSID";          // Replace with your WiFi SSID
const char *password = "Your_PASSWORD";  // Replace with your WiFi password

// NTP settings
WiFiUDP udp;
NTPClient timeClient(udp, "pool.ntp.org", 0, 60000); // Get time from NTP server every 60 seconds

void setup() {
  Serial.begin(115200);

  // Initialize OLED display
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.setTextColor(WHITE);

  // Set larger font for better readability
  display.setTextSize(2);

  // Connect to WiFi
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.println("IP Address: " + WiFi.localIP().toString());

  // Initialize NTP Client
  timeClient.begin();
  timeClient.update();
}

void loop() {
  // Fetch time from NTP
  timeClient.update();
  String formattedTime = timeClient.getFormattedTime();

  // Display time on OLED
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Time: ");
  display.setCursor(0, 30);
  display.setTextSize(3);  // Bigger text for the time
  display.println(formattedTime);
  display.display();

  delay(1000); // 1 second update rate
}
