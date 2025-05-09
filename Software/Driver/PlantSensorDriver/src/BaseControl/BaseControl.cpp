#include "BaseControl.h"

// Constructor
BaseControl::BaseControl(float vRef, float resolution)
    : voltageReference(vRef), analogResolution(resolution) {}

// Helper function to read from analog pin
float BaseControl::readFromAnalog(int inputPin) {
    analogRead(inputPin); // Dump the first read to negate noise
    delay(5);
    return analogRead(inputPin);
}

// Helper function to convert analog reading to voltage
float BaseControl::analogToVoltage(float value) {
    float sensorVoltage = (value / analogResolution) * voltageReference;
    return sensorVoltage;
}