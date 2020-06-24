#include <Arduino.h>
#include "../../../animations_constructor.hpp"

#ifndef KAVE_MOVING_BARS_H_INCLUDED
#define KAVE_MOVING_BARS_H_INCLUDED

class LedsController;


class KaveMovingBars : public AnimationConstructor {

    private:
        int ledActivated;
        float progressColor;
        RgbColor currentColor;
        RgbColor targetColor;

        //to determine the length of the bar
        const int ratioBar = 8;

        int currentPositionBar1;
        int targetPositionBar1;

        int currentPositionBar2;
        int targetPositionBar2;

        std::chrono::milliseconds changePositionTime;

        int getRandomPosition();

    public:
        KaveMovingBars(LedsController* ledsController, Microphone* microphone, int flag);
        void animationContent() override;

};

#endif