#include <Arduino.h>

#ifndef PINOUT_H
#define PINOUT_H

namespace Pins {
enum Pins {

  // Movement
  DIRECTION = D0,
  TILT_STEP = D2,
  PAN_STEP = D3,

  TILT_LIMIT = D4,  // (pullup)

  // Lights
  LED_BLUE = D5,
  LED_RED = D6,
  LED_GREEN = D7,

  // Controls
  BUTTON0 = D8,  // Yellow (pulldown)
  BUTTON1 = D1,  // Blue
  ANALOG = A0,

};

void setup();
}  // namespace Pins

#endif