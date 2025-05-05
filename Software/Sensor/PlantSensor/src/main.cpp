#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <DHT.h>

//-- Define pins

// Define the pin for the DHT sensor
#define TEMPERATURE_SENSOR_INPUT_PIN 4
// Define the pin for the moisture sensor
#define MOISTURE_SENSOR_INPUT_PIN 2
// Define the pin for the light sensor
#define UV_SENSOR_INPUT_PIN 3
#define DHTTYPE DHT11   
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
DHT dht = DHT(TEMPERATURE_SENSOR_INPUT_PIN, DHT11);

//-- Define Variables

// Message to be sent
send_message sensorMessage;
// Peer Mac address
uint8_t peer_mac_addr[] = {0x98, 0x3D, 0xAE, 0xAA, 0xCB, 0x3C};

//-- End of Define Variables

void setup() {

  // Setup serial communication
  Serial.begin(921600);
  analogSetAttenuation(ADC_11db); // or ADC_0db for minimal gain
  analogReadResolution(12);

  // Configure pin modes
  pinMode(MOISTURE_SENSOR_INPUT_PIN, INPUT);
  pinMode(UV_SENSOR_INPUT_PIN, INPUT);
  pinMode(TEMPERATURE_SENSOR_INPUT_PIN, INPUT);

  // Initialize the DHT sensor
  dht.begin();
  
  // Setup ESP NOW
  WiFi.mode(WIFI_STA);
  esp_now_init();

  // Set up callback
  esp_now_register_send_cb([](const uint8_t* mac, esp_now_send_status_t status) {

    Serial.print("Send Status: ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
  
  });

}

void loop() {

  // Read dht sensor values
  sensorMessage.temperature = dht.readTemperature();
  sensorMessage.humidity = dht.readHumidity();
  Serial.printf("Temperature Reading from DHT sensor: %f\n", sensorMessage.temperature);
  Serial.printf("Humidity Reading from DHT sensor: %f\n", sensorMessage.humidity);

  // Read uv value
  sensorMessage.uv = analogRead(UV_SENSOR_INPUT_PIN);
  Serial.printf("UV Reading from photo resistor: %f\n", sensorMessage.uv);
  
  // Read moisture value
  sensorMessage.moisture = analogRead(MOISTURE_SENSOR_INPUT_PIN);
  Serial.printf("Moisture Reading from input pin: %f\n", sensorMessage.moisture);

  delay(1000); // Wait for 5 seconds before sending the next message
}
