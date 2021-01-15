#include "headers/kave_off.hpp"
#include "../../../leds/leds_controller.hpp"

KaveOff::KaveOff(LedsController* ledsController, Microphone* microphone, int flag) : AnimationConstructor(ledsController, microphone, flag){  
    refreshMs = std::chrono::milliseconds(100);   
}

void KaveOff::animationContent(){    
  
    ledsController->getKaveLeds()->clearTo(0);
    ledsController->getKaveLeds()->show();

}
