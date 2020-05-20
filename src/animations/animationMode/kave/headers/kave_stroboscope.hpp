#include <Arduino.h>
#include "../../../animations_constructor.hpp"

#ifndef KAVE_STROBOSCOPE_H_INCLUDED
#define KAVE_STROBOSCOPE_H_INCLUDED

class LedsController;


class KaveStroboscope : public AnimationConstructor {

    public:
        KaveStroboscope(LedsController* ledsController, Microphone* microphone, int flag);
        void animationContent() override;

};

#endif