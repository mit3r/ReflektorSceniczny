#include "api/theater.h"

// Class dedicated to design animations using on device controls
// Options are limited by hardware capabilities
class Designer {
  static Animation::Timeline *pointer;
  static unsigned char index;  // Current frame index

  public:
  static bool attach(Animation::Timeline *animation);
  static void detach();

  // Adds a simple frame, dedicated to using on device controls
  static bool addFrame();
  static bool addFrame(Point point, Color color, unsigned long duration, unsigned long modifiers);

  static bool clearFrames();
};