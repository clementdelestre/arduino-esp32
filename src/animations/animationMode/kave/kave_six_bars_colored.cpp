#include "headers/kave_six_bars_colored.hpp"
#include "../../../headers/leds_controller.hpp"

SixBarsColored::SixBarsColored(LedsController* ledsController, Microphone* microphone, int flag) : AnimationConstructor(ledsController, microphone, flag){   
    backColor = Utils::getFixedRandomColor(); 
    refreshMs = std::chrono::milliseconds(10);   
    section = ledsController->getKaveLeds()->PixelCount()/6;
}


void SixBarsColored::animationContent(){    
  
    for(int x = 0;x<ledsController->getKaveLeds()->PixelCount()/6; x++){
        ledsController->getKaveLeds()->SetPixelColor(x, RgbColor(255, 0, 0).Dim(255*microphone->getLowFrequency()));
        ledsController->getKaveLeds()->SetPixelColor(x + section, RgbColor(255, 255, 0).Dim(255*microphone->getMediumFrequency()));
        ledsController->getKaveLeds()->SetPixelColor(x + 2*section, RgbColor(0, 255, 0).Dim(255*microphone->getHighFrequency()));
        ledsController->getKaveLeds()->SetPixelColor(x + 3*section, RgbColor(0, 255, 255).Dim(255*microphone->getLowFrequency()));
        ledsController->getKaveLeds()->SetPixelColor(x + 4*section, RgbColor(0, 0, 255).Dim(255*microphone->getMediumFrequency()));
        ledsController->getKaveLeds()->SetPixelColor(x + 5*section, RgbColor(255, 0, 255).Dim(255*microphone->getHighFrequency()));
    }

    ledsController->getKaveLeds()->Show();

    
}
