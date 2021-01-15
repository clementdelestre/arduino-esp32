#include "headers/kave_stroboscope.hpp"
#include "../../../leds/leds_controller.hpp"

KaveStroboscope::KaveStroboscope(LedsController* ledsController, Microphone* microphone, int flag) : AnimationConstructor(ledsController, microphone, flag){  
    
    refreshMs = std::chrono::milliseconds(20);   
}

void KaveStroboscope::animationContent(){   

    int luminosity = ledsController->getAnimationMode()->getStroboscopeLuminosity(); 
  
    ledsController->getKaveLeds()->clearTo(RgbColor(luminosity, luminosity, luminosity));
    ledsController->getKaveLeds()->show();
    delay(5);

    ledsController->getKaveLeds()->clearTo(0);
    ledsController->getKaveLeds()->show();

    int delayTime = 240-ledsController->getAnimationMode()->getStroboscopeSpeed();
    refreshMs = std::chrono::milliseconds(delayTime);

}

