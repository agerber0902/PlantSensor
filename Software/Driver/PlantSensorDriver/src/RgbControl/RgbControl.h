
#include <array>

#ifndef RGB_CONTROL_H
#define RGB_CONTROL_H

class RgbControl 
{
private:
    // Color Pins 
    int redPin;
    int greenPin;
    int bluePin;

    // Color Channels
    int redChannel;
    int greenChannel;
    int blueChannel;

    // controls
    int frequency;
    int resoulutionBits;

public:
    // Constructor
    RgbControl(int redPin, int greenPin, int bluePin, int redChannel, int greenChannel, int blueChannel, int freq = 5000, int resBit = 8);

    // Setup
    void setup();

    // instantly change color
    void setColor(const std::array<int, 3>& targetColor);

    // fade color
    void fadeToColor(const std::array<int, 3>& targetColor);
};

#endif