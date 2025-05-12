#include "api/sequence.h"

static Sequence* seq = nullptr;          // Pointer to the current sequence
static unsigned short currentFrame = 0;  // Current frame index

static unsigned long startTime = 0;
static unsigned short currentDelay = 0;

void Sequence::handle() {
  if (!seq) return;                                 // No sequence to handle
  if (millis() - startTime < currentDelay) return;  // Wait for the end of the frame
  if (Movement::isMoving()) return;                 // Wait for the movement to finish

  if (currentFrame >= seq->frames.size()) {
    seq->stop();  // Stop the sequence if all frames have been processed
    return;
  }

  // Update the current frame
  currentDelay = max(Movement::timeOf(seq->frames[currentFrame].point.x, seq->frames[currentFrame].point.y),
                     seq->frames[currentFrame].duration);

  Movement::moveTo(seq->frames[currentFrame].point.x, seq->frames[currentFrame].point.y, true);
  Lights::fadeTo(seq->frames[currentFrame].color, currentDelay);

  currentFrame++;        // Move to the next frame
  startTime = millis();  // Reset the start time for the next frame
}

void Sequence::setup() {
  static Ticker ticker;
  ticker.attach_ms(8, Sequence::handle);
}

const unsigned char Sequence::getSize() {
  return frames.size();  // Return the number of frames in the sequence
}

void Sequence::add(struct Color color, struct Point point) {
  Frame f;
  f.color = color;
  f.point = point;
  f.duration = 0;
  frames.push_back(f);
}

void Sequence::clear() {
  frames.clear();
}

bool Sequence::isRunning() {
  return seq != nullptr;  // Check if a sequence is currently running
}

void Sequence::stop() {
  Movement::stop();
  Lights::fadeTo({0, 0, 0}, 0);

  seq = nullptr;     // Clear the sequence pointer
  currentFrame = 0;  // Reset the current frame index
  startTime = 0;     // Reset the start time
  currentDelay = 0;  // Reset the current delay
}

void Sequence::run() {
  if (seq) return;

  currentFrame = 0;      // Reset the current frame index
  seq = this;            // Set the current sequence
  startTime = millis();  // Record the start time
}
