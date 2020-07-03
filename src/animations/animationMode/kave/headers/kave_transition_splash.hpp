#include <Arduino.h>
#include "../../../animations_constructor.hpp"

#ifndef KAVE_TRANSITION_SPLASH_H_INCLUDED
#define KAVE_TRANSITION_SPLASH_H_INCLUDED

class LedsController;


class KaveTransitionSplash : public AnimationConstructor {

    private:
        int splashPos;
        RgbColor splashColor;

    public:
        KaveTransitionSplash(LedsController* ledsController, Microphone* microphone, int flag);
        void animationContent() override;

};

#endif