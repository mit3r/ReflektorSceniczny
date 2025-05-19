#include <Arduino.h>
#include <Ticker.h>

#include "config/pinout.h"
#include "interfaces/movement.h"
#include "utils.h"

#ifndef LIGHTS_H
#define LIGHTS_H

class Lights {
  public:
  static void setup();
  static void handle();

  // Fade to a target color over a specified delay
  // @param _color: target color
  // @param _delay: delay in milliseconds (default is 0)
  static bool fadeColorTo(Color color, unsigned long duration = 0);

  static bool fadeRedTo(unsigned char red, unsigned long duration = 1);
  static bool fadeGreenTo(unsigned char green, unsigned long duration = 1);
  static bool fadeBlueTo(unsigned char blue, unsigned long duration = 1);

  static const bool isFading();
  static void stop();

  static const Color getCurrentColor();
  static const Color getTargetColor();
};

#endif  // LIGHTS_H