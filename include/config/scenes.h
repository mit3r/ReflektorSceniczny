#include "config/animation.h"

using namespace Animation;

#ifndef SCENES_H
#define SCENES_H

Animation::Timeline createStillAnimation(Color color, unsigned long duration);

Animation::Timeline createBlinkAnimation(Color color, unsigned long upTime, unsigned long downTime, unsigned char times);

Animation::Timeline createResetPositionAnimation();

inline constexpr unsigned char scenesCount = 4;
extern Animation::Timeline scenesTimelines[scenesCount];
extern Color scenesColors[scenesCount];

#endif  // PREDEFINED_H