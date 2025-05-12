#include <Arduino.h>

#include "chooser.h"
#include "controls.h"
#include "sequence.h"
#include "states/node.h"
#include "states/states.h"

#ifndef PUPPETEUR_STATE
#define PUPPETEUR_STATE

Chooser pParams(5, 0);

StateNode puppeteurState = {
    .setupFunction = []() {
  Controls::unlockAnalog();
  customBlueSeq->clear();  // Clear the sequence

  Controls::onHold(0, []() {  // Add frame to sequence
    customBlueSeq->add(Lights::getTargetColor(), Movement::getTargetAnglePosition());
    auto f = customBlueSeq->getSize();
    Serial.printf("Added frame %d to sequence\n", f);
    blinkBlue->run();
    if (f >= Sequence::maxFrames) State::setState(1);
  });

  Controls::onHold(1, []() {  // Go to monilith
    State::setState(1);
  });

  Controls::onPressed(0, []() {
    Controls::lockAnalog();
    pParams.previousChoice();
    Serial.printf("Adjusting parameter: %d\n", pParams.current());
  });

  Controls::onPressed(1, []() {
    Controls::lockAnalog();
    pParams.nextChoice();
    Serial.printf("Adjusting parameter: %d\n", pParams.current());
  });

  blinkBlue->run();
  Serial.printf("< %-9s >\n", "Puppeteur");
},

    .handleFunction = []() {
  unsigned char analog = Controls::getFilteredAnalog();

  if (!Controls::tryUnlockAnalog()) {
    switch (pParams.current()) {
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
}};

#endif