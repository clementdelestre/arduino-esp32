#include <Arduino.h>
#include "../../headers/animations_constructor.hpp"

#ifndef STAIRS_RAINBOW_H_INCLUDED
#define STAIRS_RAINBOW_H_INCLUDED

class LedsController;


class StairsRainbow : public AnimationConstructor {

    private:
        int dimEffect;

    public:
        StairsRainbow(LedsController* ledsController, Microphone* microphone, int flag);
        void init() override;
        void animationContent() override;

};

#endif