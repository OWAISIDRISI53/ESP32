#define LED_PIN 2  // Use the built-in LED (GPIO 2 for most ESP32 boards)

void setup() {
  pinMode(LED_PIN, OUTPUT);  // Set the LED pin as output
}

void loop() {
  digitalWrite(LED_PIN, HIGH);  // Turn the LED on
  delay(1000);                   // Wait for 1 second
  digitalWrite(LED_PIN, LOW);   // Turn the LED off
  delay(1000);                   // Wait for 1 second
}
