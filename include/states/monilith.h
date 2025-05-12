#include <Arduino.h>

#include "api/chooser.h"
#include "api/sequence.h"
#include "api/states.h"
#include "config/scenes.h"
#include "interfaces/controls.h"
#include "interfaces/lights.h"
#include "interfaces/movement.h"

#ifndef MONOLITH_STATE
#define MONOLITH_STATE

namespace MonolithState {
void setup() {
  Controls::onHold(0, []() {
    Serial.printf("Going to scene\n");
    StateManager::setState(0);
    Serial.printf("Scene state set\n");
  });                                                        // Go to scene
  Controls::onHold(1, []() { StateManager::setState(2); });  // Go to puppeteur

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

  Movement::moveTo(0, 0, true);
  blinkWhite->run();
  Serial.printf("< %-9s >\n", "Monolith");
}

void handle() {
  unsigned char analog = Controls::getFilteredAnalog();

  if (!Controls::tryUnlockAnalog()) {
    switch (chooser.current()) {
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