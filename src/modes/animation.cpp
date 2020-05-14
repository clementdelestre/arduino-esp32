#include "headers/animation.hpp"

#include "../headers/leds_controller.hpp"

AnimationMode::AnimationMode(LedsController* ledsController) : Mode(ledsController){
       this->ledsController = ledsController;
}


void AnimationMode::displayMode(){
     delay(1000);
}
