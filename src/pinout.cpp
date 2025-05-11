#include "pinout.h"

namespace Pins {

void setup() {
  pinMode(DIRECTION, OUTPUT);
  pinMode(PAN_STEP, OUTPUT);
  pinMode(TILT_STEP, OUTPUT);

  pinMode(TILT_LIMIT, INPUT);

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  pinMode(BUTTON0, INPUT);
  pinMode(BUTTON1, INPUT);
  pinMode(ANALOG, INPUT);
}
}  // namespace Pins