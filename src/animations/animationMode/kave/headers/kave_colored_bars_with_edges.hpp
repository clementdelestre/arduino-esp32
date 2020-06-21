#include <Arduino.h>
#include "../../../animations_constructor.hpp"

#ifndef KAVE_COLORED_BARS_WITH_EDGES_H_INCLUDED
#define KAVE_COLORED_BARS_WITH_EDGES_H_INCLUDED

class LedsController;


class KaveColoredBarsWithEdges : public AnimationConstructor {

    private:       
        RgbColor edgesCurrentColor;
        RgbColor edgesTargetColor;

        RgbColor barCurrentColor;
        RgbColor barTargetColor;    

        float colorProgress; 
        const int lengthBar = 5; 

    public:
        KaveColoredBarsWithEdges(LedsController* ledsController, Microphone* microphone, int flag);
        void animationContent() override;

};

#endif