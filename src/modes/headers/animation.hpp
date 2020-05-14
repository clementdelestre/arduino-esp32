#include <Arduino.h>
#include "mode.hpp"

#ifndef ANIMATION_MODE_H_INCLUDED
#define ANIMATION_MODE_H_INCLUDED

class LedsController;


class AnimationMode : public Mode {

    public:
        AnimationMode(LedsController* ledsController);
        void displayMode() override;

};

#endif