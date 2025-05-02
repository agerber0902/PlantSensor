#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

void setup()
{
  Serial.begin(921600);

  // Initialize ESP-NOW
  WiFi.mode(WIFI_STA);
  esp_now_init();

  // Callback function for receiving data
  esp_now_register_recv_cb([](const uint8_t *mac, const uint8_t *data, int len)
  {
    
  });
}

void loop()
{
}
