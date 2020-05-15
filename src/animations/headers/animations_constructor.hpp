#include <Arduino.h>
#include <NeoPixelBus.h>
#include "../../utils/headers/utils.hpp"
#include "../../utils/headers/microphone.hpp"

#ifndef ANIMATION_CONSTRUCTOR_H_INCLUDED
#define ANIMATION_CONSTRUCTOR_H_INCLUDED

class LedsController;


class AnimationConstructor {

    private:
        std::chrono::milliseconds delay;
        int flag;

    protected:
        LedsController *ledsController;
        Microphone* microphone;
        std::chrono::milliseconds refreshMs;


    public:
        
        AnimationConstructor(LedsController* ledsController, Microphone* microphone, int flag);
        virtual void init();

        void displayAnimation();
        virtual void animationContent();

        int getFlag();

};

#endif