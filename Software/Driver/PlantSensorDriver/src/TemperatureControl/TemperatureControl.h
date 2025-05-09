#ifndef TEMPERATURE_CONTROL_H
#define TEMPERATURE_CONTROL_H

#include <Arduino.h>

class TemperatureControl
{
    private:
        float sensorInput; // Value sent from the sensor
        float temperature; // Temperature value
        float humidity; // Humidity value
        float alertThreshold; // Alert threshold

    public:
        // Constructor
        TemperatureControl(float alertThreshold);

        // Get the temperature value from input
        // We know the input need converted to voltage
        // and then to temperature
        float getTemperature(float analogInput);

        //TODO: Get the humidity value from input

        // Set the alert if the temperature is above the threshold
        bool alert(){
            return temperature > alertThreshold;
        }

};

#endif