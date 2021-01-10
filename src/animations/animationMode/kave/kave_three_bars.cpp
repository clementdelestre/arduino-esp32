#include "headers/kave_three_bars.hpp"
#include "../../../headers/leds_controller.hpp"

KaveThreeBars::KaveThreeBars(LedsController* ledsController, Microphone* microphone, int flag) : AnimationConstructor(ledsController, microphone, flag){  
    refreshMs = std::chrono::milliseconds(10);   

    ledActivatedLow = 0;
    currentColorLow = RgbColor(0, 0, 0);
    targetColorLow = Utils::getRandomColor();

    ledActivatedHigh = 0;
    currentColorHigh = RgbColor(0, 0, 0);
    targetColorHigh = Utils::getRandomColor();

    progressColor = 0;
}

void KaveThreeBars::animationContent(){    
  
    //LOW FREQUENCY   
    int activeLedTargetLow = ledsController->getKaveLeds()->PixelCount()*microphone->getLowFrequency()/6;

    if(ledActivatedLow <= activeLedTargetLow){
        ledActivatedLow+=1;
    } else {
        ledActivatedLow-=1;
    }

    for(int x = ledsController->getKaveLeds()->PixelCount()/6; x>=ledActivatedLow; x--){
        ledsController->getKaveLeds()->SetPixelColor(ledsController->getKaveLeds()->PixelCount()/2+x, 0);    
        ledsController->getKaveLeds()->SetPixelColor(ledsController->getKaveLeds()->PixelCount()/2-x, 0);   
    }
    
    RgbColor tempColorLow = RgbColor().LinearBlend(currentColorLow, targetColorLow, progressColor);
    for(int x = 0;x<ledActivatedLow;x++){      
        ledsController->getKaveLeds()->SetPixelColor(ledsController->getKaveLeds()->PixelCount()/2+x, tempColorLow);
        ledsController->getKaveLeds()->SetPixelColor(ledsController->getKaveLeds()->PixelCount()/2-x, tempColorLow);
    }

    //fix
    ledsController->getKaveLeds()->SetPixelColor(ledsController->getKaveLeds()->PixelCount()/2, tempColorLow);

    //HIGH FREQUENCY
    int activeLedTargetHigh = ledsController->getKaveLeds()->PixelCount()*microphone->getHighFrequency()/6;

    if(ledActivatedHigh <= activeLedTargetHigh){
        ledActivatedHigh+=1;
    } else {
        ledActivatedHigh-=1;
    }

    for(int x = ledsController->getKaveLeds()->PixelCount()/6; x>=ledActivatedHigh; x--){
        ledsController->getKaveLeds()->SetPixelColor(ledsController->getKaveLeds()->PixelCount()/6+x, 0);    
        ledsController->getKaveLeds()->SetPixelColor(ledsController->getKaveLeds()->PixelCount()/6-x, 0);

        ledsController->getKaveLeds()->SetPixelColor(ledsController->getKaveLeds()->PixelCount()*5/6+x, 0);    
        ledsController->getKaveLeds()->SetPixelColor(ledsController->getKaveLeds()->PixelCount()*5/6-x, 0);   
    }
    
    RgbColor tempColorHigh = RgbColor().LinearBlend(currentColorHigh, targetColorHigh, progressColor);
    for(int x = 0;x<ledActivatedHigh;x++){        
        ledsController->getKaveLeds()->SetPixelColor(ledsController->getKaveLeds()->PixelCount()/6+x, tempColorHigh);
        ledsController->getKaveLeds()->SetPixelColor(ledsController->getKaveLeds()->PixelCount()/6-x, tempColorHigh);

        ledsController->getKaveLeds()->SetPixelColor(ledsController->getKaveLeds()->PixelCount()*5/6+x, tempColorHigh);
        ledsController->getKaveLeds()->SetPixelColor(ledsController->getKaveLeds()->PixelCount()*5/6-x, tempColorHigh);
    }

    //fix
    ledsController->getKaveLeds()->SetPixelColor(ledsController->getKaveLeds()->PixelCount()/6, tempColorHigh);
    ledsController->getKaveLeds()->SetPixelColor(ledsController->getKaveLeds()->PixelCount()*5/6, tempColorHigh);

    //GENERAL
    progressColor+=0.005;

    if(progressColor>1){
        currentColorLow = targetColorLow;
        targetColorLow = Utils::getRandomColor();

        currentColorHigh = targetColorHigh;
        targetColorHigh = getColorWithDefault(Utils::getRandomColor());

        progressColor = 0;
    }
 
    ledsController->getKaveLeds()->Show();

}

void KaveThreeBars::init(){
    ledsController->getKaveLeds()->ClearTo(0);
    ledsController->getKaveLeds()->Show();
}
