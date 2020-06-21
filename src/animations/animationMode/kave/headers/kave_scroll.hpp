#include <Arduino.h>
#include "../../../animations_constructor.hpp"

#ifndef KAVE_SCROLL_H_INCLUDED
#define KAVE_SCROLL_H_INCLUDED

class LedsController;


class KaveScroll : public AnimationConstructor {

    private:
        std::chrono::milliseconds lastSpawn;

    public:
        KaveScroll(LedsController* ledsController, Microphone* microphone, int flag);
        void animationContent() override;

};

#endif