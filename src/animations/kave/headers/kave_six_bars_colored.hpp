#include <Arduino.h>
#include "../../headers/animations_constructor.hpp"

#ifndef SIX_BARS_COLORED_H_INCLUDED
#define SIX_BARS_COLORED_H_INCLUDED

class LedsController;


class SixBarsColored : public AnimationConstructor {

    private:       
        RgbColor backColor;
        int section;

    public:
        SixBarsColored(LedsController* ledsController, Microphone* microphone, int flag);
        void animationContent() override;

};

#endif