#include <Arduino.h>
#include "../../headers/animations_constructor.hpp"

#ifndef KAVE_GRADIENT_FROM_EDGES_H_INCLUDED
#define KAVE_GRADIENT_FROM_EDGES_H_INCLUDED

class LedsController;


class KaveGradientFromEdges : public AnimationConstructor {

    private:       
        RgbColor colorFrom;
        RgbColor colorTo;
        int position;

    public:
        KaveGradientFromEdges(LedsController* ledsController, Microphone* microphone, int flag);
        void animationContent() override;

};

#endif