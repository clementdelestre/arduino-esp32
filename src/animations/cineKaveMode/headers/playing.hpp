#include <Arduino.h>
#include "../../animations_constructor.hpp"

#ifndef PLAYING_CINEKAVE_H_INCLUDED
#define PLAYING_CINEKAVE_H_INCLUDED

class LedsController;


class PlayingCineKaveAnim : public AnimationConstructor {

    public:
        PlayingCineKaveAnim(LedsController* ledsController);
        void animationContent() override;

};

#endif