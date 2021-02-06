#include "headers/playing.hpp"
#include "../../leds/leds_controller.hpp"

PlayingCineKaveAnim::PlayingCineKaveAnim(LedsController* ledsController) : AnimationConstructor(ledsController){  
    this->flag = CinePlayMode::PLAYING;
    refreshMs = std::chrono::milliseconds(5);


    lastUpdate = Utils::getTimeSinceEpoch();
    currentColor = RgbColor(0);
    targetColor = ledsController->getCineKaveMode()->getScreenColor();
}

void PlayingCineKaveAnim::animationContent(){

    float progress = (float)(Utils::getTimeSinceEpoch() - lastUpdate).count()/(float)50; //20 is the refresh rate of java program
    RgbColor color = RgbColor().LinearBlend(currentColor, targetColor, progress);

    //ledsController->getKaveLeds()->clearTo(ledsController->getCineKaveMode()->getScreenColor().Dim(ledsController->getCineKaveMode()->getLuminosity()*255/100));

    ledsController->getKaveLeds()->clearTo(color.Dim(ledsController->getCineKaveMode()->getLuminosity()*255/100));
    ledsController->getKaveLeds()->show(); 

    if(progress >= 1){
        currentColor = targetColor; 
        targetColor = ledsController->getCineKaveMode()->getScreenColor();
        lastUpdate = Utils::getTimeSinceEpoch();
    }
}
