#include <Arduino.h>

#include "api/chooser.h"
#include "api/sequence.h"
#include "api/states.h"
#include "config/scenes.h"
#include "interfaces/controls.h"

#ifndef PUPPETEUR_STATE
#define PUPPETEUR_STATE

namespace PuppeteurState {
void setup() {
  Serial.printf("Puppeteur setup\n");

  Controls::unlockAnalog();
  customBlueSeq->clear();  // Clear the sequence

  Controls::onHold(0, []() {  // Add frame to sequence
    customBlueSeq->add(Lights::getTargetColor(), Movement::getTargetAnglePosition());
    auto f = customBlueSeq->getSize();
    Serial.printf("Added frame %d to sequence\n", f);
    blinkBlue->run();
    if (f >= Sequence::maxFrames) StateManager::setState(1);
  });

  Controls::onHold(1, []() {  // Go to monilith
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

  blinkBlue->run();
  Serial.printf("< %-9s >\n", "Puppeteur");
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
      Lights::setRedTo(analog);
      break;
    case 3:
      Lights::setGreen(analog);
      break;
    case 4:
      Lights::setBlue(analog);
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