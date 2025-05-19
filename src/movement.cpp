#include "interfaces/movement.h"

static unsigned int now = millis();

Point Movement::distanceSteps = {0, 0};         // distance to target in [steps]
Point Movement::currentSteps = {0, 0};          // current position in [steps]
Point Movement::targetSteps = {0, 0};           // target position in [steps]
Point Movement::currentDistanceSteps = {0, 0};  // difference between target and current position in [steps]

void Movement::setup() {
  static Ticker tickerPan;
  tickerPan.attach_ms(2, Movement::stepPan);

  static Ticker tickerTilt;
  tickerTilt.attach_ms(2, Movement::stepTilt);
}

bool Movement::moveToAngle(Point angle) {
  if (isMoving()) return false;

  targetSteps.x = constrain(angle.x, minAngle.x, maxAngle.x) * stepsPer360 / 360;
  targetSteps.y = constrain(angle.y, minAngle.y, maxAngle.y) * stepsPer360 / 360;

  distanceSteps.x = targetSteps.x - currentSteps.x;
  currentDistanceSteps.x = distanceSteps.x;

  distanceSteps.y = targetSteps.y - currentSteps.y;
  currentDistanceSteps.y = distanceSteps.y;

  return true;
}

bool Movement::movePanToAngle(short angle) {
  if (isMoving()) return false;  // If already moving, return false
  targetSteps.x = constrain(angle, minAngle.x, maxAngle.x) * stepsPer360 / 360;
  distanceSteps.x = targetSteps.x - currentSteps.x;
  currentDistanceSteps.x = distanceSteps.x;

  return true;
}
bool Movement::moveTiltToAngle(short angle) {
  if (isMoving()) return false;  // If already moving, return false
  targetSteps.y = constrain(angle, minAngle.y, maxAngle.y) * stepsPer360 / 360;
  distanceSteps.y = targetSteps.y - currentSteps.y;
  currentDistanceSteps.y = distanceSteps.y;

  return true;
}

const bool Movement::isMoving() {
  return currentDistanceSteps.x != 0 || currentDistanceSteps.y != 0;
}

const unsigned char Movement::movingProgress() {
  if (!isMoving()) return 255;

  float progressX = distanceSteps.x != 0 ? 255 - abs(currentDistanceSteps.x * 255 / distanceSteps.x) : 255;
  float progressY = distanceSteps.y != 0 ? 255 - abs(currentDistanceSteps.y * 255 / distanceSteps.y) : 255;
  return (progressX + progressY) / 2;
}

void Movement::stop() {
  targetSteps = currentSteps;
  distanceSteps = {0, 0};
  currentDistanceSteps = {0, 0};
}

const Point Movement::getTargetAngle() {
  return {(short)(targetSteps.x * 360 / stepsPer360),
          (short)(targetSteps.y * 360 / stepsPer360)};
}

const Point Movement::getCurrentAngle() {
  return {(short)(currentSteps.x * 360 / stepsPer360),
          (short)(currentSteps.y * 360 / stepsPer360)};
}

bool Movement::stepPan() {
  if (currentDistanceSteps.x == 0)
    return false;

  if (currentDistanceSteps.x > 0) {
    digitalWrite(Pins::DIRECTION, HIGH);
    currentDistanceSteps.x--;
    currentSteps.x++;
  } else {
    digitalWrite(Pins::DIRECTION, LOW);
    currentDistanceSteps.x++;
    currentSteps.x--;
  }

  digitalWrite(Pins::PAN_STEP, HIGH);
  digitalWrite(Pins::PAN_STEP, LOW);

  return true;
}

bool Movement::stepTilt() {
  if (currentDistanceSteps.y == 0)
    return false;

  if (currentDistanceSteps.y > 0) {
    digitalWrite(Pins::DIRECTION, LOW);
    currentDistanceSteps.y--;
    currentSteps.y++;
  } else {
    digitalWrite(Pins::DIRECTION, HIGH);
    currentDistanceSteps.y++;
    currentSteps.y--;
  }

  digitalWrite(Pins::TILT_STEP, HIGH);
  digitalWrite(Pins::TILT_STEP, LOW);
  return true;
}
