#include <Ticker.h>

#ifndef STATES_H
#define STATES_H

struct State {
  void (*setup)();
  void (*handle)();
  void (*cleanup)();
};

class StateManager {
  private:
  static State *states;
  static int currentState;
  static int countStates;

  public:
  static void setup(State *states, int countStates, int currentState = 0);

  static unsigned short index();
  static State state();

  static void nextState();
  static void prevState();
  static void setState(char state);
};

#endif