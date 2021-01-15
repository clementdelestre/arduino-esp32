#include "headers/kave_slide.hpp"
#include "../../../leds/leds_controller.hpp"

KaveSlide::KaveSlide(LedsController* ledsController, Microphone* microphone, int flag) : AnimationConstructor(ledsController, microphone, flag){  
    refreshMs = std::chrono::milliseconds(13);   

    lastMove = std::chrono::duration_cast< std::chrono::seconds >(
        Utils::getTimeSinceEpoch()
    );

    ledsController->getKaveLeds()->clearTo(Utils::getRandomColor());
    ledsController->getKaveLeds()->show();
}

void KaveSlide::animationContent(){    
  
    int ledsCount = ledsController->getKaveLeds()->getLength()/6;

    if(microphone->getMediumFrequency() > 0.85 && lastMove+std::chrono::seconds(1)<Utils::getTimeSinceEpoch()){
        RgbColor color = Utils::getRandomColor();
        ledsController->getKaveLeds()->setPixelColor(ledsCount, color);
        ledsController->getKaveLeds()->setPixelColor(3*ledsCount, color);
        ledsController->getKaveLeds()->setPixelColor(5*ledsCount, color);

        lastMove = std::chrono::duration_cast< std::chrono::seconds >(
            Utils::getTimeSinceEpoch()
        );
    }

    
    for(int x = ledsCount; x>0;x--){
        ledsController->getKaveLeds()->setPixelColor(ledsCount+x, ledsController->getKaveLeds()->getPixelColor(ledsCount+x-1));
        ledsController->getKaveLeds()->setPixelColor(ledsCount-x, ledsController->getKaveLeds()->getPixelColor(ledsCount-x+1));

        ledsController->getKaveLeds()->setPixelColor(3*ledsCount+x, ledsController->getKaveLeds()->getPixelColor(ledsCount+x-1));
        ledsController->getKaveLeds()->setPixelColor(3*ledsCount-x, ledsController->getKaveLeds()->getPixelColor(ledsCount-x+1));

        ledsController->getKaveLeds()->setPixelColor(5*ledsCount+x, ledsController->getKaveLeds()->getPixelColor(ledsCount+x-1));
        ledsController->getKaveLeds()->setPixelColor(5*ledsCount-x, ledsController->getKaveLeds()->getPixelColor(ledsCount-x+1));
    }
 
    ledsController->getKaveLeds()->show();

}
