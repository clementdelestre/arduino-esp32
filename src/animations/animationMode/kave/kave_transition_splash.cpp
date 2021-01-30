#include "headers/kave_transition_splash.hpp"
#include "../../../leds/leds_controller.hpp"

KaveTransitionSplash::KaveTransitionSplash(LedsController* ledsController, Microphone* microphone, int flag) : AnimationConstructor(ledsController, microphone, flag){  
    refreshMs = std::chrono::milliseconds(10);   

    ledsController->getKaveLeds()->clearTo(0);
    ledsController->getKaveLeds()->show();
    
    splashPos = 0;
    splashColor = getColorWithDefault(Utils::getFixedRandomColor());
}

void KaveTransitionSplash::animationContent(){    
  
    if(splashPos<=ledsController->getKaveLeds()->getLength()/2.5){
        for(int x = 0;x<=splashPos;x++){

            RgbColor ledColor = RgbColor().LinearBlend(splashColor, 0, min( (float) (splashPos-x)/ (float) splashPos*1.5, (double) 1));

            ledsController->getKaveLeds()->setPixelColor(ledsController->getKaveLeds()->getLength()/2+x, ledColor);
            ledsController->getKaveLeds()->setPixelColor(ledsController->getKaveLeds()->getLength()/2-x, ledColor);  
        } 
        splashPos+=2;
    } else {
        for(int x = 0;x<ledsController->getKaveLeds()->getLength();x++){

            RgbColor ledColor = ledsController->getKaveLeds()->getPixelColor(x).Dim(220);

            ledsController->getKaveLeds()->setPixelColor(ledsController->getKaveLeds()->getLength()/2+x, ledColor);
            ledsController->getKaveLeds()->setPixelColor(ledsController->getKaveLeds()->getLength()/2-x, ledColor);  
        }

        if(ledsController->getKaveLeds()->getPixelColor(ledsController->getKaveLeds()->getLength()/2.5) == 0){
            ledsController->getAnimationMode()->nextKaveAnimation();
        }
    }
      
    ledsController->getKaveLeds()->show();

}

void KaveTransitionSplash::init(){
    ledsController->getKaveLeds()->clearTo(0);
    ledsController->getKaveLeds()->show();
}