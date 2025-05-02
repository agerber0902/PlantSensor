#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

//-- Define pins

// Pin that controls the speed of the fan motor
#define FAN_POTENTIOMETER_PIN 5
// Pin that controls the speed of the water pump motor
#define WATER_PUMP_POTENTIOMETER_PIN 6
// Pin that controls the fan motor (BI of TA6585 driver)
#define FAN_PIN 10
// Pin that controls the water pump motor (FI of TA6585 driver)
#define WATER_PUMP_PIN 9

//-- Define PWM Values

#define FAN_PWN_CHANNEL 0
#define FAN_PWM_FREQUENCY 1000
#define FAN_PWM_RESOLUTION 8

#define WATER_PUMP_PWM_CHANNEL 1
#define WATER_PUMP_PWM_FREQUENCY 1000
#define WATER_PUMP_PWM_RESOLUTION 8

//-- End of PWM Values

//-- End of Define pins

void PWM_Setup();

void setup()
{
  Serial.begin(921600);

  // Configure Pin Modes

  pinMode(FAN_POTENTIOMETER_PIN, INPUT);
  pinMode(WATER_PUMP_POTENTIOMETER_PIN, INPUT);

  // End of Configure Pin Modes

  // Setup PWM for fan and water pump
  PWM_Setup();

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

// Setup functions that sets the pwm values for the fan and water pump
void PWM_Setup()
{
  // Setup PWM for Fan
  ledcSetup(FAN_PWN_CHANNEL, FAN_PWM_FREQUENCY, FAN_PWM_RESOLUTION);
  // Attach PWM output to the fam pin
  ledcAttachPin(FAN_PIN, FAN_PWN_CHANNEL);

  // Setup PWN for Water Pump
  ledcSetup(WATER_PUMP_PWM_CHANNEL, WATER_PUMP_PWM_FREQUENCY, WATER_PUMP_PWM_RESOLUTION);
  // Attach PWM output to the water pump pin
  ledcAttachPin(WATER_PUMP_PIN, WATER_PUMP_PWM_CHANNEL);

  return;
}
