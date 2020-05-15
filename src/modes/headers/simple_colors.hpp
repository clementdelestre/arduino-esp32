#include <Arduino.h>
#include "mode.hpp"

#ifndef SIMPLE_COLORS_MODE_H_INCLUDED
#define SIMPLE_COLORS_MODE_H_INCLUDED

class LedsController;


class SimpleColorsMode : public Mode {

    private:
        bool isAnimated;
        int animationSpeed;
        RgbColor animInitColor;

        RgbColor kaveCurrentColor;
        RgbColor stairsCurrentColor;

        //stairs enable
        float posStairsColor;
        bool isStairsDisplayed;
        
        //Animation
        float posColor;
        RgbColor targetColor;

    public:
        SimpleColorsMode(LedsController* ledsController);
        void displayMode() override; 
        void startMode() override;

        void setKaveColor(RgbColor color);
        void setStairsColor(RgbColor color);

        void sendModeData() override;

        void changeAnimated(bool animated);
        void changeAnimationSpeed(int speed);

};

#endif