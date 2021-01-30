#include <Arduino.h>
#include "mode.hpp"

#ifndef WIFI_LOADER_MODE_H_INCLUDED
#define WIFI_LOADER_MODE_H_INCLUDED

class LedsController;


class WifiLoaderMode : public Mode {

    private:
        std::chrono::milliseconds lastAnim;
        const int lengthBar = 15;
        const RgbColor color = RgbColor(150, 150, 150);
        const RgbColor restartColor = RgbColor(150, 0, 0);

        bool restartAnim;

    public:
        WifiLoaderMode(LedsController* ledsController);
        void startMode() override;
        void displayMode() override;

        void needRestart();
};

#endif