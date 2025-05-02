#ifndef BASE_CONTROL_H
#define BASE_CONTROL_H
#include <Arduino.h>

class BaseControl
{
private:
    float voltageReference; // Reference voltage for the analog input
    float analogResolution; // Resolution of the analog input (default is 4095 for 12-bit ADC)
public:
    // Constructor
    BaseControl(float voltageReference = 3.3, float analogResolution = 4095.0);

    // Helper functions
    float readFromAnalog(int inputPin);
    float analogToVoltage(float value);
};

#endif