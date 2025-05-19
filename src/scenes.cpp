#include "config/scenes.h"

Animation::Timeline createStillAnimation(Color color, unsigned long duration) {
  return {
      .size = 1,
      .frames = {
          {(duration & MASK_DURATION) | Modifier::KEEP_POSITION, color, Point{0, 0}},
      },
  };
}

Animation::Timeline createBlinkAnimation(Color color, unsigned long upTime, unsigned long downTime, unsigned char times) {
  Animation::Timeline animation;
  animation.size = times * 2 + 1;
  for (unsigned char i = 0; i < times; i++) {
    animation.frames[i * 2].modifier = (upTime & MASK_DURATION) | Animation::Modifier::KEEP_POSITION;
    animation.frames[i * 2].color = color;
    animation.frames[i * 2].point = {0, 0};
    animation.frames[i * 2 + 1].modifier = (downTime & MASK_DURATION) | Animation::Modifier::KEEP_POSITION;
    animation.frames[i * 2 + 1].color = {0, 0, 0};
    animation.frames[i * 2 + 1].point = {0, 0};
  }
  return animation;
}

Animation::Timeline createResetPositionAnimation() {
  return {
      .size = 1,
      .frames = {
          {0 | Modifier::KEEP_LIGHT, Color{0, 0, 0}, Point{0, 0}},
      },
  };
}

Animation::Timeline scenesTimelines[scenesCount] = {
    {
        .size = 4,
        .frames = {
            {0, Color{255, 255, 255}, Point{-45, -45}},
            {0, Color{255, 255, 255}, Point{45, -45}},
            {0, Color{255, 255, 255}, Point{45, 45}},
            {0, Color{255, 255, 255}, Point{-45, 45}},
        },
    },
    {
        .size = 12,
        .frames = {
            {0, Color{0, 0, 0}, Point{0, 0}},
            {0, Color{0, 0, 0}, Point{-45, 0}},
            {1 | KEEP_POSITION, Color{255, 0, 0}, Point{0, 0}},

            {0, Color{0, 0, 0}, Point{0, 0}},
            {0, Color{0, 0, 0}, Point{0, -45}},
            {1 | KEEP_POSITION, Color{0, 255, 0}, Point{0, 0}},

            {0, Color{0, 0, 0}, Point{0, 0}},
            {0, Color{0, 0, 0}, Point{45, 0}},
            {1 | KEEP_POSITION, Color{0, 0, 255}, Point{0, 0}},

            {0, Color{0, 0, 0}, Point{0, 0}},
            {0, Color{0, 0, 0}, Point{0, 45}},
            {1 | KEEP_POSITION, Color{255, 255, 0}, Point{0, 0}},

        },
    },
    {
        .size = 2,
        .frames = {
            {0, Color{255, 0, 0}, Point{-45, -45}},
            {0, Color{0, 255, 0}, Point{45, 45}},
        },
    },
    {
        .size = 0,
        .frames = {},
    },
};

Color scenesColors[scenesCount] = {
    {255, 0, 0},    // Red
    {0, 255, 0},    // Green
    {255, 255, 0},  // Yellow
    {0, 0, 255},    // Blue
};