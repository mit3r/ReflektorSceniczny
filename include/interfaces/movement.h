#include "config/pinout.h"
//
#include <Arduino.h>

#include "Ticker.h"
#include "utils.h"

#ifndef MOVEMENT_H
#define MOVEMENT_H

typedef unsigned short ushort;

const ushort stepsPer360 = 2037;  // 2037.5;  //
const ushort minStepDelay = 2;    // 4ms delay between steps
const ushort maxStepDelay = 100;  // 100ms delay between steps

const short panMax = 180;
const short panMin = -180;

const short tiltMax = 90;
const short tiltMin = -90;

class Movement {
  public:
  static void setup();
  // Handle the movement of the motors
  // This function should be called in the main loop
  static void handle();

  // Orders a movement to the target angles
  // @param targetAngleX: target angle in panorama axis [<0: left, 0: center, >0: right>]
  // @param targetAngleY: target angle in tilt axis [<0: up, 0: center, >0: down>]
  // @return: `true` if the movement was ordered, `false` if the motors are already moving
  // @note: The target angles are clamped to the limits defined by `panMax`, `panMin`, `tiltMax`, and `tiltMin`.
  static void moveTo(short targetAngleX, short targetAngleY, bool immediate = false);
  static void movePan(short targetAngleX, bool immediate = true);
  static void moveTilt(short targetAngleY, bool immediate = true);

  // Returns the time needed to reach the target angles
  static unsigned long timeOf(short targetAngleX, short targetAngleY);
  static const bool isMoving();

  static const Point getTargetStepsPosition();
  static const Point getTargetAnglePosition();
  static const Point getCurrentStepsPosition();
  static const Point getCurrentAnglePosition();

  static void stop();

  private:
  // Step motors in panorama axis
  // @param dir: `true` = right, `false` - left
  static void stepPan(bool dir);

  // Step motors in tilt axis
  // @param dir: `true` = down, `false` - up
  static void stepTilt(bool dir);

};  // namespace Movement

#endif