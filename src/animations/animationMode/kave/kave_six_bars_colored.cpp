#include "headers/kave_six_bars_colored.hpp"
#include "../../../leds/leds_controller.hpp"

SixBarsColored::SixBarsColored(LedsController* ledsController, Microphone* microphone, int flag) : AnimationConstructor(ledsController, microphone, flag){   
    backColor = Utils::getFixedRandomColor(); 
    refreshMs = std::chrono::milliseconds(10);   
    section = ledsController->getKaveLeds()->getLength()/6;
}


void SixBarsColored::animationContent(){    
  
    for(int x = 0;x<ledsController->getKaveLeds()->getLength()/6; x++){
        ledsController->getKaveLeds()->setPixelColor(x, RgbColor(255, 0, 0).Dim(255*microphone->getLowFrequency()));
        ledsController->getKaveLeds()->setPixelColor(x + section, RgbColor(255, 255, 0).Dim(255*microphone->getMediumFrequency()));
        ledsController->getKaveLeds()->setPixelColor(x + 2*section, RgbColor(0, 255, 0).Dim(255*microphone->getHighFrequency()));
        ledsController->getKaveLeds()->setPixelColor(x + 3*section, RgbColor(0, 255, 255).Dim(255*microphone->getLowFrequency()));
        ledsController->getKaveLeds()->setPixelColor(x + 4*section, RgbColor(0, 0, 255).Dim(255*microphone->getMediumFrequency()));
        ledsController->getKaveLeds()->setPixelColor(x + 5*section, RgbColor(255, 0, 255).Dim(255*microphone->getHighFrequency()));
    }

    ledsController->getKaveLeds()->show();

    
}
