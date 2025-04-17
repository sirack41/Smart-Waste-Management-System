// For ESP8266 with HC-SR04
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
const char* serverURL = "http://your-server-address/upload"; // endpoint to receive data

#define TRIG_PIN D1
#define ECHO_PIN D2

long duration;
float distance;

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
}

void loop() {
  // Measure distance
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2; // in cm

  Serial.print("Distance: ");
  Serial.println(distance);

  // Send to server if connected
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverURL);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    String postData = "bin_id=1&level=" + String(distance);
    int httpResponseCode = http.POST(postData);

    Serial.println(httpResponseCode);
    http.end();
  }

  delay(30000); // Send every 30 seconds
}
