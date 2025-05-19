#include <Ticker.h>

#include "config/pinout.h"

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

class Controls {
  private:
  const static float analogFilter;                 // Analog filter value (0.0 to 1.0)
  static const unsigned char analogLockThreshold;  // Threshold for analog lock
  static bool analogLock;                          // Flag for analog lock

  public:
  static void setup();
  static void handle();

  static void onPressed(int index, void (*callback)());
  static void onHold(int index, void (*callback)());
  static void clearCallbacks();

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