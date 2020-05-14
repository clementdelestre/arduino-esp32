#include "headers/simple_colors.hpp"

#include "../headers/leds_controller.hpp"

SimpleColorsMode::SimpleColorsMode(LedsController* ledsController) : Mode(ledsController){
     this->ledsController = ledsController;
     isAnimated = false;
     kaveColor = RgbColor(255, 255, 255);
     stairsColor = RgbColor(255, 255, 255);     
}


void SimpleColorsMode::displayMode(){
     delay(1000);
}
