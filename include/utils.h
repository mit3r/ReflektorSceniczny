

#ifndef UTILS_H
#define UTILS_H

struct Color {
  unsigned char r, g, b;
};

struct Point {
  short x, y;  // x and y coordinates (pan and tilt angles)
};

template <typename T>
int sgn(T val) {
  return (T(0) < val) - (val < T(0));
}

#endif  // UTILS_H