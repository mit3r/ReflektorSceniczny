

#include <Arduino.h>
#include <Ticker.h>

#include "api/network.h"
#include "api/sequence.h"
#include "api/states.h"
#include "interfaces/controls.h"
#include "interfaces/lights.h"
#include "interfaces/movement.h"
#include "states/monilith.h"
#include "states/puppeteur.h"
#include "states/scene.h"

unsigned short av = 0;
int s = 0;
int stateLastAnalog = 0;
bool stateBlock = false;

void setup() {
  Serial.begin(115200);
  Pins::setup();

  Movement::setup();
  Lights::setup();
  Controls::setup();
  Sequence::setup();

  Serial.println("Press buttons to navigate through the states");

  State::states = new State::Node[3];
  State::states[0] = sceneState;
  State::states[1] = monilithState;
  State::states[2] = puppeteurState;
  State::setup(3, 1);  // Start with the monolith state

  Network::setup();
}

void loop() {}