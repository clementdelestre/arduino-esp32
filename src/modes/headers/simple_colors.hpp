#include <Arduino.h>
#include "mode.hpp"

#ifndef SIMPLE_COLORS_MODE_H_INCLUDED
#define SIMPLE_COLORS_MODE_H_INCLUDED

class LedsController;


class SimpleColorsMode : public Mode {

    private:
        bool isAnimated;
        RgbColor kaveColor;
        RgbColor stairsColor;
        

    public:
        SimpleColorsMode(LedsController* ledsController);
        void displayMode() override;

};

#endif