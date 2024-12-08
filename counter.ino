#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED display settings
#define OLED_ADDR 0x3C
Adafruit_SSD1306 display(128, 64, &Wire, -1);

// Button pins
const int incrementButton = 15;  // GPIO Pin for increment button
const int decrementButton = 16;  // GPIO Pin for decrement button
int counter = 0;  // Initialize counter

void setup() {
  Serial.begin(115200);

  // Initialize OLED display
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.setTextColor(WHITE);

  // Set larger font for better readability
  display.setTextSize(2);

  // Setup button pins
  pinMode(incrementButton, INPUT_PULLUP);
  pinMode(decrementButton, INPUT_PULLUP);
}

void loop() {
  // Read button states and update the counter accordingly
  if (digitalRead(incrementButton) == LOW) {
    counter++;
    delay(200);  // Debounce delay
  }
  if (digitalRead(decrementButton) == LOW) {
    counter--;
    delay(200);  // Debounce delay
  }

  // Display the counter on OLED
  display.clearDisplay();
  display.setCursor(0, 30);
  display.print("Counter: ");
  display.println(counter);
  display.display();

  delay(100); // Small delay for responsiveness
}
