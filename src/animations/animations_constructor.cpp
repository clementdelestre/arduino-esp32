#include "animations/headers/animations_constructor.hpp"

AnimationConstructor::AnimationConstructor(LedsController* ledsController, Microphone* microphone, int flag){
    this->ledsController = ledsController;
    this->microphone = microphone;
    this->flag = flag;
    delay =  Utils::getTimeSinceEpoch();
    refreshMs = std::chrono::milliseconds(40);
}

void AnimationConstructor::init(){
    
}

void AnimationConstructor::displayAnimation(){

    if(delay+refreshMs > Utils::getTimeSinceEpoch()) return;
    animationContent();
    delay =  Utils::getTimeSinceEpoch();

}

void AnimationConstructor::animationContent(){

}

int AnimationConstructor::getFlag(){
    return flag;
}