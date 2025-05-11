#include <Ticker.h>

#include "pinout.h"

#ifndef CONTROLS_H
#define CONTROLS_H

struct Button {
  unsigned int pin;

  unsigned long timer;

  unsigned long holdTime;
  bool pressActive;
  bool holdActive;

  void (*callbackPress)();
  void (*callbackHold)();
};

struct Analog {
  unsigned int pin;

  int value;
  int lastValue;
  int filtered;

  int minValue;
  int maxValue;
};

static bool analogLock = false;                      // Flag for analog lock
static const unsigned char analogLockThreshold = 5;  // Threshold for analog lock
static const float analogFilter = 0.1;               // Analog filter value (0.0 to 1.0)

class Controls {
  public:
  static void setup();

  static void handle();

  static void onPressed(int index, void (*callback)());

  static void onHold(int index, void (*callback)());

  // Analog value mapped to [0, 255]
  static unsigned short getAnalog();

  // Analog value mapped to [0, 255] with filter
  static unsigned short getFilteredAnalog();

  static void lockAnalog();
  static bool tryUnlockAnalog();
  static void unlockAnalog();
  static bool isAnalogLocked();
};

#endif