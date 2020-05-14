#include <Arduino.h>
#include <arduinoFFT.h>
#include <NeoPixelBus.h>
#include "headers/wifi_manager.hpp"
#include "utils.hpp"

#include "modes/headers/mode.hpp"
#include "modes/headers/simple_colors.hpp"
#include "modes/headers/animation.hpp"

#ifndef LEDS_CONTROLLER_H_INCLUDED
#define LEDS_CONTROLLER_H_INCLUDED


class LedsController {

    private:
        WifiManager *wifiManager;
        Mode* mode;
        ModeLabel modeLabel;

        SimpleColorsMode* simpleColorMode;
        AnimationMode* animationMode;

        bool stairsSensorValue;

        static void ledsThread(void * parameter);

    public:
        LedsController(WifiManager* wifiManager);
        void init();

        Mode* getMode();
        ModeLabel getModeLabel();
        void setMode(ModeLabel modeLabel);

        NeoPixelBus<NeoGrbFeature, NeoEsp32Rmt1800KbpsMethod> *getKaveLeds();
        NeoPixelBus<NeoGrbFeature, NeoEsp32I2s1800KbpsMethod> *getStairsLeds();

        void setStairsSensorValue(bool value);
        bool getStairsSensorValue();
};



#endif