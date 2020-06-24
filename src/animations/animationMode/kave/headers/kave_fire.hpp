#include <Arduino.h>
#include "../../../animations_constructor.hpp"

#ifndef KAVE_FIRE_H_INCLUDED
#define KAVE_FIRE_H_INCLUDED

class LedsController;


class KaveFire : public AnimationConstructor {

    private:
        RgbColor currentColor;
        RgbColor targetColor;
        float progressColor;

    public:
        KaveFire(LedsController* ledsController, Microphone* microphone, int flag);
        void animationContent() override;

};

#endif