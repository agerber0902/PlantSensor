#include "RgbControl/RgbControl.h"
#include <Arduino.h>

RgbControl::RgbControl(int redPin, int greenPin, int bluePin, int redChannel, int greenChannel, int blueChannel, int freq, int resBit)
: redPin(redPin), greenPin(greenPin), bluePin(bluePin),
redChannel(redChannel), greenChannel(greenChannel), blueChannel(blueChannel),
frequency(freq), resoulutionBits(resBit)
{}

void RgbControl::setup() {
  // Configure PWM for each color channel
  ledcSetup(redChannel, frequency, resoulutionBits);
  ledcAttachPin(redPin, redChannel);

  ledcSetup(greenChannel, frequency, resoulutionBits);
  ledcAttachPin(greenPin, greenChannel);

  ledcSetup(blueChannel, frequency, resoulutionBits);
  ledcAttachPin(bluePin, blueChannel);
}

// Instantly set color of tri color led
void RgbControl::setColor(const std::array<int, 3>& targetColor) {

  ledcWrite(redChannel, targetColor[0]);
  ledcWrite(greenChannel,targetColor[1]);
  ledcWrite(blueChannel, targetColor[2]);

}

// Changes color slowly for half a sec
void RgbControl::fadeToColor(const std::array<int, 3>& targetColor) {
  static int r = 0, g = 0, b = 0;

  const int steps = 50;
  const int delayMs = 10;

  float rStep = (targetColor[0] - r) / (float)steps;
  float gStep = (targetColor[1] - g) / (float)steps;
  float bStep = (targetColor[2] - b) / (float)steps;

  for (int i = 0; i <= steps; ++i) {
    r = round(r + rStep);
    g = round(g + gStep);
    b = round(b + bStep);

    ledcWrite(redChannel, r);
    ledcWrite(greenChannel, g);
    ledcWrite(blueChannel, b);
    delay(delayMs);
  }
}

