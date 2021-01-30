#include "headers/kave_moving_bars.hpp"
#include "../../../leds/leds_controller.hpp"

KaveMovingBars::KaveMovingBars(LedsController* ledsController, Microphone* microphone, int flag) : AnimationConstructor(ledsController, microphone, flag){  
    refreshMs = std::chrono::milliseconds(6);   

    ledActivated = 0;
    progressColor = 0;
    currentColor = RgbColor(0, 0, 0);
    targetColor = Utils::getRandomColor();

    currentPositionBar1 = ledsController->getKaveLeds()->getLength()/2;
    currentPositionBar2 = ledsController->getKaveLeds()->getLength()/2;
    changePositionTime = Utils::getTimeSinceEpoch();

    targetPositionBar1 = getRandomPosition();
    targetPositionBar2 = getRandomPosition();
}

void KaveMovingBars::animationContent(){    
  
    ledsController->getKaveLeds()->clearTo(0);

    int activeLedTarget = ledsController->getKaveLeds()->getLength()*microphone->getLowFrequency()/ratioBar;

    if(changePositionTime + std::chrono::milliseconds(17) < Utils::getTimeSinceEpoch()){
        if(currentPositionBar1 < targetPositionBar1){
            currentPositionBar1++;
        } else {
            currentPositionBar1--;
        }

        if(currentPositionBar2 < targetPositionBar2){
            currentPositionBar2++;
        } else {
            currentPositionBar2--;
        }
        changePositionTime = Utils::getTimeSinceEpoch();
    }
    

    RgbColor activeColor = RgbColor().LinearBlend(currentColor, targetColor, progressColor);

    if(ledActivated <= activeLedTarget){
        ledActivated+=2;
    } else {
        ledActivated-=2;
    }
    
    for(int x = 0;x<ledActivated;x++){
        ledsController->getKaveLeds()->setPixelColor(currentPositionBar1+x, activeColor);
        ledsController->getKaveLeds()->setPixelColor(currentPositionBar1-x, activeColor);

        ledsController->getKaveLeds()->setPixelColor(currentPositionBar2+x, activeColor);
        ledsController->getKaveLeds()->setPixelColor(currentPositionBar2-x, activeColor);
    }

    progressColor+=0.005;

    if(progressColor>1){
        currentColor = targetColor;
        targetColor = Utils::getRandomColor();
        progressColor = 0;
    }
 
    ledsController->getKaveLeds()->show();

    if(currentPositionBar1 == targetPositionBar1){
        targetPositionBar1 = getRandomPosition();
    }

    if(currentPositionBar2 == targetPositionBar2){
        targetPositionBar2 = getRandomPosition();
    }

    if(ledActivated <= activeLedTarget){
        refreshMs = std::chrono::milliseconds(4); 
    } else {
        refreshMs = std::chrono::milliseconds(6); 
    }

}


int KaveMovingBars::getRandomPosition(){
    return ledsController->getKaveLeds()->getLength()/ratioBar + random(ledsController->getKaveLeds()->getLength()-ledsController->getKaveLeds()->getLength()/(ratioBar/2));
}
