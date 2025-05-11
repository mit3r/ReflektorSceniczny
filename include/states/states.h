#include <Ticker.h>

#include "states/node.h"

#ifndef STATES_H
#define STATES_H

namespace State {

StateNode *states;

static int currentState;
static int statesCount;

void setup(int statesCount, int currentState) {  // Initialize the states array

  State::statesCount = statesCount;
  State::currentState = currentState;

  states[currentState].setupFunction();

  static Ticker ticker;
  ticker.attach_ms(11, []() { states[State::currentState].handleFunction(); });
}

unsigned short current() { return currentState; }

void nextState() {
  if (currentState + 1 >= statesCount)
    currentState = 0;
  else
    currentState++;

  if (states[currentState].setupFunction) states[currentState].setupFunction();
}

void prevState() {
  if (currentState - 1 < 0)
    currentState = statesCount - 1;
  else
    currentState--;
  if (states[currentState].setupFunction) states[currentState].setupFunction();
}

void setState(char state) {
  if (state < 0 || state >= statesCount) return;
  currentState = state;
  if (states[currentState].setupFunction) states[currentState].setupFunction();
}

}  // namespace State
#endif