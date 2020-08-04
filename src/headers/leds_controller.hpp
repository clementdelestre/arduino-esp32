#include <Arduino.h>
#include <arduinoFFT.h>
#include <NeoPixelBus.h>
#include "../utils/headers/wifi_controller.hpp"
#include "../utils/headers/utils.hpp"

#include "modes/headers/mode.hpp"
#include "modes/headers/wifi_loader.hpp"
#include "modes/headers/simple_colors.hpp"
#include "modes/headers/animation.hpp"
#include "modes/headers/cinekave.hpp"
#include "modes/headers/power_off.hpp"

//SENSOR
#define STAIRS_SENSOR 14

#ifndef LEDS_CONTROLLER_H_INCLUDED
#define LEDS_CONTROLLER_H_INCLUDED


class LedsController {

    private:
        WifiController* wifiController;
        Mode* currentMode;
        ModeLabel modeLabel;

        WifiLoaderMode* wifiLoaderMode;
        SimpleColorsMode* simpleColorMode;
        AnimationMode* animationMode;
        CineKaveMode* cineKaveMode;
        PowerOffMode* offMode;

        bool stairsSensorValue;
        bool useStairsSensor;

        static void ledsThread(void * parameter);

    public:
        LedsController(WifiController* WifiController);
        void init();

        Mode* getCurrentMode();
        void setMode(int modeLabel);

        NeoPixelBus<NeoGrbFeature, NeoEsp32Rmt1800KbpsMethod> *getKaveLeds();
        NeoPixelBus<NeoGrbFeature, NeoEsp32I2s1800KbpsMethod> *getStairsLeds();

        WifiController* getWifiManager();

        void setUseStairsSensor(bool value);
        bool getUseStairsSensor();

        bool canShowStairs();

        WifiLoaderMode* getWifiLoaderMode();
        SimpleColorsMode* getSimpleColorMode();
        AnimationMode* getAnimationMode();
        CineKaveMode* getCineKaveMode();
};



#endif