#include <NeoPixelBus.h>
#include <chrono>

#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

enum ModeLabel {simpleColor = 0, animations = 1, cinekave = 2, off = 3,  wifiLoader = 4};

class Utils {

    public:
        static std::chrono::milliseconds getTimeSinceEpoch();
        static RgbColor getRandomColor();
        static RgbColor getFixedRandomColor();
        static int kaveNumAnimation;
        static RgbColor cineDefaultColor;

};

#endif