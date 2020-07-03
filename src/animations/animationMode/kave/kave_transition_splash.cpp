#include "headers/kave_transition_splash.hpp"
#include "../../../headers/leds_controller.hpp"

KaveTransitionSplash::KaveTransitionSplash(LedsController* ledsController, Microphone* microphone, int flag) : AnimationConstructor(ledsController, microphone, flag){  
    refreshMs = std::chrono::milliseconds(10);   

    ledsController->getKaveLeds()->ClearTo(0);
    ledsController->getKaveLeds()->Show();
    
    splashPos = 0;
    splashColor = getColorWithDefault(Utils::getFixedRandomColor());
}

void KaveTransitionSplash::animationContent(){    
  
    if(splashPos<=ledsController->getKaveLeds()->PixelCount()/2.5){
        for(int x = 0;x<=splashPos;x++){

            RgbColor ledColor = RgbColor().LinearBlend(splashColor, 0, min( (float) (splashPos-x)/ (float) splashPos*1.5, (double) 1));

            ledsController->getKaveLeds()->SetPixelColor(ledsController->getKaveLeds()->PixelCount()/2+x, ledColor);
            ledsController->getKaveLeds()->SetPixelColor(ledsController->getKaveLeds()->PixelCount()/2-x, ledColor);  
        } 
        splashPos+=1;
    } else {
        for(int x = 0;x<ledsController->getKaveLeds()->PixelCount();x++){

            RgbColor ledColor = ledsController->getKaveLeds()->GetPixelColor(x).Dim(220);

            ledsController->getKaveLeds()->SetPixelColor(ledsController->getKaveLeds()->PixelCount()/2+x, ledColor);
            ledsController->getKaveLeds()->SetPixelColor(ledsController->getKaveLeds()->PixelCount()/2-x, ledColor);  
        }

        if(ledsController->getKaveLeds()->GetPixelColor(ledsController->getKaveLeds()->PixelCount()/2.5) == 0){
            ledsController->getAnimationMode()->nextKaveAnimation();
        }
    }
      
    ledsController->getKaveLeds()->Show();

}
