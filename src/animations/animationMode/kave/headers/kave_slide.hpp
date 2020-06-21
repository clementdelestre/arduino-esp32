#include <Arduino.h>
#include "../../../animations_constructor.hpp"

#ifndef KAVE_SLIDE_H_INCLUDED
#define KAVE_SLIDE_H_INCLUDED

class LedsController;


class KaveSlide : public AnimationConstructor {

    private:
        std::chrono::seconds lastMove;

    public:
        KaveSlide(LedsController* ledsController, Microphone* microphone, int flag);
        void animationContent() override;

};

#endif