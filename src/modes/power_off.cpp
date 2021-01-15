#include "headers/power_off.hpp"

#include "../leds/leds_controller.hpp"

PowerOffMode::PowerOffMode(LedsController* ledsController) : Mode(ledsController){
     this->ledsController = ledsController;
     this->modeLabel = ModeLabel::off;
}

void PowerOffMode::startMode(){
     ledsController->getKaveLeds()->clearTo(0);
     ledsController->getKaveLeds()->show();

     ledsController->getStairsLeds()->clearTo(0);
     ledsController->getStairsLeds()->show();
}

void PowerOffMode::displayMode(){
     delay(100);
}

