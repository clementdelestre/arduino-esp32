#include <Arduino.h>
#include "mode.hpp"

#ifndef TRANSITION_MODE_H_INCLUDED
#define TRANSITION_MODE_H_INCLUDED

class LedsController;


class TransitionMode : public Mode {

    private:
        RgbColor initColor;
        RgbColor targetColor;

        uint8_t countTransition;
        int speed;
        float progress;
        int index;
        
        std::vector<RgbColor> colors = {};

    public:
        TransitionMode(LedsController* ledsController);
        void displayMode() override; 
        void startMode() override;

        void loadTransition();

        void sendModeData() override;

        void changeAnimationSpeed(int speed);

};

#endif