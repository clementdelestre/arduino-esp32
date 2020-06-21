#include "headers/kave_centered_bar.hpp"
#include "../../../headers/leds_controller.hpp"

KaveCenteredBar::KaveCenteredBar(LedsController* ledsController, Microphone* microphone, int flag) : AnimationConstructor(ledsController, microphone, flag){  

    refreshMs = std::chrono::milliseconds(20);    

    ledActivated = 0;
    progressColor = 0;
    currentColor = RgbColor(0, 0, 0);
    targetColor = getColorWithDefault(Utils::getFixedRandomColor());
}

void KaveCenteredBar::animationContent(){    
  
    int activeLedTarget = ledsController->getKaveLeds()->PixelCount()*microphone->getMediumFrequency()/2;

    if(activeLedTarget == 0) activeLedTarget = 1;

    RgbColor activeColor = RgbColor().LinearBlend(currentColor, targetColor, progressColor);
    RgbColor inactiveColor = activeColor.Dim(10);

    if(ledActivated <= activeLedTarget){
        ledActivated+=3;
    } else {
        ledActivated-=3;
    }

    for(int x = ledsController->getKaveLeds()->PixelCount()/2; x>=ledActivated && x>2; x--){
        ledsController->getKaveLeds()->SetPixelColor(ledsController->getKaveLeds()->PixelCount()/2+x, inactiveColor);    
        ledsController->getKaveLeds()->SetPixelColor(ledsController->getKaveLeds()->PixelCount()/2-x, inactiveColor);   
    }
    
    for(int x = 0;x<ledActivated;x++){
        ledsController->getKaveLeds()->SetPixelColor(ledsController->getKaveLeds()->PixelCount()/2+x, activeColor);
        ledsController->getKaveLeds()->SetPixelColor(ledsController->getKaveLeds()->PixelCount()/2-x, activeColor);
    }

    progressColor+=0.005;

    if(progressColor>1){
        currentColor = targetColor;
        targetColor = getColorWithDefault(Utils::getFixedRandomColor());
        progressColor = 0;
    }
 
    ledsController->getKaveLeds()->Show();

    if(ledActivated <= activeLedTarget){
        refreshMs = std::chrono::milliseconds(20);
    } else {
        refreshMs = std::chrono::milliseconds(40);
    }

}
