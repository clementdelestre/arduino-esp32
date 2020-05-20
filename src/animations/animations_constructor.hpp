#include <Arduino.h>
#include <NeoPixelBus.h>
#include "../utils/headers/utils.hpp"
#include "../utils/headers/microphone.hpp"

#ifndef ANIMATION_CONSTRUCTOR_H_INCLUDED
#define ANIMATION_CONSTRUCTOR_H_INCLUDED

class LedsController;


class AnimationConstructor {

    private:
        std::chrono::milliseconds pauseDelay;

    protected:
        LedsController *ledsController;
        Microphone* microphone;
        std::chrono::milliseconds refreshMs;

        RgbColor getColorWithDefault(RgbColor color);
        int flag;


    public:
        AnimationConstructor(LedsController* ledsController);
        AnimationConstructor(LedsController* ledsController, Microphone* microphone, int flag);
        virtual void init();
        virtual void eventClose();

        void displayAnimation();
        virtual void animationContent();

        int getFlag();

};

#endif