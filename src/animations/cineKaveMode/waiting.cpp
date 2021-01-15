#include "headers/waiting.hpp"
#include "../../leds/leds_controller.hpp"

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
    
    ledsController->getKaveLeds()->clearTo(currentColor);
    ledsController->getKaveLeds()->show(); 
    

    if(ledsController->canShowStairs()){
        ledsController->getStairsLeds()->clearTo(currentColor);
        ledsController->getStairsLeds()->show();
    } else {
        ledsController->getStairsLeds()->clearTo(0);
        ledsController->getStairsLeds()->show();
    }
    

}
