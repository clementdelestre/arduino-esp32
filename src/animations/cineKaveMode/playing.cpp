#include "headers/playing.hpp"
#include "../../headers/leds_controller.hpp"

PlayingCineKaveAnim::PlayingCineKaveAnim(LedsController* ledsController) : AnimationConstructor(ledsController){  
    this->flag = CinePlayMode::PLAYING;
    refreshMs = std::chrono::milliseconds(10);
}

void PlayingCineKaveAnim::animationContent(){    
    ledsController->getKaveLeds()->ClearTo(ledsController->getCineKaveMode()->getScreenColor());
    ledsController->getKaveLeds()->Show(); 
}
