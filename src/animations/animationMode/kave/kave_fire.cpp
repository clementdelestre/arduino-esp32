#include "headers/kave_fire.hpp"
#include "../../../headers/leds_controller.hpp"

KaveFire::KaveFire(LedsController* ledsController, Microphone* microphone, int flag) : AnimationConstructor(ledsController, microphone, flag){  
    refreshMs = std::chrono::milliseconds(10);   

    ledsController->getKaveLeds()->ClearTo(0);
    currentColor = RgbColor(255, 0, 0);
    targetColor = RgbColor(255, 255, 0);
    progressColor = 0;
}

void KaveFire::animationContent(){    
  
    float micVal = microphone->getMediumFrequency();

    ledsController->getKaveLeds()->ShiftRight(1);

    if(micVal>0.3){
        ledsController->getKaveLeds()->SetPixelColor(0, RgbColor().LinearBlend(currentColor, targetColor, progressColor).Dim(255*micVal));
    }
    
    
    for(int x = 0;x<ledsController->getKaveLeds()->PixelCount();x++){
        ledsController->getKaveLeds()->SetPixelColor(x, ledsController->getKaveLeds()->GetPixelColor(x).Dim(254));
    }
    
    ledsController->getKaveLeds()->Show();

    if(progressColor >= 1){
        RgbColor oldCurrentColor = currentColor;
        currentColor = targetColor;
        targetColor = oldCurrentColor;
        progressColor = 0;
    }

    progressColor+=0.005;
 
    ledsController->getKaveLeds()->Show();

}
