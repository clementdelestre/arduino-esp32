#include "headers/kave_strobodots.hpp"
#include "../../headers/leds_controller.hpp"

KaveStrobodots::KaveStrobodots(LedsController* ledsController, Microphone* microphone, int flag) : AnimationConstructor(ledsController, microphone, flag){  

    refreshMs = std::chrono::milliseconds(50);   
}

void KaveStrobodots::animationContent(){    
  
    ledsController->getKaveLeds()->ClearTo(0);
    
    int countLeds = maxLeds*microphone->getMediumFrequency();

    for(int x = 0; x<countLeds;x++){
        int position = 1+random(ledsController->getKaveLeds()->PixelCount()-2);

        RgbColor color = Utils::getFixedRandomColor();
        
        ledsController->getKaveLeds()->SetPixelColor(position-1, color);
        ledsController->getKaveLeds()->SetPixelColor(position, color);
        ledsController->getKaveLeds()->SetPixelColor(position+1, color);
    }

    ledsController->getKaveLeds()->Show();

}
