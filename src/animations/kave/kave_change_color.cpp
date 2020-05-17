#include "headers/kave_change_color.hpp"
#include "../../headers/leds_controller.hpp"

KaveChangeColor::KaveChangeColor(LedsController* ledsController, Microphone* microphone, int flag) : AnimationConstructor(ledsController, microphone, flag){  
    refreshMs = std::chrono::milliseconds(100);    
    color = Utils::getRandomColor();  

    ledsController->getKaveLeds()->ClearTo(color); 
    ledsController->getKaveLeds()->Show();
}

void KaveChangeColor::animationContent(){   
     
   if(microphone->getLowFrequency()>0.65){   
        color = Utils::getRandomColor();    
        ledsController->getKaveLeds()->ClearTo(color);
    }

    ledsController->getKaveLeds()->Show();

}
