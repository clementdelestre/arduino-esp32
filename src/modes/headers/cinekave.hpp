#include <Arduino.h>
#include "WiFi.h"

#include "mode.hpp"

#include "../../animations/cineKaveMode/headers/waiting.hpp"
#include "../../animations/cineKaveMode/headers/playing.hpp"
#include "../../animations/cineKaveMode/headers/paused.hpp"

#ifndef CINEKAVE_MODE_H_INCLUDED
#define CINEKAVE_MODE_H_INCLUDED

enum CinePlayMode {
    WAITING = 0,
    PLAYING = 1,
    PAUSED = 2
};

class LedsController;

class CineKaveMode : public Mode {

    private:
        bool resetStairsSensorValue;

        bool isConnected;
        RgbColor screenColor;
        int luminosity;
        AnimationConstructor* currentAnimation;

        WiFiClient* computerClient;

        std::chrono::milliseconds timeCheckComputer;

    public:
        CineKaveMode(LedsController* ledsController);
        void displayMode() override; 
        void startMode() override;
        void stopMode() override;
        void sendModeData() override;

        void setComputerClient(WiFiClient* computerClient);
        bool getConnectionState();

        int getPlayMode();
        void setPlayMode(int playMode);

        void setScreenColor(RgbColor screenColor);
        RgbColor getScreenColor();

        void setLuminosity(int luminosity);
        int getLuminosity();

        
};

#endif