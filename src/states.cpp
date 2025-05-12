#include "api/states.h"

// Define static members of StateManager
State *StateManager::states = nullptr;
int StateManager::currentState = 0;
int StateManager::countStates = 0;

void StateManager::setup(State *states, int countStates, int currentState) {
  StateManager::states = states;
  StateManager::countStates = countStates;
  StateManager::currentState = currentState;

  static Ticker ticker;
  states[currentState].setup();
  ticker.attach_ms(11, []() {
    if (StateManager::states == nullptr) return;
    StateManager::states[StateManager::currentState].handle();
  });
}

unsigned short StateManager::index() { return currentState; }

State StateManager::state() { return states[StateManager::currentState]; }

void StateManager::nextState() {
  states[currentState].cleanup();
  currentState = currentState + 1 >= countStates ? 0 : currentState + 1;
  states[currentState].setup();
}

void StateManager::prevState() {
  states[currentState].cleanup();
  currentState = currentState - 1 < 0 ? countStates - 1 : currentState - 1;
  states[currentState].setup();
}

void StateManager::setState(char state) {
  if (state < 0 || state >= countStates)
    return;

  states[currentState].cleanup();
  currentState = state;
  states[currentState].setup();
}