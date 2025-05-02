#ifndef TEMPERATURE_CONTROL_H
#define TEMPERATURE_CONTROL_H

#include <Arduino.h>
#include "BaseControl/BaseControl.h"

class TemperatureControl : public BaseControl
{
    private:
        float sensorInput; // Value sent from the sensor
        float temperature; // Temperature value
        float humidity; // Humidity value
        float alertThreshold; // Alert threshold
    public:
        // Constructor
        TemperatureControl(float voltageReference = 3.3, float analogResolution = 4095.0, float alertThreshold = 75.0);

        // Get the temperature value from input
        // We know the input need converted to voltage
        // and then to temperature
        float getTemperature(float analogInput);

        //TODO: Get the humidity value from input

};

#endif