

#ifndef STATES_NODE_H
#define STATES_NODE_H

struct StateNode {
  void (*setupFunction)();
  void (*handleFunction)();
};

#endif