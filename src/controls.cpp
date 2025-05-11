#include "controls.h"

static Button buttons[] = {
    {Pins::BUTTON0, 0, 250, false, false, nullptr, nullptr},
    {Pins::BUTTON1, 0, 250, false, false, nullptr, nullptr},
};

static Analog analog = {Pins::ANALOG, 0, 0, 0, 0, 1023};

void Controls::setup() {
  static Ticker ticker;
  ticker.attach_ms(16, Controls::handle);
}

void Controls::handle() {
  for (auto &btn : buttons) {
    if (digitalRead(btn.pin) == HIGH) {
      if (btn.pressActive == false) {
        btn.timer = millis();
        btn.pressActive = true;
      }

      if ((millis() - btn.timer) > btn.holdTime && (btn.holdActive == false)) {
        btn.holdActive = true;

        if (btn.callbackHold)
          btn.callbackHold();
      }
    } else {
      if (btn.pressActive) {
        if (btn.holdActive)
          btn.holdActive = false;
        else {
          if (btn.callbackPress)
            btn.callbackPress();
        }

        btn.pressActive = false;
      }
    }
  }

  analog.value = map(analogRead(analog.pin), analog.minValue, analog.maxValue, 255, 0);
  analog.filtered = analog.value * analogFilter + analog.filtered * (1 - analogFilter);
}

void Controls::onPressed(int index, void (*callback)()) {
  buttons[index].callbackPress = callback;
}

void Controls::onHold(int index, void (*callback)()) {
  buttons[index].callbackHold = callback;
}

unsigned short Controls::getAnalog() { return analog.value; }

unsigned short Controls::getFilteredAnalog() { return analog.filtered; }

void Controls::lockAnalog() {
  analog.lastValue = analog.value;
  analogLock = true;
}

bool Controls::tryUnlockAnalog() {
  if (analogLock && abs((int)(analog.value - analog.lastValue)) > analogLockThreshold)
    analogLock = false;

  return analogLock;
}

void Controls::unlockAnalog() { analogLock = false; }

bool Controls::isAnalogLocked() { return analogLock; }
