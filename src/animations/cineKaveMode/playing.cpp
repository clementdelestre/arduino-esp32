#include "headers/playing.hpp"
#include "../../headers/leds_controller.hpp"

PlayingCineKaveAnim::PlayingCineKaveAnim(LedsController* ledsController) : AnimationConstructor(ledsController){  
    this->flag = CinePlayMode::PLAYING;

    refreshMs = std::chrono::milliseconds(50);  

}

void PlayingCineKaveAnim::animationContent(){    

    ledsController->getKaveLeds()->ClearTo(RgbColor(0, 255, 0));
    ledsController->getKaveLeds()->Show(); 
    

}
