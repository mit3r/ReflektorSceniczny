#include "config/pinout.h"
#include "interfaces/controls.h"
#include "interfaces/lights.h"
#include "interfaces/movement.h"
#include "utils.h"
#include "vector"

#ifndef SEQUENCE_H
#define SEQUENCE_H

struct Frame {
  struct Color color;
  struct Point point;
  unsigned long duration;
};

class Sequence {
  private:
  static void handle();

  public:
  std::vector<Frame> frames;
  static const unsigned char maxFrames = 24;  // Maximum number of frames in the sequence
  static void setup();

  Sequence() { frames.reserve(24); }                              // Reserve space for frames to avoid reallocations}
  Sequence(std::vector<Frame> frames) { this->frames = frames; }  // Constructor with initial frames

  const unsigned char getSize();                     // Get the number of frames in the sequence
  void add(struct Color color, struct Point point);  // Add a frame to the sequence
  void clear();                                      // Clear the sequence frames

  static bool isRunning();  // Check if the sequence is running
  static void stop();       // Stop the sequence
  void run();               // Run the sequence
};

#endif  // SEQUENCE_H