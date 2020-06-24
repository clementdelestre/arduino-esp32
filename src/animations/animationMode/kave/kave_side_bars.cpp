#include "headers/kave_side_bars.hpp"
#include "../../../headers/leds_controller.hpp"

KaveSideBars::KaveSideBars(LedsController* ledsController, Microphone* microphone, int flag) : AnimationConstructor(ledsController, microphone, flag){  
    refreshMs = std::chrono::milliseconds(6);   

    ledActivated = 0;
    progressColor = 0;
    currentColor = RgbColor(0, 0, 0);
    targetColor = Utils::getRandomColor();
}

void KaveSideBars::animationContent(){    
  
    int activeLedTarget = ledsController->getKaveLeds()->PixelCount()*microphone->getLowFrequency()/2;

    RgbColor activeColor = RgbColor().LinearBlend(currentColor, targetColor, progressColor);
    RgbColor inactiveColor = activeColor.Dim(10);

    if(ledActivated <= activeLedTarget){
        ledActivated+=3;
    } else {
        ledActivated-=3;
    }

    for(int x = ledsController->getKaveLeds()->PixelCount()/2; x>=ledActivated; x--){
        ledsController->getKaveLeds()->SetPixelColor(x, inactiveColor);    
        ledsController->getKaveLeds()->SetPixelColor(ledsController->getKaveLeds()->PixelCount()-x, inactiveColor);   
    }
    
    for(int x = 0;x<ledActivated;x++){
        ledsController->getKaveLeds()->SetPixelColor(x, activeColor);
        ledsController->getKaveLeds()->SetPixelColor(ledsController->getKaveLeds()->PixelCount()-x, activeColor);
    }

    progressColor+=0.005;

    if(progressColor>1){
        currentColor = targetColor;
        targetColor = getColorWithDefault(Utils::getRandomColor());
        progressColor = 0;
    }
 
    ledsController->getKaveLeds()->Show();

    if(ledActivated <= activeLedTarget){
        refreshMs = std::chrono::milliseconds(4);
    } else {
        refreshMs = std::chrono::milliseconds(6);
    }

}
