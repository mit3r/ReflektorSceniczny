#include "config/pinout.h"
#include "utils.h"

#ifndef ANIMATION_H
#define ANIMATION_H

namespace Animation {

const unsigned char MAX_FRAMES = 20;                            // Maximum number of frames in an animation
const unsigned long MASK_DURATION = (unsigned long)0x0FFFFFFF;  // Duration mask [28 bits]
const unsigned long MASK_MODIFIER = (unsigned long)0xF0000000;  // Modifier mask [4 bits]

enum Modifier {
  WAITFORCOMMAND = (unsigned long)0x20000000,  // Wait for command [3rd most significant bit]
  KEEP_POSITION = (unsigned long)0x40000000,   // Don't change position [2nd most significant bit]
  KEEP_LIGHT = (unsigned long)0x80000000,      // Don't change light [1st most significant bit]
};

struct Frame {
  unsigned long modifier;
  struct Color color;
  struct Point point;
};

struct Timeline {
  unsigned char size;        // Number of frames in the animation [0, 255]
  Frame frames[MAX_FRAMES];  // Pointer to the array of frames
};

}  // namespace Animation
#endif  // ANIMATION_H