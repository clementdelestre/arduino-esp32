#include <Arduino.h>
#include "../../animations_constructor.hpp"

#ifndef WAITING_CINEKAVE_H_INCLUDED
#define WAITING_CINEKAVE_H_INCLUDED

class LedsController;


class WaitingCineKaveAnim : public AnimationConstructor {

    private:
        RgbColor defaultColor;
        RgbColor currentColor;
        float progressColor;

    public:
        WaitingCineKaveAnim(LedsController* ledsController);
        void animationContent() override;

};

#endif