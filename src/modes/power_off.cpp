#include "headers/power_off.hpp"

#include "../headers/leds_controller.hpp"

PowerOffMode::PowerOffMode(LedsController* ledsController) : Mode(ledsController){
     this->ledsController = ledsController;
     this->modeLabel = ModeLabel::off;
}

void PowerOffMode::startMode(){
     ledsController->getKaveLeds()->ClearTo(0);
     ledsController->getKaveLeds()->Show();

     ledsController->getStairsLeds()->ClearTo(0);
     ledsController->getStairsLeds()->Show();
}

void PowerOffMode::displayMode(){
     delay(100);
}

