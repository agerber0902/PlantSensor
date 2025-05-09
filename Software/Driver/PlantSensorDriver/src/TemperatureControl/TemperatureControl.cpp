#include "TemperatureControl.h"
#include <Arduino.h>

// Constructor
TemperatureControl::TemperatureControl(float alertThreshold)
: 
alertThreshold(alertThreshold){}


// Get the temperature value from input
float TemperatureControl::getTemperature(float analogInput) {
    // Convert the analog input to voltage - we dont need to do this the dht 11 sends temperature in celsius
    //sensorInput = analogToVoltage(analogInput);
    // float temperatureC = (analogInput - 0.5) * 100.0;
    temperature = analogInput * 9.0 / 5.0 + 32.0;
    return temperature; 
}