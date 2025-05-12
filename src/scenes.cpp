#include "config/scenes.h"

Sequence *blinkWhite = new Sequence(std::vector<Frame>{
    {Color{255, 255, 255}, Point{0, 0}, 200},
    {Color{255, 255, 255}, Point{0, 0}, 0},
    {Color{255, 255, 255}, Point{0, 0}, 200},
    {Color{255, 255, 255}, Point{0, 0}, 0},
    {Color{0, 0, 0}, Point{0, 0}, 100},
});

Sequence *blinkYellow = new Sequence(std::vector<Frame>{
    {Color{255, 255, 0}, Point{0, 0}, 200},
    {Color{255, 255, 0}, Point{0, 0}, 0},
    {Color{255, 255, 0}, Point{0, 0}, 200},
    {Color{255, 255, 0}, Point{0, 0}, 0},
    {Color{0, 0, 0}, Point{0, 0}, 100},
});

Sequence *blinkBlue = new Sequence(std::vector<Frame>{
    {Color{0, 0, 255}, Point{0, 0}, 200},
    {Color{0, 0, 255}, Point{0, 0}, 0},
    {Color{0, 0, 255}, Point{0, 0}, 200},
    {Color{0, 0, 255}, Point{0, 0}, 0},
    {Color{0, 0, 0}, Point{0, 0}, 100},
});

Sequence *predefinedRedSeq = new Sequence(std::vector<Frame>{
    {Color{255, 0, 0}, Point{0, 0}, 500},
    {Color{255, 0, 0}, Point{-45, 0}, 0},
    {Color{0, 255, 0}, Point{-45, 0}, 500},
    {Color{0, 255, 0}, Point{45, 0}, 0},
    {Color{0, 0, 255}, Point{45, 0}, 500},
    {Color{0, 0, 255}, Point{45, 0}, 0},
    {Color{0, 0, 0}, Point{0, 0}, 0},
});

Sequence *predefinedGreenSeq = new Sequence(std::vector<Frame>{
    {Color{255, 0, 0}, Point{0, 0}, 500},
    {Color{255, 0, 0}, Point{-45, 0}, 0},
    {Color{0, 255, 0}, Point{-45, 0}, 500},
    {Color{0, 255, 0}, Point{45, 0}, 0},
    {Color{0, 0, 255}, Point{45, 0}, 500},
    {Color{0, 0, 255}, Point{45, 0}, 0},
    {Color{0, 0, 0}, Point{0, 0}, 0},
});

Sequence *customBlueSeq = new Sequence();  // Empty sequence