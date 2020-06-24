#include "headers/leds_controller.hpp"

/////  LEDS KAVE  /////

#define KAVE_LED_PIN 26
//357
#define KAVE_LED_COUNT 66
NeoPixelBus<NeoGrbFeature, NeoEsp32Rmt1800KbpsMethod> kaveStrip(KAVE_LED_COUNT, KAVE_LED_PIN);

/////  END LEDS KAVE  /////

/////  LEDS STAIRS  /////

#define STAIRS_LED_PIN 27
//158
#define STAIRS_LED_COUNT 66
NeoPixelBus<NeoGrbFeature, NeoEsp32I2s1800KbpsMethod> stairsStrip(STAIRS_LED_COUNT, STAIRS_LED_PIN);

/////  END LEDS STAIRS  /////

LedsController::LedsController(WifiManager* wifiManager){
    this->wifiManager = wifiManager;


    //create modes
    wifiLoaderMode = new WifiLoaderMode(this);
    simpleColorMode = new SimpleColorsMode(this);
    animationMode = new AnimationMode(this);
    cineKaveMode = new CineKaveMode(this);
    offMode = new PowerOffMode(this);

    //to load initial animation
    animationMode->init();

    //set initial mode
    currentMode = wifiLoaderMode;

    stairsSensorValue = false;
    useStairsSensor = false;
}

void LedsController::init(){
    //initialize leds strip

    kaveStrip.Begin();
    stairsStrip.Begin();

    //start mode
    currentMode->startMode();

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
    
    if(modeLabel != currentMode->getModeLabel()){
        Serial.println("change mode");
        wifiManager->sendAllClientData(Flags::CHANGE_MODE, modeLabel, 0, 0);

        currentMode->stopMode();

        switch (modeLabel)
        {
        case ModeLabel::simpleColor:
            currentMode = simpleColorMode;        
            break;
        case ModeLabel::animations:
            currentMode = animationMode;
            break;
        case ModeLabel::cinekave:
            currentMode = cineKaveMode;
            break;
        case ModeLabel::off:
            currentMode = offMode;
            break;
        }

        currentMode->startMode();
    }

   currentMode->sendModeData();


}

void LedsController::ledsThread(void * parameter){

    LedsController* ledsController = (LedsController*) parameter;
    
    while(true){     
        ledsController->getCurrentMode()->displayMode();
        delay(1);
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

WifiLoaderMode* LedsController::getWifiLoaderMode(){
    return wifiLoaderMode;
}

SimpleColorsMode* LedsController::getSimpleColorMode(){
    return simpleColorMode;
}

AnimationMode* LedsController::getAnimationMode(){
    return animationMode;
}

CineKaveMode* LedsController::getCineKaveMode(){
    return cineKaveMode;
}

