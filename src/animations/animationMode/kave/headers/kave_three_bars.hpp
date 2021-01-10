#include <Arduino.h>
#include "../../../animations_constructor.hpp"

#ifndef KAVE_THREE_BARS_H_INCLUDED
#define KAVE_THREE_BARS_H_INCLUDED

class LedsController;


class KaveThreeBars : public AnimationConstructor {

    private:
        int ledActivatedLow;
        RgbColor currentColorLow;
        RgbColor targetColorLow;

        int ledActivatedHigh;
        RgbColor currentColorHigh;
        RgbColor targetColorHigh;

        float progressColor;

    public:
        KaveThreeBars(LedsController* ledsController, Microphone* microphone, int flag);
        void animationContent() override;
        void init() override;

};

#endif