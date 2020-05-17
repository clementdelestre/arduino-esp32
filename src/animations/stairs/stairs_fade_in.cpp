#include "headers/stairs_fade_in.hpp"
#include "../../headers/leds_controller.hpp"

StairsFadeIn::StairsFadeIn(LedsController* ledsController, Microphone* microphone, int flag) : AnimationConstructor(ledsController, microphone, flag){
      
    init();
    refreshMs = std::chrono::milliseconds(40); 
}


void StairsFadeIn::animationContent(){
    if(progress <1){
        ledsController->getStairsLeds()->ClearTo(RgbColor().LinearBlend(0, color, progress));
        ledsController->getStairsLeds()->Show();
        progress+=0.05;
    }
}

void StairsFadeIn::init(){
    progress = 0;
    if(!ledsController->getAnimationMode()->getMainAutoColor()){
        color = ledsController->getAnimationMode()->getMainColor(); 
    } else {
        color = Utils::getRandomColor(); 
    }
}
