#include "headers/kave_strobodots.hpp"
#include "../../../leds/leds_controller.hpp"

KaveStrobodots::KaveStrobodots(LedsController* ledsController, Microphone* microphone, int flag) : AnimationConstructor(ledsController, microphone, flag){  

    refreshMs = std::chrono::milliseconds(50);   
}

void KaveStrobodots::animationContent(){    
  
    ledsController->getKaveLeds()->clearTo(0);
    
    int countLeds = maxLeds*microphone->getMediumFrequency();

    for(int x = 0; x<countLeds;x++){
        int position = 1+random(ledsController->getKaveLeds()->getLength()-2);

        RgbColor color = getColorWithDefault(Utils::getFixedRandomColor());
        
        ledsController->getKaveLeds()->setPixelColor(position-1, color);
        ledsController->getKaveLeds()->setPixelColor(position, color);
        ledsController->getKaveLeds()->setPixelColor(position+1, color);
    }

    ledsController->getKaveLeds()->show();

}
