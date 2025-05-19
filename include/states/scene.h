#include <Arduino.h>

#include "api/states.h"
#include "api/theater.h"
#include "config/scenes.h"
#include "interfaces/controls.h"

#ifndef SCENE_STATE
#define SCENE_STATE

namespace SceneState {

static bool looping = false;
static Chooser chooser = Chooser(scenesCount, 0);

void setup() {
  Controls::clearCallbacks();
  Controls::onHold(0, []() {
    StateManager::setState(1);
  });

  Controls::onHold(1, []() {
    if (Theater::isAnimating()) {
      looping = false;
      Theater::skip();

      Theater::run(createResetPositionAnimation());
      Theater::run(createStillAnimation(scenesColors[chooser.current()], 1));
      Serial.printf("Stopped %d.\n", chooser.current());
    } else {
      looping = true;

      Theater::run(scenesTimelines[chooser.current()]);
      Serial.printf("Running %d...\n", chooser.current());
    }
  });

  Controls::onPressed(0, []() {
    chooser.previousChoice();

    Theater::run(createResetPositionAnimation());
    Theater::run(createStillAnimation(scenesColors[chooser.current()], 1));
    Serial.printf("Selected scene: %d\n", chooser.current());
  });

  Controls::onPressed(1, []() {
    chooser.nextChoice();

    Theater::run(createResetPositionAnimation());
    Theater::run(createStillAnimation(scenesColors[chooser.current()], 1));
    Serial.printf("Selected scene: %d\n", chooser.current());
  });

  Serial.printf("< %-9s >\n", "Scene");
  Theater::run(createResetPositionAnimation());
  Theater::run(createBlinkAnimation({255, 255, 0}, 100, 100, 3));

  Serial.printf("Selected scene: %d\n", chooser.current());
  Theater::run(createStillAnimation(scenesColors[chooser.current()], 1));
}

void handle() {
  if (looping && !Theater::isAnimating()) Theater::run(scenesTimelines[chooser.current()]);
}

void cleanup() {}

State state = {
    .setup = setup,
    .handle = handle,
    .cleanup = cleanup,
};

}  // namespace SceneState

#endif