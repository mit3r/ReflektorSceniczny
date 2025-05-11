

#include <Arduino.h>
#include <Ticker.h>
#include <lights.h>

#include "controls.h"
#include "movement.h"
#include "network.h"
#include "pinout.h"
//
#include "states/states.h"
//
#include "states/_monilith.h"
#include "states/_puppeteur.h"
#include "states/_scene.h"

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

  State::states = new StateNode[3];
  State::states[0] = sceneState;
  State::states[1] = monilithState;
  State::states[2] = puppeteurState;
  State::setup(3, 1);  // Start with the monolith state

  Network::setup();
}

void loop() {}