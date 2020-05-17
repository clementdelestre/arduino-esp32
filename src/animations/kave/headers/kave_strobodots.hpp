#include <Arduino.h>
#include "../../headers/animations_constructor.hpp"

#ifndef KAVE_STROBODOTS_H_INCLUDED
#define KAVE_STROBODOTS_H_INCLUDED

class LedsController;


class KaveStrobodots : public AnimationConstructor {

    private:       
        const int maxLeds = 7;

    public:
        KaveStrobodots(LedsController* ledsController, Microphone* microphone, int flag);
        void animationContent() override;

};

#endif