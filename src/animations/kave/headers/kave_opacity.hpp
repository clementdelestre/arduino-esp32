#include <Arduino.h>
#include "../../headers/animations_constructor.hpp"

#ifndef KAVE_OPACITY_H_INCLUDED
#define KAVE_OPACITY_H_INCLUDED

class LedsController;

class KaveOpacity : public AnimationConstructor {

    private:       
        int ledActivated;
        std::chrono::seconds timeColor;
        RgbColor color;

    public:
        KaveOpacity(LedsController* ledsController, Microphone* microphone, int flag);
        void animationContent() override;

};

#endif