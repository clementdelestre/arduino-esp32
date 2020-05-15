#include <Arduino.h>
#include "animations_constructor.hpp"

#ifndef WHITE_DOTS_H_INCLUDED
#define WHITE_DOTS_H_INCLUDED

class LedsController;


class WhiteDots : public AnimationConstructor {

    private:       
        RgbColor backColor;

    public:
        WhiteDots(LedsController* ledsController, Microphone* microphone, int flag);
        void animationContent() override;

};

#endif