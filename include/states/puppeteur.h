#include <Arduino.h>

#include "api/chooser.h"
#include "api/designer.h"
#include "api/states.h"
#include "api/theater.h"
#include "config/scenes.h"
#include "interfaces/controls.h"

#ifndef PUPPETEUR_STATE
#define PUPPETEUR_STATE

namespace PuppeteurState {

static Chooser chooser = Chooser(5, 0);

void setup() {
  Designer::attach(&scenesTimelines[scenesCount - 1]);
  Designer::clearFrames();

  Controls::clearCallbacks();
  Controls::onHold(0, []() {  // Add frame to sequence
    if (Designer::addFrame()) {
      Serial.printf("Frame added: %d\n", scenesTimelines[scenesCount - 1].size);

      Color color = Lights::getCurrentColor();
      Theater::run(createBlinkAnimation(color, 200, 200, 1));
      Theater::run(createStillAnimation(color, 0));
    } else {
      Serial.println("Max frames reached");
      Designer::detach();
      StateManager::setState(1);
    }
  });

  Controls::onHold(1, []() {  // Go to monilith
    Designer::detach();
    StateManager::setState(1);
  });

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

  Serial.printf("< %-9s >\n", "Puppeteur");
  Theater::run(createBlinkAnimation({0, 0, 255}, 200, 200, 3));
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

void cleanup() {}

State state = {
    .setup = setup,
    .handle = handle,
    .cleanup = cleanup,
};

}  // namespace PuppeteurState

#endif