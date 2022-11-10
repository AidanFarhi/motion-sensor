#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "secrets.h"

int sensor = 13;
const char* ssid = SSID;
const char* password = PASSWORD;
const char* get_endpoint = "http://192.168.1.157:8080";
const char* post_endpoint = "http://192.168.1.157:8080/echo";

void make_post_request() {
  WiFiClient client;
  HTTPClient http;
  http.begin(client, post_endpoint);
  http.addHeader("Content-Type", "application/json");
  int httpResponseCode = http.POST("{\"msg\":\"motion detected!\"}");
  Serial.print("HTTP Response code: ");
  Serial.println(httpResponseCode);
  http.end();
}

void make_get_request() {
  WiFiClient client;
  HTTPClient http;
  http.begin(client, get_endpoint);
  int httpResponseCode = http.GET();
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    Serial.println(payload);
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
}

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  pinMode(sensor, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  long state = digitalRead(sensor);
  if (state == HIGH) {
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("Motion detected!");
    make_post_request();
    delay(3000);
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("No Motion detected!");
    delay(1000);
  }
}
