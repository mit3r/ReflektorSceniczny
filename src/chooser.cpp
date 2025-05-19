#include "api/chooser.h"

Chooser::Chooser(unsigned char count, unsigned char start) {
  this->count = count;
  this->start = start;
  this->curr = start;
}

unsigned char Chooser::current() {
  return curr;
}

void Chooser::nextChoice() {
  if (curr >= count - 1)
    curr = 0;
  else
    curr++;
}

void Chooser::previousChoice() {
  if (curr == 0)
    curr = count - 1;
  else
    curr--;
}

void Chooser::reset() {
  curr = start;
}