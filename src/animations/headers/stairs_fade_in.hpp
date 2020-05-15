#include <Arduino.h>
#include "animations_constructor.hpp"

#ifndef STAIRS_FADE_IN_H_INCLUDED
#define STAIRS_FADE_IN_H_INCLUDED

class LedsController;


class StairsFadeIn : public AnimationConstructor {

    private:
        RgbColor color;
        float progress;

    public:
        StairsFadeIn(LedsController* ledsController, Microphone* microphone, int flag);
        void init() override;
        void animationContent() override;

};

#endif