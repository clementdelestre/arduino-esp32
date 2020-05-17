#include <Arduino.h>
#include "../../headers/animations_constructor.hpp"

#ifndef KAVE_CHANGE_COLOR_H_INCLUDED
#define KAVE_CHANGE_COLOR_H_INCLUDED

class LedsController;


class KaveChangeColor : public AnimationConstructor {

    private:       
        RgbColor color;

    public:
        KaveChangeColor(LedsController* ledsController, Microphone* microphone, int flag);
        void animationContent() override;

};

#endif