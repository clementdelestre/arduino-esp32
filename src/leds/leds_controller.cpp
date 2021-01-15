#include "leds_controller.hpp"


/////  LEDS KAVE  /////

#define KAVE_LED_PIN 26
#define KAVE_LED_COUNT 25 //371

#define STAIRS_LED_PIN 27
#define STAIRS_LED_COUNT 25 //104

/////  END LEDS STAIRS  /////

LedsController::LedsController(WifiController* wifiController){
    this->wifiController = wifiController;

    kaveStrip = new LedsStrip(KAVE_LED_COUNT, KAVE_LED_PIN, 0);
    stairsStrip = new LedsStrip(STAIRS_LED_COUNT, STAIRS_LED_PIN, 1);

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

LedsStrip* LedsController::getKaveLeds(){
    return kaveStrip;
}

LedsStrip* LedsController::getStairsLeds(){
    return stairsStrip;
}

WifiController* LedsController::getWifiManager(){
    return wifiController;
}

void LedsController::setMode(int modeLabel){
    
    if(modeLabel != currentMode->getModeLabel()){
        Serial.println("change mode");
        wifiController->sendAllClientData(Flags::CHANGE_MODE, modeLabel, 0, 0);

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
    wifiController->sendAllClientData(Flags::SENSOR_STAIRS, value ? 1 : 0, 0, 0);
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

