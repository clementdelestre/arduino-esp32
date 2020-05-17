#include "animations/headers/animations_constructor.hpp"

#include "../headers/leds_controller.hpp"

AnimationConstructor::AnimationConstructor(LedsController* ledsController, Microphone* microphone, int flag){
    this->ledsController = ledsController;
    this->microphone = microphone;
    this->flag = flag;
    pauseDelay =  Utils::getTimeSinceEpoch();
    refreshMs = std::chrono::milliseconds(40);
}

void AnimationConstructor::init(){
    
}

void AnimationConstructor::eventClose(){
    
}

void AnimationConstructor::displayAnimation(){

    if(pauseDelay+refreshMs > Utils::getTimeSinceEpoch()) return;
    animationContent();
    pauseDelay =  Utils::getTimeSinceEpoch();

}

void AnimationConstructor::animationContent(){

}

int AnimationConstructor::getFlag(){
    return flag;
}

RgbColor AnimationConstructor::getColorWithDefault(RgbColor color){
    if(!ledsController->getAnimationMode()->getMainAutoColor()){
        return ledsController->getAnimationMode()->getMainColor(); 
    } else {
        return color;
    }
}