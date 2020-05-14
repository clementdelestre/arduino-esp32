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
    currentMode = simpleColorMode;

    stairsSensorValue = false;
    useStairsSensor = false;
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

WifiManager* LedsController::getWifiManager(){
    return wifiManager;
}

void LedsController::setMode(int modeLabel){
    Serial.println("change mode");
    wifiManager->sendAllClientData(Flags::CHANGE_MODE, modeLabel, 0, 0);
    switch (modeLabel)
    {
    case ModeLabel::simpleColor:
        currentMode = simpleColorMode;
        simpleColorMode->sendModeData();
        break;
    case ModeLabel::animations:
        currentMode = animationMode;
        break;
    case ModeLabel::cinekave:
        currentMode = animationMode;
    case ModeLabel::off:
        currentMode = animationMode;
    }
}

void LedsController::ledsThread(void * parameter){

    LedsController* ledsController = (LedsController*) parameter;
    
    while(true){     
        ledsController->getCurrentMode()->displayMode();
    }

}

//STAIRS SENSOR

void LedsController::setUseStairsSensor(bool value){
    useStairsSensor = value;
    wifiManager->sendAllClientData(Flags::SENSOR_STAIRS, value ? 1 : 0, 0, 0);
}

bool LedsController::getUseStairsSensor(){
    return useStairsSensor;
}

bool LedsController::canShowStairs(){
    return !useStairsSensor || digitalRead(STAIRS_SENSOR) == 1;
}

//GET MODES

Mode* LedsController::getCurrentMode(){
    return currentMode;
}

SimpleColorsMode* LedsController::getSimpleColorMode(){
    return simpleColorMode;
}

AnimationMode* LedsController::getAnimationMode(){
    return animationMode;
}

