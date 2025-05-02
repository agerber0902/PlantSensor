#include "TemperatureControl.h"
#include <Arduino.h>

// Constructor
TemperatureControl::TemperatureControl(float alertThreshold,  float vRef, float resolution)
: 
alertThreshold(alertThreshold),
BaseControl(vRef, resolution) {}


// Get the temperature value from input
float TemperatureControl::getTemperature(float analogInput) {
    // Convert the analog input to voltage
    sensorInput = analogToVoltage(analogInput);
    
    float temperatureC = (sensorInput - 0.5) * 100.0;
    temperature = temperatureC * 9.0 / 5.0 + 32.0;
    return temperature; 
}