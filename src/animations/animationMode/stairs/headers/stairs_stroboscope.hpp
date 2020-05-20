#include <Arduino.h>
#include "../../../animations_constructor.hpp"

#ifndef STAIRS_STROBOSCOPE_H_INCLUDED
#define STAIRS_STROBOSCOPE_H_INCLUDED

class LedsController;


class StairsStroboscope : public AnimationConstructor {

    private:
        RgbColor color;
        float progress;

    public:
        StairsStroboscope(LedsController* ledsController, Microphone* microphone, int flag);
        void init() override;
        void animationContent() override;

};

#endif