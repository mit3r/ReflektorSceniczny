

#ifndef UTILS_H
#define UTILS_H

// Color with RGB values in [0, 255]
struct Color {
  unsigned char r, g, b;
};

// Point with coordinates in [-32768, 32767]
struct Point {
  short x, y;
};

template <typename T>
int sgn(T val) {
  return (T(0) < val) - (val < T(0));
}

#endif  // UTILS_H