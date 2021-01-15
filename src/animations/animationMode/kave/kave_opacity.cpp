#include "headers/kave_opacity.hpp"
#include "../../../leds/leds_controller.hpp"

KaveOpacity::KaveOpacity(LedsController* ledsController, Microphone* microphone, int flag) : AnimationConstructor(ledsController, microphone, flag){  
    
    refreshMs = std::chrono::milliseconds(7);  

    color = getColorWithDefault(Utils::getRandomColor());
    
    timeColor = std::chrono::duration_cast< std::chrono::seconds >(
        Utils::getTimeSinceEpoch()
    ); 
}

void KaveOpacity::animationContent(){    
  
    for(int x = 0;x<ledsController->getKaveLeds()->getLength();x++){
        ledsController->getKaveLeds()->setPixelColor(x, color.Dim(255*std::max(microphone->getMediumFrequency(), (float) 0.30)));
    }
 
    ledsController->getKaveLeds()->show();

    if(timeColor+std::chrono::seconds(8)<Utils::getTimeSinceEpoch()){
        color = getColorWithDefault(Utils::getRandomColor());
        timeColor = std::chrono::duration_cast< std::chrono::seconds >(
            Utils::getTimeSinceEpoch()
        );
    }

}
