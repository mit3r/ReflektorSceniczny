#include <Arduino.h>

#include "api/sequence.h"
#include "api/states.h"
#include "config/scenes.h"
#include "interfaces/controls.h"

#ifndef SCENE_STATE
#define SCENE_STATE

namespace SceneState {

struct Item {
  Color identifier;
  Sequence *sequence;
};

static bool looping = false;
static unsigned char choose = 0;
static const unsigned char length = 3;

static Item items[length] = {
    {Color{255, 0, 0}, predefinedRedSeq},    // Red
    {Color{0, 255, 0}, predefinedGreenSeq},  // Green
    {Color{0, 0, 255}, customBlueSeq},       // Blue
};

void setup() {
  Controls::onHold(0, []() {
    StateManager::setState(1);
  });

  Controls::onHold(1, []() {
    if (Sequence::isRunning()) {
      looping = false;
      Sequence::stop();
      Serial.printf("Stopping scene: %d\n", choose);
    } else {
      looping = true;
      items[choose].sequence->run();
      Serial.printf("Running scene: %d\n", choose);
    }
  });

  Controls::onPressed(0, []() {
    choose = choose - 1 < 0 ? length - 1 : choose - 1;
    Serial.printf("Selected scene: %d\n", choose);
  });

  Controls::onPressed(1, []() {
    choose = choose + 1 > length - 1 ? 0 : choose + 1;
    Serial.printf("Selected scene: %d\n", choose);
  });

  blinkYellow->run();
  Serial.printf("< %-9s >\n", "Scene");
  Lights::fadeTo(items[choose].identifier, 0);
}

void handle() {
  if (!Sequence::isRunning()) {
    if (looping)
      items[choose].sequence->run();

    Lights::fadeTo(items[choose].identifier, 0);
    Movement::moveTo(0, 0);
  }
  // Handle the sequence state
}

void cleanup() {}

State state = {
    .setup = setup,
    .handle = handle,
    .cleanup = cleanup,
};

}  // namespace SceneState

#endif