#include <Arduino.h>
#include "../../../animations_constructor.hpp"

#ifndef KAVE_OFF_H_INCLUDED
#define KAVE_OFF_H_INCLUDED

class LedsController;


class KaveOff : public AnimationConstructor {

    public:
        KaveOff(LedsController* ledsController, Microphone* microphone, int flag);
        void animationContent() override;

};

#endif