#include "interfaces/movement.h"

static unsigned int now = millis();

short Movement::x = 0;   // pan  axis [steps]
short Movement::y = 0;   // tilt axis [steps]
short Movement::tx = 0;  // target pan axis [steps]
short Movement::ty = 0;  // target tilt axis [steps]
bool Movement::moving = false;

void Movement::setup() {
  static Ticker ticker;
  ticker.attach_ms(4, Movement::handle);
}

void Movement::stepPan(bool dir) {
  x += dir ? 1 : -1;
  digitalWrite(Pins::DIRECTION, dir ? HIGH : LOW);
  digitalWrite(Pins::PAN_STEP, HIGH);
  now = millis();
  while (millis() - now < minStepDelay) {
  }

  digitalWrite(Pins::PAN_STEP, LOW);
  now = millis();
  while (millis() - now < minStepDelay) {
  }
}

void Movement::stepTilt(bool dir) {
  y += dir ? -1 : 1;
  digitalWrite(Pins::DIRECTION, dir ? HIGH : LOW);
  digitalWrite(Pins::TILT_STEP, HIGH);

  now = millis();
  while (millis() - now < minStepDelay) {
  }
  digitalWrite(Pins::TILT_STEP, LOW);
  now = millis();
  while (millis() - now < minStepDelay) {
  }
}

void Movement::moveTo(short targetAngleX, short targetAngleY, bool immediate) {
  if (moving && !immediate) return;

  // Clamp and convert the target angles to steps
  tx = constrain(targetAngleX, panMin, panMax) * 1.4 * stepsPer360 / 360;
  ty = constrain(targetAngleY, tiltMin, tiltMax) * stepsPer360 / 360;
  moving = true;
}

void Movement::movePan(short targetAngleX, bool immediate) {
  if (moving && !immediate) return;

  tx = constrain(targetAngleX, panMin, panMax) * 1.4 * stepsPer360 / 360;
  moving = true;
}

void Movement::moveTilt(short targetAngleY, bool immediate) {
  if (moving && !immediate) return;

  ty = constrain(targetAngleY, tiltMin, tiltMax) * stepsPer360 / 360;
  moving = true;
}

unsigned long Movement::timeOf(short targetAngleX, short targetAngleY) {
  // Clamp and convert the target angles to steps
  tx = constrain(targetAngleX, panMin, panMax) * 1.4 * stepsPer360 / 360;
  ty = constrain(targetAngleY, tiltMin, tiltMax) * stepsPer360 / 360;

  // Calculate the time needed to reach the target angles
  return abs(tx - x) * minStepDelay + abs(ty - y) * minStepDelay;
}

const bool Movement::isMoving() {
  return moving;
}

const Point Movement::getTargetStepsPosition() {
  return Point{tx, ty};
}

const Point Movement::getCurrentStepsPosition() {
  return Point{x, y};
}

const Point Movement::getTargetAnglePosition() {
  return Point{(short)((float)tx * 360.f / stepsPer360), (short)((float)ty * 360.f / stepsPer360)};
}

const Point Movement::getCurrentAnglePosition() {
  return Point{(short)((float)x * 360.f / stepsPer360), (short)((float)y * 360.f / stepsPer360)};
}

void Movement::stop() {
  ty = y;
  tx = x;
  moving = false;
}

void Movement::handle() {
  short dx = tx - x;
  if (dx != 0)
    stepPan(dx > 0);

  short dy = ty - y;
  if (dy != 0)
    stepTilt(dy < 0);

  if (dx == 0 && dy == 0)
    moving = false;
}