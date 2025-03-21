#include <WiFi.h>
#include <HTTPClient.h>

// Wi-Fi credentials
const char* ssid = "YOUR_WIFI_SSID";  // Replace with your Wi-Fi name
const char* password = "YOUR_WIFI_PASSWORD";  // Replace with your Wi-Fi password

// Receiver ESP's IP address and endpoint
const char* receiverURL = "http://RECEIVER_ESP_IP/count";  // Replace with Receiver ESP's IP

// Flex sensor pin
const int flexPin = A0;

// Bend count
int bendCount = 0;

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }
  Serial.println("Connected to Wi-Fi");
}

void loop() {
  // Read flex sensor value
  int flexValue = analogRead(flexPin);

  // Check if flex sensor is bent (adjust threshold as needed)
  if (flexValue > 2000) {  // Example threshold
    bendCount++;
    Serial.print("Bend Count: ");
    Serial.println(bendCount);

    // Send bend count to Receiver ESP
    sendBendCount(bendCount);

    // Wait for the flex sensor to return to normal
    delay(1000);  // Debounce delay
  }
}

void sendBendCount(int count) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(receiverURL);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Send bend count as a POST request
    String postData = "count=" + String(count);
    int httpResponseCode = http.POST(postData);

    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Error sending HTTP request: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  }
} //sender