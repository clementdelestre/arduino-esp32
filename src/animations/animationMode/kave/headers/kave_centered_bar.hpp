#include <Arduino.h>
#include "../../../animations_constructor.hpp"

#ifndef KAVE_CENTERED_BAR_H_INCLUDED
#define KAVE_CENTERED_BAR_H_INCLUDED

class LedsController;


class KaveCenteredBar : public AnimationConstructor {

    private:       
        int ledActivated;
        float progressColor;
        RgbColor currentColor;
        RgbColor targetColor;

    public:
        KaveCenteredBar(LedsController* ledsController, Microphone* microphone, int flag);
        void animationContent() override;

};

#endif