#include "headers/kave_opacity.hpp"
#include "../../../headers/leds_controller.hpp"

KaveOpacity::KaveOpacity(LedsController* ledsController, Microphone* microphone, int flag) : AnimationConstructor(ledsController, microphone, flag){  
    
    refreshMs = std::chrono::milliseconds(7);  

    color = getColorWithDefault(Utils::getRandomColor());
    
    timeColor = std::chrono::duration_cast< std::chrono::seconds >(
        Utils::getTimeSinceEpoch()
    ); 
}

void KaveOpacity::animationContent(){    
  
    for(int x = 0;x<ledsController->getKaveLeds()->PixelCount();x++){
        ledsController->getKaveLeds()->SetPixelColor(x, color.Dim(255*std::max(microphone->getMediumFrequency(), (float) 0.30)));
    }
 
    ledsController->getKaveLeds()->Show();

    if(timeColor+std::chrono::seconds(8)<Utils::getTimeSinceEpoch()){
        color = getColorWithDefault(Utils::getRandomColor());
        timeColor = std::chrono::duration_cast< std::chrono::seconds >(
            Utils::getTimeSinceEpoch()
        );
    }

}
