#include "headers/leds_controller.hpp"

/////  LEDS KAVE  /////

#define KAVE_LED_PIN 26
#define KAVE_LED_COUNT 357
NeoPixelBus<NeoGrbFeature, NeoEsp32Rmt1800KbpsMethod> kaveStrip(KAVE_LED_COUNT, KAVE_LED_PIN);

/////  END LEDS KAVE  /////

/////  LEDS STAIRS  /////

#define STAIRS_LED_PIN 27
#define STAIRS_LED_COUNT 158
NeoPixelBus<NeoGrbFeature, NeoEsp32I2s1800KbpsMethod> stairsStrip(STAIRS_LED_COUNT, STAIRS_LED_PIN);

/////  END LEDS STAIRS  /////

LedsController::LedsController(WifiManager* wifiManager){
    this->wifiManager = wifiManager;


    //create modes
    simpleColorMode = new SimpleColorsMode(this);
    animationMode = new AnimationMode(this);

    //set initial mode
    mode = simpleColorMode;

    stairsSensorValue = false;
}

void LedsController::init(){
    //initialize leds strip

    kaveStrip.Begin();
    stairsStrip.Begin();

    xTaskCreatePinnedToCore(
        ledsThread, /* Function to implement the task */
        "LEDS_CONTROLLER", /* Name of the task */
        10000,  /* Stack size in words */
        this,  /* Task input parameter */
        10,  /* Priority of the task */
        NULL,  /* Task handle. */
        0); /* Core where the task should run */

}

NeoPixelBus<NeoGrbFeature, NeoEsp32Rmt1800KbpsMethod>* LedsController::getKaveLeds(){
    return &kaveStrip;
}

NeoPixelBus<NeoGrbFeature, NeoEsp32I2s1800KbpsMethod>* LedsController::getStairsLeds(){
    return &stairsStrip;
}

Mode* LedsController::getMode(){
    return mode;
}

ModeLabel LedsController::getModeLabel(){
    return modeLabel;
}

void LedsController::setMode(ModeLabel modeLabel){
    switch (modeLabel)
    {
    case simpleColor:
        mode = simpleColorMode;
        break;
    case animations:
        mode = animationMode;
        break;
    }
}

void LedsController::ledsThread(void * parameter){

    LedsController* ledsController = (LedsController*) parameter;
    
    while(true){     
        ledsController->getMode()->displayMode();
    }

}

void LedsController::setStairsSensorValue(bool value){
    stairsSensorValue = value;
}

bool LedsController::getStairsSensorValue(){
    return stairsSensorValue;
}

