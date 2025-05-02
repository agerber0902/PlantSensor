#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>


void setup() {
  Serial.begin(921600);

  // Initialize ESP-NOW
  WiFi.mode(WIFI_STA);
  esp_now_init();
}

void loop() {
}
