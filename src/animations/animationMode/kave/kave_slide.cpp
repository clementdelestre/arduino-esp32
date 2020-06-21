#include "headers/kave_slide.hpp"
#include "../../../headers/leds_controller.hpp"

KaveSlide::KaveSlide(LedsController* ledsController, Microphone* microphone, int flag) : AnimationConstructor(ledsController, microphone, flag){  
    refreshMs = std::chrono::milliseconds(13);   

    lastMove = std::chrono::duration_cast< std::chrono::seconds >(
        Utils::getTimeSinceEpoch()
    );

    ledsController->getKaveLeds()->ClearTo(Utils::getRandomColor());
    ledsController->getKaveLeds()->Show();
}

void KaveSlide::animationContent(){    
  
    int ledsCount = ledsController->getKaveLeds()->PixelCount()/6;

    if(microphone->getMediumFrequency() > 0.85 && lastMove+std::chrono::seconds(1)<Utils::getTimeSinceEpoch()){
        RgbColor color = Utils::getRandomColor();
        ledsController->getKaveLeds()->SetPixelColor(ledsCount, color);
        ledsController->getKaveLeds()->SetPixelColor(3*ledsCount, color);
        ledsController->getKaveLeds()->SetPixelColor(5*ledsCount, color);

        lastMove = std::chrono::duration_cast< std::chrono::seconds >(
            Utils::getTimeSinceEpoch()
        );
    }

    
    for(int x = ledsCount; x>0;x--){
        ledsController->getKaveLeds()->SetPixelColor(ledsCount+x, ledsController->getKaveLeds()->GetPixelColor(ledsCount+x-1));
        ledsController->getKaveLeds()->SetPixelColor(ledsCount-x, ledsController->getKaveLeds()->GetPixelColor(ledsCount-x+1));

        ledsController->getKaveLeds()->SetPixelColor(3*ledsCount+x, ledsController->getKaveLeds()->GetPixelColor(ledsCount+x-1));
        ledsController->getKaveLeds()->SetPixelColor(3*ledsCount-x, ledsController->getKaveLeds()->GetPixelColor(ledsCount-x+1));

        ledsController->getKaveLeds()->SetPixelColor(5*ledsCount+x, ledsController->getKaveLeds()->GetPixelColor(ledsCount+x-1));
        ledsController->getKaveLeds()->SetPixelColor(5*ledsCount-x, ledsController->getKaveLeds()->GetPixelColor(ledsCount-x+1));
    }
 
    ledsController->getKaveLeds()->Show();

}
