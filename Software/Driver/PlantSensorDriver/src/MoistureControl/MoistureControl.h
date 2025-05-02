#ifndef MOISTURE_CONTROL_H
#define MOISTURE_CONTROL_H
#include <Arduino.h>
#include "BaseControl/BaseControl.h"

class MoistureControl : public BaseControl
{
    private:
        float sensorInput; // Value sent from the sensor
        float moisture; // Moisture value
        float alertThreshold; // Alert threshold
    public:
        // Constructor
        MoistureControl(float voltageReference = 3.3, float analogResolution = 4095.0, float alertThreshold = 30.0);

        // Get the moisture value from input
        // We know the input need converted to voltage
        // and then to moisture
        float getMoisture(float analogInput);
};

#endif