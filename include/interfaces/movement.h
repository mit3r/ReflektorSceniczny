#include "config/pinout.h"
//
#include <Arduino.h>

#include "Ticker.h"
#include "utils.h"

#ifndef MOVEMENT_H
#define MOVEMENT_H

class Movement {
  private:
  const static unsigned short stepsPer360 = 2037.5;  // 2037.5;  //
  const static unsigned short minStepDelay = 2;      // 4ms delay between steps
  const static unsigned short maxStepDelay = 100;    // 100ms delay between steps

  const constexpr static Point maxAngle = {180, 90};    // max angle in [degrees]
  const constexpr static Point minAngle = {-180, -90};  // min angle in [degrees]

  static Point distanceSteps;         // start position in [steps]
  static Point currentSteps;          // current position in [steps]
  static Point targetSteps;           // target position in [steps]
  static Point currentDistanceSteps;  // difference between target and current position in [steps]

  public:
  static void setup();

  static bool moveToAngle(Point angle);
  static bool movePanToAngle(short angle);
  static bool moveTiltToAngle(short angle);

  static const bool isMoving();
  static const unsigned char movingProgress();  // [0, 255] - 0% to 100%
  static void stop();

  static const Point getTargetAngle();
  static const Point getCurrentAngle();

  private:
  // @param pan axis - dir: `true` = right, `false` - left
  static bool stepPan();
  // @param tilt axis - dir: `true` = down, `false` - up
  static bool stepTilt();
};

#endif