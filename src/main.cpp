

#include <Arduino.h>
#include <Ticker.h>

//
#include "interfaces/controls.h"
#include "interfaces/lights.h"
#include "interfaces/movement.h"
//
#include "api/network.h"
#include "api/states.h"
#include "api/theater.h"
//
#include "states/monilith.h"
#include "states/puppeteur.h"
#include "states/scene.h"

void setup() {
  Serial.begin(115200);

  Network::setup();
  Pins::setup();

  Movement::setup();
  Lights::setup();

  Controls::setup();
  Theater::setup();

  static State *stateList = new State[3];
  stateList[0] = SceneState::state;
  stateList[1] = MonolithState::state;
  stateList[2] = PuppeteurState::state;
  StateManager::setup(stateList, 3, 1);

  Network::begin();
}

void loop() {}