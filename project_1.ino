#include <WiFi.h>
#include <UniversalTelegramBot.h>
#include <WiFiClientSecure.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <HTTPClient.h>

// Replace with your WiFi credentials
const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";
const char* apiKey = "Your_API_KEY";
const char* botToken = "Your_BOT_TOKEN";
const char* city = "Mumbai";

WiFiClientSecure client;
UniversalTelegramBot bot(botToken, client);

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 19800, 60000); // For IST (GMT+5:30)

Adafruit_SSD1306 display(128, 64, &Wire, -1);

int counter = 0;
unsigned long lastTime = 0;
const long interval = 1000; // Bot check interval (1 second)

String getFormattedTime() {
  timeClient.update();
  return timeClient.getFormattedTime();
}


// Weather placeholder function
String getWeather() {
  if (WiFi.status() != WL_CONNECTED) {
    return "WiFi not connected!";
  }

  HTTPClient http;
  String url = String("http://api.openweathermap.org/data/2.5/weather?q=") + city + "&appid=" + apiKey + "&units=metric";
  http.begin(url);
  
  int httpResponseCode = http.GET();
  if (httpResponseCode > 0) {
    String payload = http.getString();
    http.end();
    
    // Parse JSON payload (basic example, better to use ArduinoJson library)
    int tempIndex = payload.indexOf("\"temp\":");
    int humidityIndex = payload.indexOf("\"humidity\":");
    if (tempIndex != -1 && humidityIndex != -1) {
      String temp = payload.substring(tempIndex + 7, payload.indexOf(",", tempIndex));
      String humidity = payload.substring(humidityIndex + 10, payload.indexOf("}", humidityIndex));
      return "Temperature: " + temp + "°C\nHumidity: " + humidity + "%";
    }
  } else {
    http.end();
    return "Error fetching weather data!";
  }

  return "Failed to parse weather data!";
}


// Quote placeholder function
String getRandomQuote() {
  if (WiFi.status() != WL_CONNECTED) {
    return "WiFi not connected!";
  }

  HTTPClient http;
  http.begin("https://api.quotable.io/random"); // Quotable API for random quotes
  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    String payload = http.getString();
    http.end();

    // Parse JSON payload (basic parsing without libraries)
    int contentIndex = payload.indexOf("\"content\":\"");
    int authorIndex = payload.indexOf("\"author\":\"");
    if (contentIndex != -1 && authorIndex != -1) {
      String content = payload.substring(contentIndex + 11, payload.indexOf("\"", contentIndex + 11));
      String author = payload.substring(authorIndex + 10, payload.indexOf("\"", authorIndex + 10));
      return "\"" + content + "\"\n- " + author;
    }
  } else {
    http.end();
    return "Error fetching quote!";
  }

  return "Failed to parse quote data!";
}


String getRandomJoke() {
  if (WiFi.status() != WL_CONNECTED) {
    return "WiFi not connected!";
  }

  HTTPClient http;
  http.begin("https://official-joke-api.appspot.com/jokes/random"); // Joke API
  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    String payload = http.getString();
    http.end();

    // Parse JSON payload (basic parsing without libraries)
    int setupIndex = payload.indexOf("\"setup\":\"");
    int punchlineIndex = payload.indexOf("\"punchline\":\"");
    if (setupIndex != -1 && punchlineIndex != -1) {
      String setup = payload.substring(setupIndex + 9, payload.indexOf("\"", setupIndex + 9));
      String punchline = payload.substring(punchlineIndex + 12, payload.indexOf("\"", punchlineIndex + 12));
      return setup + "\n" + punchline;
    }
  } else {
    http.end();
    return "Error fetching joke!";
  }

  return "Failed to parse joke data!";
}


// Handle incoming messages
void handleMessage(int messageIndex) {
  String chat_id = bot.messages[messageIndex].chat_id;
  String text = bot.messages[messageIndex].text;

  if (text == "/start") {
    bot.sendMessage(chat_id, "Welcome to ESP32 Telegram Bot!\nCommands:\n/weather\n/time\n/counter_inc\n/counter_dec\n/quote", "");
  } else if (text == "/weather") {
    String weather = getWeather();
    bot.sendMessage(chat_id, "Weather:\n" + weather, "");
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.println("Weather:");
    display.println(weather);
    display.display();
  } 
  
  else if (text == "/joke") {  // Handling /joke command
    String joke = getRandomJoke();
    bot.sendMessage(chat_id, "Joke:\n" + joke, "");
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.println("Joke:");
    display.println(joke);
    display.display();
  }
  
  else if (text == "/time") {
    String timeStr = "Time: " + getFormattedTime();
    bot.sendMessage(chat_id, timeStr, "");
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.println(timeStr);
    display.display();
  } else if (text == "/counter_inc") {
    counter++;
    bot.sendMessage(chat_id, "Counter: " + String(counter), "");
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.println("Counter:");
    display.println(counter);
    display.display();
  } else if (text == "/counter_dec") {
    counter--;
    bot.sendMessage(chat_id, "Counter: " + String(counter), "");
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.println("Counter:");
    display.println(counter);
    display.display();
  } else if (text == "/quote") {
    String quote = getRandomQuote();
    bot.sendMessage(chat_id, "Quote:\n" + quote, "");
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.println("Quote:");
    display.println(quote);
    display.display();
  } else {
    bot.sendMessage(chat_id, "Unknown command. Type /start to see available commands.", "");
  }
}

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize NTP client
  timeClient.begin();

  // Set up Telegram client
  client.setInsecure(); // Skip SSL certificate validation

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED initialization failed");
    while (true);
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  // Initial message
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("Telegram Bot Ready");
  display.display();
}

void loop() {
  if (millis() - lastTime > interval) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while (numNewMessages) {
      handleMessage(numNewMessages - 1);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTime = millis();
  }
}
