#include "headers/stairs_fade_in.hpp"
#include "../../../leds/leds_controller.hpp"

StairsFadeIn::StairsFadeIn(LedsController* ledsController, Microphone* microphone, int flag) : AnimationConstructor(ledsController, microphone, flag){
      
    init();
    refreshMs = std::chrono::milliseconds(40); 
}


void StairsFadeIn::animationContent(){
    if(progress <1){
        ledsController->getStairsLeds()->clearTo(RgbColor().LinearBlend(0, color, progress));
        ledsController->getStairsLeds()->show();
        progress+=0.05;
    }

    if(progress == 1){
        refreshMs = std::chrono::milliseconds(100); ;
    }
}

void StairsFadeIn::init(){
    progress = 0;
    if(!ledsController->getAnimationMode()->getMainAutoColor()){
        color = ledsController->getAnimationMode()->getMainColor(); 
    } else {
        color = Utils::getFixedRandomColor(); 
    }
}
