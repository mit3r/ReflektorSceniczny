#include "interfaces/lights.h"

static Color startColor = {0, 0, 0};  // Start color
static Color currentColor = {0, 0, 0};
static Color targetColor = {0, 0, 0};

// Difference between current and target
static short diffRed = 0;
static short diffGreen = 0;
static short diffBlue = 0;

static unsigned long startTime = 0;
static unsigned long durationTime = 0;
static bool fading = false;

void Lights::setup() {
  static Ticker ticker;
  ticker.attach_ms(16, Lights::handle);
}

void Lights::handle() {
  if (!fading) return;

  unsigned char progress = 0;
  if (durationTime == 0) {
    progress = Movement::movingProgress();
  } else {
    progress = constrain((millis() - startTime) * 255 / durationTime, 0, 255);
  }

  currentColor.r = startColor.r + (diffRed * progress / 255);
  currentColor.g = startColor.g + (diffGreen * progress / 255);
  currentColor.b = startColor.b + (diffBlue * progress / 255);

  analogWrite(Pins::LED_RED, currentColor.r);
  analogWrite(Pins::LED_GREEN, currentColor.g);
  analogWrite(Pins::LED_BLUE, currentColor.b);

  if (progress == 255) stop();
}

bool Lights::fadeColorTo(Color color, unsigned long duration) {
  if (fading) return false;  // Already fading

  startColor = currentColor;
  targetColor = color;
  diffRed = targetColor.r - startColor.r;
  diffGreen = targetColor.g - startColor.g;
  diffBlue = targetColor.b - startColor.b;

  startTime = millis();
  durationTime = duration;

  fading = diffRed != 0 || diffGreen != 0 || diffBlue != 0;
  return true;
}

bool Lights::fadeRedTo(unsigned char red, unsigned long duration) {
  if (fading) return false;  // Already fading

  startColor = currentColor;
  targetColor.r = red;
  diffRed = targetColor.r - startColor.r;

  startTime = millis();
  durationTime = duration;

  fading = diffRed != 0;
  return true;
}
bool Lights::fadeGreenTo(unsigned char green, unsigned long duration) {
  if (fading) return false;  // Already fading

  startColor = currentColor;
  targetColor.g = green;
  diffGreen = targetColor.g - startColor.g;

  startTime = millis();
  durationTime = duration;

  fading = diffGreen != 0;
  return true;
}
bool Lights::fadeBlueTo(unsigned char blue, unsigned long duration) {
  if (fading) return false;  // Already fading

  startColor = currentColor;
  targetColor.b = blue;
  diffBlue = targetColor.b - startColor.b;

  startTime = millis();
  durationTime = duration;

  fading = diffBlue != 0;
  return true;
}

const bool Lights::isFading() {
  return fading;
}

void Lights::stop() {
  fading = false;
  currentColor = targetColor;
  durationTime = 0;
  startTime = 0;
}

const Color Lights::getTargetColor() {
  return targetColor;
}

const Color Lights::getCurrentColor() {
  return currentColor;
}
