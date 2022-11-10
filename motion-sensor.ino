#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

int sensor = 13;
const char* ssid = "REPLACE_WITH_YOUR_SSID";
const char* password = "REPLACE_WITH_YOUR_PASSWORD";
const char* serverName = "http://localhost:8080/echo";

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  pinMode(sensor, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  long state = digitalRead(sensor);
  if (state == HIGH) {
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("Motion detected!");
    delay(3000);
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("No Motion detected!");
    delay(1000);
  }
}