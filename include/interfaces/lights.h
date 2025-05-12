#include <Arduino.h>
#include <Ticker.h>

#include "config/pinout.h"
#include "utils.h"

#ifndef LIGHTS_H
#define LIGHTS_H

class Lights {
  public:
  static void setup();

  // Handle the fading animation
  // This function should be called in the main loop
  static void handle();

  // Fade to a target color over a specified delay
  // @param _color: target color
  // @param _delay: delay in milliseconds (default is 0)
  static void fadeTo(Color _color, unsigned long _delay = 0);

  static void setRedTo(unsigned char _red);

  static void setGreen(unsigned char _green);

  static void setBlue(unsigned char _blue);

  static const Color getTargetColor();
};

#endif  // LIGHTS_H