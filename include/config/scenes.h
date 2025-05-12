#include "api/sequence.h"

#ifndef PREDEFINED_H
#define PREDEFINED_H

auto *blinkWhite = new Sequence(std::vector<Frame>{
    {Color{255, 255, 255}, Point{0, 0}, 200},
    {Color{255, 255, 255}, Point{0, 0}, 0},
    {Color{255, 255, 255}, Point{0, 0}, 200},
    {Color{255, 255, 255}, Point{0, 0}, 0},
    {Color{0, 0, 0}, Point{0, 0}, 100},
});

auto *blinkYellow = new Sequence(std::vector<Frame>{
    {Color{255, 255, 0}, Point{0, 0}, 200},
    {Color{255, 255, 0}, Point{0, 0}, 0},
    {Color{255, 255, 0}, Point{0, 0}, 200},
    {Color{255, 255, 0}, Point{0, 0}, 0},
    {Color{0, 0, 0}, Point{0, 0}, 100},
});

auto *blinkBlue = new Sequence(std::vector<Frame>{
    {Color{0, 0, 255}, Point{0, 0}, 200},
    {Color{0, 0, 255}, Point{0, 0}, 0},
    {Color{0, 0, 255}, Point{0, 0}, 200},
    {Color{0, 0, 255}, Point{0, 0}, 0},
    {Color{0, 0, 0}, Point{0, 0}, 100},
});

auto *predefinedRedSeq = new Sequence(std::vector<Frame>{
    {Color{255, 0, 0}, Point{0, 0}, 500},  // 500 sekund koloru czerownego
    {Color{255, 0, 0}, Point{-45, 0}, 0},
    {Color{0, 255, 0}, Point{-45, 0}, 500},
    {Color{0, 255, 0}, Point{45, 0}, 0},
    {Color{0, 0, 255}, Point{45, 0}, 500},
    {Color{0, 0, 255}, Point{45, 0}, 0},
    {Color{0, 0, 0}, Point{0, 0}, 0},
});

auto *predefinedGreenSeq = new Sequence(std::vector<Frame>{
    {Color{255, 0, 0}, Point{0, 0}, 500},  // 500 sekund koloru czerownego
    {Color{255, 0, 0}, Point{-45, 0}, 0},
    {Color{0, 255, 0}, Point{-45, 0}, 500},
    {Color{0, 255, 0}, Point{45, 0}, 0},
    {Color{0, 0, 255}, Point{45, 0}, 500},
    {Color{0, 0, 255}, Point{45, 0}, 0},
    {Color{0, 0, 0}, Point{0, 0}, 0},
});

auto *customBlueSeq = new Sequence();  // Empty sequence

#endif  // PREDEFINED_H