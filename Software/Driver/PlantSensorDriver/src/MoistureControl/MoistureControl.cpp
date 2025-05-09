#include "MoistureControl.h"

// Constructor
MoistureControl::MoistureControl(float threshold)
    : alertThreshold(threshold){}
     // BaseControl(vRef, resolution) {}

// Function to read moisture level
float MoistureControl::getMoisture(float inputValue)
{
    sensorInput = inputValue;//analogToVoltage(inputValue);
    moisture = sensorInput;
    return moisture;
}