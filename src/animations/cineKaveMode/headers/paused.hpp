#include <Arduino.h>
#include "../../animations_constructor.hpp"

#ifndef PAUSED_CINEKAVE_H_INCLUDED
#define PAUSED_CINEKAVE_H_INCLUDED

class LedsController;


class PausedCineKaveAnim : public AnimationConstructor {

    private:
        RgbColor defaultColor;
        RgbColor currentColor;
        float progressColor;

    public:
        PausedCineKaveAnim(LedsController* ledsController);
        void animationContent() override;

};

#endif