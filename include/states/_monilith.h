#include <Arduino.h>

#include "chooser.h"
#include "controls.h"
#include "predefined.h"
#include "sequence.h"
#include "states/node.h"
#include "states/states.h"

#ifndef MONOLITH_STATE
#define MONOLITH_STATE

Chooser mParams(5, 0);

StateNode monilithState = {
    .setupFunction = []() {
  Controls::onHold(0, []() { State::setState(0); });  // Go to scene
  Controls::onHold(1, []() { State::setState(2); });  // Go to puppeteur

  Controls::onPressed(0, []() {
    Controls::lockAnalog();
    mParams.previousChoice();
    Serial.printf("Adjusting parameter: %d\n", mParams.current());
  });

  Controls::onPressed(1, []() {
    Controls::lockAnalog();
    mParams.nextChoice();
    Serial.printf("Adjusting parameter: %d\n", mParams.current());
  });

  Movement::moveTo(0, 0, true);
  blinkWhite->run();
  Serial.printf("< %-9s >\n", "Monolith");
},

    .handleFunction = []() {
  unsigned char analog = Controls::getFilteredAnalog();

  if (!Controls::tryUnlockAnalog()) {
    switch (mParams.current()) {
    case 0:
      Movement::movePan(map(analog, 0, 255, -90, 90));
      break;
    case 1:
      Movement::moveTilt(map(analog, 0, 255, -90, 90));
      break;
    case 2:
      Lights::setRedTo(map(analog, 0, 255, 0, 255));
      break;
    case 3:
      Lights::setGreen(map(analog, 0, 255, 0, 255));
      break;
    case 4:
      Lights::setBlue(map(analog, 0, 255, 0, 255));
      break;
    }
  }
}};

#endif