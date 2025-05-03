#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <DHT.h>

//-- Define pins

// Define the pin for the DHT sensor
#define TEMPERATURE_SENSOR_INPUT_PIN 2
// Define the pin for the moisture sensor
#define MOISTURE_SENSOR_INPUT_PIN 0
// Define the pin for the light sensor
#define UV_SENSOR_INPUT_PIN 1

//-- End of Define pins

//-- Define the message we are sending
typedef struct send_message
{
  float temperature;
  float humidity;
  float moisture;
  float uv;
} send_message;
//-- End of Define the message we are sending

// Define and configure the DHT sensor
DHT dhtTemperatureSensor(TEMPERATURE_SENSOR_INPUT_PIN, DHT11);

//-- Define Variables

// Message to be sent
send_message sensorMessage;
// Peer Mac address
uint8_t peer_mac_addr[] = {0x98, 0x3D, 0xAE, 0xAA, 0xCB, 0x3C};

//-- End of Define Variables

void setup() {

  // Setup serial communication
  Serial.begin(921600);

  // Configure pin modes
  pinMode(MOISTURE_SENSOR_INPUT_PIN, INPUT);
  pinMode(UV_SENSOR_INPUT_PIN, INPUT);
  pinMode(TEMPERATURE_SENSOR_INPUT_PIN, INPUT);

  // Initialize the DHT sensor
  dhtTemperatureSensor.begin();
  
  // Setup ESP NOW
  WiFi.mode(WIFI_STA);
  esp_now_init();

  

}

void loop() {

}
