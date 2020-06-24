#include <Arduino.h>
#include "../../../animations_constructor.hpp"

#ifndef KAVE_SIDE_BARSH_INCLUDED
#define KAVE_SIDE_BARSH_INCLUDED

class LedsController;


class KaveSideBars : public AnimationConstructor {

    private:
        int ledActivated;
        float progressColor;
        RgbColor currentColor;
        RgbColor targetColor;

    public:
        KaveSideBars(LedsController* ledsController, Microphone* microphone, int flag);
        void animationContent() override;

};

#endif