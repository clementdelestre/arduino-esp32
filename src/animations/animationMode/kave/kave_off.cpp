#include "headers/kave_off.hpp"
#include "../../../headers/leds_controller.hpp"

KaveOff::KaveOff(LedsController* ledsController, Microphone* microphone, int flag) : AnimationConstructor(ledsController, microphone, flag){  
    refreshMs = std::chrono::milliseconds(100);   
}

void KaveOff::animationContent(){    
  
    ledsController->getKaveLeds()->ClearTo(0);
    ledsController->getKaveLeds()->Show();

}
