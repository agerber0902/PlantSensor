#include "MoistureControl.h"

// Constructor
MoistureControl::MoistureControl(float threshold, float vRef, float resolution)
    : alertThreshold(threshold),
      BaseControl(vRef, resolution) {}

// Function to read moisture level
float MoistureControl::getMoisture(float inputValue)
{
    sensorInput = analogToVoltage(inputValue);
    moisture = sensorInput;
    return moisture;
}