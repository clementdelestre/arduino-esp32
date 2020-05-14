#include <Arduino.h>
#include <arduinoFFT.h>
#include <NeoPixelBus.h>
#include "headers/wifi_manager.hpp"
#include "utils.hpp"

#include "modes/headers/mode.hpp"
#include "modes/headers/simple_colors.hpp"
#include "modes/headers/animation.hpp"

//SENSOR
#define STAIRS_SENSOR 14

#ifndef LEDS_CONTROLLER_H_INCLUDED
#define LEDS_CONTROLLER_H_INCLUDED


class LedsController {

    private:
        WifiManager *wifiManager;
        Mode* currentMode;
        ModeLabel modeLabel;

        SimpleColorsMode* simpleColorMode;
        AnimationMode* animationMode;

        bool stairsSensorValue;
        bool useStairsSensor;

        static void ledsThread(void * parameter);

    public:
        LedsController(WifiManager* wifiManager);
        void init();

        Mode* getCurrentMode();
        void setMode(int modeLabel);

        NeoPixelBus<NeoGrbFeature, NeoEsp32Rmt1800KbpsMethod> *getKaveLeds();
        NeoPixelBus<NeoGrbFeature, NeoEsp32I2s1800KbpsMethod> *getStairsLeds();

        WifiManager* getWifiManager();

        void setUseStairsSensor(bool value);
        bool getUseStairsSensor();

        bool canShowStairs();

        SimpleColorsMode* getSimpleColorMode();
        AnimationMode* getAnimationMode();
};



#endif