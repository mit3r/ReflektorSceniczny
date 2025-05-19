#include <Arduino.h>

#include "api/chooser.h"
#include "api/states.h"
#include "api/theater.h"
#include "config/scenes.h"
#include "interfaces/controls.h"
#include "interfaces/lights.h"
#include "interfaces/movement.h"

#ifndef MONOLITH_STATE
#define MONOLITH_STATE

namespace MonolithState {

Chooser chooser(5, 0);

void setup() {
  Controls::clearCallbacks();
  Controls::onHold(0, []() { StateManager::setState(0); });
  Controls::onHold(1, []() { StateManager::setState(2); });

  Controls::onPressed(0, []() {
    Controls::lockAnalog();
    chooser.previousChoice();
    Serial.printf("Adjusting parameter: %d\n", chooser.current());
  });

  Controls::onPressed(1, []() {
    Controls::lockAnalog();
    chooser.nextChoice();
    Serial.printf("Adjusting parameter: %d\n", chooser.current());
  });

  Serial.printf("< %-9s >\n", "Monolith");
  Theater::run(createBlinkAnimation({100, 100, 100}, 100, 100, 3));
}

void handle() {
  unsigned char analog = Controls::getFilteredAnalog();

  if (!Controls::tryUnlockAnalog()) {
    switch (chooser.current()) {
    case 0:
      Movement::movePanToAngle(map(analog, 0, 255, -90, 90));
      break;
    case 1:
      Movement::moveTiltToAngle(map(analog, 0, 255, -90, 90));
      break;
    case 2:
      Lights::fadeRedTo(analog);
      break;
    case 3:
      Lights::fadeGreenTo(analog);
      break;
    case 4:
      Lights::fadeBlueTo(analog);
      break;
    }
  }
}

void cleanup() {
}

State state = {
    .setup = setup,
    .handle = handle,
    .cleanup = cleanup,
};

};  // namespace MonolithState

#endif