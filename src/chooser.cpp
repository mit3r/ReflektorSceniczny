#include "api/chooser.h"

Chooser::Chooser(char count, char start) {
  this->count = count;
  this->curr = start;
}

char Chooser::current() const {
  return curr;
}

void Chooser::nextChoice() {
  curr = (curr >= count - 1) ? 0 : curr + 1;
}

void Chooser::previousChoice() {
  curr = (curr <= 0) ? count - 1 : curr - 1;
}
