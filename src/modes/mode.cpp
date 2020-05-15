#include "headers/mode.hpp"

#include "../headers/leds_controller.hpp"


Mode::Mode(LedsController *LedsController){
    this->ledsController = ledsController;
}

void Mode::init(){
    
}

void Mode::displayMode(){
    Serial.println("Wrong function");
    delay(1000);
}

void Mode::startMode(){
    
}

void Mode::stopMode(){
    
}

void Mode::sendModeData(){

}

ModeLabel Mode::getModeLabel(){
    return modeLabel;
}
