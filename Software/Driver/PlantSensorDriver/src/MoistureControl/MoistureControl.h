#ifndef MOISTURE_CONTROL_H
#define MOISTURE_CONTROL_H
#include <Arduino.h>
#include "BaseControl/BaseControl.h"

class MoistureControl //: public BaseControl
{
    private:
        float sensorInput; // Value sent from the sensor
        float moisture; // Moisture value
        float alertThreshold; // Alert threshold
    public:
        // Constructor
        MoistureControl(float alertThreshold);

        // Get the moisture value from input
        // We know the input need converted to voltage
        // and then to moisture
        float getMoisture(float analogInput);

        // Set the alert if the moisture is below the threshold
        bool alert(){
            Serial.printf("Moisture Testing: %f\n", alertThreshold);
            // Check if the moisture is below the alert threshold
            return moisture < alertThreshold;
        }
};

#endif