#include "interfaces/lights.h"

static float maxBrightness = 1.0;  // Maximum brightness for the LEDs (0.0 to 1.0)
static Color current = {0, 0, 0};
static Color target = {0, 0, 0};
static unsigned long startTime = 0;
static unsigned long fadeDelay = 0;
static bool isAnimating = false;

void Lights::setup() {
  static Ticker ticker;
  ticker.attach_ms(16, Lights::handle);
}

void Lights::handle() {
  unsigned long now = millis();
  unsigned long elapsed = now - startTime;

  if (elapsed >= fadeDelay) {
    current = target;
    isAnimating = false;
  }

  float ratio = (fadeDelay == 0) ? 1 : (float)elapsed / (float)(fadeDelay);
  current.r += (target.r - current.r) * ratio;
  current.g += (target.g - current.g) * ratio;
  current.b += (target.b - current.b) * ratio;

  analogWrite(Pins::LED_RED, current.r);
  analogWrite(Pins::LED_GREEN, current.g);
  analogWrite(Pins::LED_BLUE, current.b);
}

void Lights::fadeTo(Color _color, unsigned long _delay) {
  if (isAnimating) return;
  isAnimating = true;

  target = _color;
  target.r *= maxBrightness;
  target.g *= maxBrightness;
  target.b *= maxBrightness;

  startTime = millis();
  fadeDelay = _delay;
}

void Lights::setRedTo(unsigned char _red) {
  if (isAnimating) return;
  isAnimating = true;
  target.r = _red * maxBrightness;
  fadeDelay = 0;
}

void Lights::setGreen(unsigned char _green) {
  if (isAnimating) return;
  isAnimating = true;
  target.g = _green * maxBrightness;
  fadeDelay = 0;
}

void Lights::setBlue(unsigned char _blue) {
  if (isAnimating) return;
  isAnimating = true;
  target.b = _blue * maxBrightness;
  fadeDelay = 0;
}

const Color Lights::getTargetColor() {
  return target;
}
