#include <Arduino.h>
#include <arduinoFFT.h>
#include "../network/wifi/wifi_controller.hpp"
#include "../utils/headers/utils.hpp"

#include "../storage/nvs.hpp"

#include "components/ledsStrip.hpp"

#include "modes/headers/mode.hpp"
#include "modes/headers/wifi_loader.hpp"
#include "modes/headers/simple_colors.hpp"
#include "modes/headers/animation.hpp"
#include "modes/headers/cinekave.hpp"
#include "modes/headers/power_off.hpp"
#include "modes/headers/transition.hpp"

//SENSOR
#define STAIRS_SENSOR 14

#ifndef LEDS_CONTROLLER_H_INCLUDED
#define LEDS_CONTROLLER_H_INCLUDED


class LedsController {

    private:
        WifiController* wifiController;
        Mode* currentMode;
        ModeLabel modeLabel;

        NVSStorage* nvsStorage;

        WifiLoaderMode* wifiLoaderMode;
        SimpleColorsMode* simpleColorMode;
        AnimationMode* animationMode;
        CineKaveMode* cineKaveMode;
        PowerOffMode* offMode;
        TransitionMode* transitionMode;

        LedsStrip* kaveStrip;
        LedsStrip* stairsStrip;

        bool stairsSensorValue;
        bool useStairsSensor;

        static void ledsThread(void * parameter);

    public:
        LedsController(WifiController* WifiController, NVSStorage* storage);
        void init();

        Mode* getCurrentMode();
        void setMode(int modeLabel);

        LedsStrip* getKaveLeds();
        LedsStrip* getStairsLeds();

        WifiController* getWifiManager();

        void setUseStairsSensor(bool value);
        bool getUseStairsSensor();

        bool canShowStairs();

        WifiLoaderMode* getWifiLoaderMode();
        SimpleColorsMode* getSimpleColorMode();
        AnimationMode* getAnimationMode();
        CineKaveMode* getCineKaveMode();
        TransitionMode* getTransitionMode();

        NVSStorage* getNVSStorage();
};



#endif