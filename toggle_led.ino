#define LED_PIN 2          // Use the built-in LED (GPIO 2 for most ESP32 boards)
#define BUTTON_PIN 0       // GPIO Pin for the built-in button (GPIO 0 for most ESP32 boards)

void setup() {
  pinMode(LED_PIN, OUTPUT);     // Set the LED pin as output
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Set the built-in button pin as input with internal pull-up resistor
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);  // Read the state of the built-in button

  if (buttonState == LOW) {  // Button is pressed (since we use INPUT_PULLUP)
    digitalWrite(LED_PIN, HIGH);  // Turn the LED on
  } else {
    digitalWrite(LED_PIN, LOW);   // Turn the LED off
  }
}
