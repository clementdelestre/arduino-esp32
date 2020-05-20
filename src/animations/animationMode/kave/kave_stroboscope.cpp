#include "headers/kave_stroboscope.hpp"
#include "../../../headers/leds_controller.hpp"

KaveStroboscope::KaveStroboscope(LedsController* ledsController, Microphone* microphone, int flag) : AnimationConstructor(ledsController, microphone, flag){  
    
    refreshMs = std::chrono::milliseconds(20);   
}

void KaveStroboscope::animationContent(){    
  
    ledsController->getKaveLeds()->ClearTo(RgbColor(255, 255, 255));
    ledsController->getKaveLeds()->Show();
    delay(5);

    ledsController->getKaveLeds()->ClearTo(0);
    ledsController->getKaveLeds()->Show();

    int delayTime = 245-ledsController->getAnimationMode()->getStroboscopeSpeed();
    refreshMs = std::chrono::milliseconds(delayTime);

}

