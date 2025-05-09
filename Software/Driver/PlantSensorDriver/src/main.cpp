#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include "RgbControl/RgbControl.h"
#include "TemperatureControl/TemperatureControl.h"
#include "MoistureControl/MoistureControl.h"

//-- Define pins

// Pin that controls the speed of the fan motor
#define FAN_POTENTIOMETER_PIN 5
// Pin that controls the speed of the water pump motor
#define WATER_PUMP_POTENTIOMETER_PIN 7
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

#define MOISTURE_ALERT_COLOR {0, 0, 255} // Blue
#define TEMPERATURE_ALERT_COLOR {255, 0, 0} // Red

//-- End of PWM Values

//-- End of Define pins

//-- Define Control Class
typedef struct control 
{
  // Define the led control class
  RgbControl rgbControl = RgbControl(4, 3, 2, 3, 4, 5); // Red Pin, Green Pin, Blue Pin, Red Channel, Green Channel, Blue Channel
  // Define the temperature control class
  TemperatureControl temperatureControl = TemperatureControl(80.0); //Alert Threshold
  // Define the moisture control class
  MoistureControl moistureControl = MoistureControl(3000); //Alert Threshold
} control;
//-- End of Define Control Class

//-- Define the message we are expecting to receive
typedef struct rcvd_message
{
  float temperature;
  float humidity;
  float moisture;
  float uv;
} rcvd_message;
//-- End of Define the message we are expecting to receive

//-- Define Variables
// Control class instance
control driverControl;
// Message from sensor
rcvd_message sensorMessage;

// Alert flags for temperature and moisture
bool temperatureAlert = false;
bool moistureAlert = false;
//-- End of Define Variables

//-- Define Functions
void PWM_Setup();
void control_Setup();
void handleTemperatureInput();
void handleMoistureInput();
void handleAlerts();
//-- End of Define Functions

void setup()
{
  Serial.begin(921600);
  Serial.println("Serial communication initialized");
  
  // Configure Pin Modes

  pinMode(FAN_POTENTIOMETER_PIN, INPUT);
  pinMode(WATER_PUMP_POTENTIOMETER_PIN, INPUT);

  // End of Configure Pin Modes

  // Setup PWM for fan and water pump
  PWM_Setup();

  // Setup the controls
  control_Setup();

  // Initialize ESP-NOW
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    return;
  } else {
    Serial.println("ESP-NOW initialized successfully");
  }

  // Callback function for receiving data
  esp_now_register_recv_cb([](const uint8_t *mac, const uint8_t *data, int len)
  {
    Serial.println("Data received");

    // Process the received data
    memcpy(&sensorMessage, data, sizeof(sensorMessage));

    // Handle the received data
    handleTemperatureInput();
    handleMoistureInput();

    // Handle alerts
    handleAlerts();

  });
}

void loop()
{
}

// Handle the alert values and control motors from here
void handleAlerts()
{
  // We can only turn on either the fan or the pump, not both
  // Moisture alert comes first
  Serial.printf("Moisture Alert: %s\n", moistureAlert ? "ON" : "OFF");
  if(moistureAlert)
  {
    Serial.println("Moisture Alert");

    // Set the led color
    driverControl.rgbControl.fadeToColor(MOISTURE_ALERT_COLOR);

    // Set the water pump speed
    int waterPumpSpeed = analogRead(WATER_PUMP_POTENTIOMETER_PIN);
    int waterPumpPwmValue = map(waterPumpSpeed, 0, 4095, 0, 255);
    ledcWrite(WATER_PUMP_PWM_CHANNEL, waterPumpPwmValue);

    // Stay here and wait for the moisture to be above the threshold
    // blink the led to indicate the alert is processing
    // while(moistureAlert)
    // {
    //   // Blink the led
    //   driverControl.rgbControl.setColor(MOISTURE_ALERT_COLOR);
    //   delay(500);
    //   driverControl.rgbControl.setColor({0, 0, 0});
    //   delay(500);

    //   // Read Sensor Value
    //   Serial.printf("Moisture Alert: %.2f\n", sensorMessage.moisture);

    //   // Convert to moisture and store in the control class
    //   float moisture = driverControl.moistureControl.getMoisture(sensorMessage.moisture);

    //   // Check if the moisture is below the alert threshold
    //   moistureAlert = driverControl.moistureControl.alert();

    //   // Print the moisture value
    //   Serial.printf("Moisture: %.2f\n", moisture);
    // }
  }
  else if (temperatureAlert)
  {
    // Set the led color
    driverControl.rgbControl.fadeToColor(TEMPERATURE_ALERT_COLOR);

    // Set the fan speed
    int fanSpeed = analogRead(FAN_POTENTIOMETER_PIN);
    int fanPwmValue = map(fanSpeed, 0, 4095, 0, 255);
    ledcWrite(FAN_PWN_CHANNEL, fanPwmValue);

    // Stay here and wait for the temperature to be below the threshold
    // blink the led to indicate the alert is processing
    while(temperatureAlert)
    {
      // Blink the led
      driverControl.rgbControl.setColor(TEMPERATURE_ALERT_COLOR);
      delay(500);
      driverControl.rgbControl.setColor({0, 0, 0});
      delay(500);

      // Read Sensor Value
      Serial.printf("Temperature Alert: %.2f\n", sensorMessage.temperature);

      // Convert to degrees Fahrenheit and store in the control class
      float temperature = driverControl.temperatureControl.getTemperature(sensorMessage.temperature);

      // Check if the temperature is above the alert threshold
      temperatureAlert = driverControl.temperatureControl.alert();

      // Print the temperature value
      Serial.printf("Temperature: %.2f°F\n", temperature);
    }
  }
  else
  {
    // Turn off both motors and set led color to off
    driverControl.rgbControl.setColor({0, 0, 0});
    ledcWrite(FAN_PWN_CHANNEL, 0);
    ledcWrite(WATER_PUMP_PWM_CHANNEL, 0);
  }

  // We need to turn these off when both are done
  // Turn off both motors and set led color to off
  driverControl.rgbControl.setColor({0, 0, 0});
  ledcWrite(FAN_PWN_CHANNEL, 0);
  ledcWrite(WATER_PUMP_PWM_CHANNEL, 0);

  return;
}

void handleTemperatureInput()
{
  // Read Sensor Value
  Serial.printf("Received Temperature: %.2f\n", sensorMessage.temperature);
  
  // Convert to degrees Fahrenheit and store in the control class
  float temperature = driverControl.temperatureControl.getTemperature(sensorMessage.temperature);

  // Check if the temperature is above the alert threshold
  //temperatureAlert = driverControl.temperatureControl.alert();

  // Print the temperature value
  Serial.printf("Temperature: %.2f°F\n", temperature);

  return;
}

void handleMoistureInput()
{
  // Read Sensor Value
  Serial.printf("\nReceived Moisture: %.2f\n", sensorMessage.moisture);

  // Convert to moisture and store in the control class
  float moisture = driverControl.moistureControl.getMoisture(sensorMessage.moisture);

  // Check if the moisture is below the alert threshold
  moistureAlert = driverControl.moistureControl.alert();

  // Print the moisture value
  Serial.printf("Moisture: %.2f\n", moisture);

  Serial.printf("Moisture Alert: %s\n", moistureAlert ? "ON" : "OFF");

  return;
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

// Function to setup the control class
void control_Setup()
{
  // Setup the RGB control
  driverControl.rgbControl.setup();

  // Setup the temperature control
  // No setup needed for temperature control

  // Setup the moisture control
  // No setup needed for moisture control

  return;
}