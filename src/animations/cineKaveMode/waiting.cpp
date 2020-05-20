#include "headers/waiting.hpp"
#include "../../headers/leds_controller.hpp"

WaitingCineKaveAnim::WaitingCineKaveAnim(LedsController* ledsController) : AnimationConstructor(ledsController){  
    this->flag = CinePlayMode::WAITING;

    refreshMs = std::chrono::milliseconds(20);  
    defaultColor = RgbColor(255, 0, 255); 
    currentColor = 0;

    progressColor = 0;
}

void WaitingCineKaveAnim::animationContent(){    

    if(progressColor<1){
        progressColor+=0.05;
        currentColor = RgbColor().LinearBlend(0, defaultColor, progressColor);
    }
    
    ledsController->getKaveLeds()->ClearTo(currentColor);
    ledsController->getKaveLeds()->Show(); 
    

    if(ledsController->canShowStairs()){
        ledsController->getStairsLeds()->ClearTo(currentColor);
        ledsController->getStairsLeds()->Show();
    } else {
        ledsController->getStairsLeds()->ClearTo(0);
        ledsController->getStairsLeds()->Show();
    }
    

}
