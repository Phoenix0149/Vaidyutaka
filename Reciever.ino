#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <Twilio.h>

// Wi-Fi credentials
const char* ssid = "YOUR_WIFI_SSID";  // Replace with your Wi-Fi name
const char* password = "YOUR_WIFI_PASSWORD";  // Replace with your Wi-Fi password

// Twilio credentials
const char* accountSID = "YOUR_TWILIO_ACCOUNT_SID";  // Replace with your Twilio SID
const char* authToken = "YOUR_TWILIO_AUTH_TOKEN";  // Replace with your Twilio token
const char* fromNumber = "YOUR_TWILIO_PHONE_NUMBER";  // Replace with your Twilio number
const char* toNumber = "YOUR_PHONE_NUMBER";  // Replace with your phone number

// Buzzer and LED pins
const int buzzerPin = 5;
const int ledPin = 6;

// Bend count
int bendCount = 0;

// Twilio client
Twilio twilio(accountSID, authToken);

// Create an HTTP server
AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);

  // Set up buzzer and LED
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }
  Serial.println("Connected to Wi-Fi");
  Serial.println("IP Address: " + WiFi.localIP().toString());

  // Set up HTTP server
  server.on("/count", HTTP_POST, [](AsyncWebServerRequest *request) {
    if (request->hasParam("count", true)) {
      String count = request->getParam("count", true)->value();
      bendCount = count.toInt();
      Serial.println("Received count: " + count);

      // Perform actions based on the count
      if (bendCount >= 5) {
        // Turn on buzzer and LED
        digitalWrite(buzzerPin, HIGH);
        digitalWrite(ledPin, HIGH);
      } else {
        // Turn off buzzer and LED
        digitalWrite(buzzerPin, LOW);
        digitalWrite(ledPin, LOW);
      }

      if (bendCount >= 10) {
        // Send SMS using Twilio
        String message = "Emergency! Flex sensor bent 10 times.";
        twilio.sendSMS(fromNumber, toNumber, message);
        Serial.println("SMS sent via Twilio.");
      }

      request->send(200, "text/plain", "Count received");
    } else {
      request->send(400, "text/plain", "Bad request");
    }
  });

  server.begin();  // Start the server
}

void loop() {
  // Nothing to do here
}//receiver