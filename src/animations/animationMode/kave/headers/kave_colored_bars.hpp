#include <Arduino.h>
#include "../../../animations_constructor.hpp"

#ifndef KAVE_COLORED_BARS_H_INCLUDED
#define KAVE_COLORED_BARS_H_INCLUDED

class LedsController;


class KaveColoredBars : public AnimationConstructor {

    private:       
        RgbColor barCurrentColor;
        RgbColor barTargetColor;    

        float colorProgress; 
        //10 in the Kave
        const int lengthBar = 6;   

    public:
        KaveColoredBars(LedsController* ledsController, Microphone* microphone, int flag);
        void animationContent() override;

};

#endif