#include "headers/kave_fire.hpp"
#include "../../../leds/leds_controller.hpp"

KaveFire::KaveFire(LedsController* ledsController, Microphone* microphone, int flag) : AnimationConstructor(ledsController, microphone, flag){  
    refreshMs = std::chrono::milliseconds(10);   

    ledsController->getKaveLeds()->clearTo(0);
    currentColor = RgbColor(255, 0, 0);
    targetColor = RgbColor(255, 255, 0);
    progressColor = 0;
}

void KaveFire::animationContent(){    
  
    float micVal = microphone->getMediumFrequency();
    

    ledsController->getKaveLeds()->shiftRight(1);

    if(micVal>0.3){
        ledsController->getKaveLeds()->setPixelColor(0, RgbColor().LinearBlend(currentColor, targetColor, progressColor).Dim(255*micVal));
    }
    
    
    for(int x = 0;x<ledsController->getKaveLeds()->getLength();x++){
        ledsController->getKaveLeds()->setPixelColor(x, ledsController->getKaveLeds()->getPixelColor(x).Dim(254));
    }
    
    ledsController->getKaveLeds()->show();

    if(progressColor >= 1){
        RgbColor oldCurrentColor = currentColor;
        currentColor = targetColor;
        targetColor = oldCurrentColor;
        progressColor = 0;
    }

    progressColor+=0.005;
 
    ledsController->getKaveLeds()->show();

}
