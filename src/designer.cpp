#include "api/designer.h"

Animation::Timeline* Designer::pointer = nullptr;
unsigned char Designer::index = 0;

bool Designer::attach(Animation::Timeline* animation) {
  pointer = animation;
  index = 0;
  return pointer != nullptr;
}

void Designer::detach() {
  pointer = nullptr;
  index = 0;
}

bool Designer::addFrame() {
  return addFrame(Movement::getTargetAngle(), Lights::getTargetColor(), 0, 0);
}

bool Designer::addFrame(Point point, Color color, unsigned long duration, unsigned long modifiers) {
  if (pointer == nullptr) return false;
  if (pointer->size >= Animation::MAX_FRAMES) return false;

  pointer->frames[pointer->size++] = {
      .modifier = (modifiers & Animation::MASK_MODIFIER) | (duration & Animation::MASK_DURATION),
      .color = color,
      .point = point,
  };

  return true;
}

bool Designer::clearFrames() {
  if (pointer == nullptr) return false;

  pointer->size = 0;
  for (unsigned char i = 0; i < Animation::MAX_FRAMES; i++) {
    pointer->frames[i] = {
        .modifier = 0,
        .color = {0, 0, 0},
        .point = {0, 0},
    };
  }

  return true;
}
