#include "api/chooser.h"

Chooser::Chooser(char count, char start) {
  this->count = count;
  this->start = start;
  this->curr = start;
}

char Chooser::current() {
  return curr;
}

void Chooser::nextChoice() {
  curr = (curr >= count - 1) ? 0 : curr + 1;
}

void Chooser::previousChoice() {
  curr = (curr <= 0) ? count - 1 : curr - 1;
}

void Chooser::reset() {
  curr = start;
}

// Define chooser here
Chooser chooser(5, 0);