#include "api/queue.h"
#include "config/animation.h"
#include "config/pinout.h"
#include "interfaces/controls.h"
#include "interfaces/lights.h"
#include "interfaces/movement.h"
#include "utils.h"
#include "vector"

#ifndef THEATER_H
#define THEATER_H

class Theater {
  private:
  constexpr static const unsigned long MAX_QUEUE = 10;  // Maximum number of animations in the queue
  static Queue<Animation::Timeline> queue;              // Queue of animations

  static unsigned char index;  // Current frame of the animation
  static bool animating;       // Current animation status

  static void handle();

  public:
  static void setup();

  // Save, Enqueue & Run the animation
  static bool run(Animation::Timeline animation);

  // Stop the animation
  static void skip();

  // Check if the animation is running
  static bool isAnimating();
};

#endif  // THEATER_H