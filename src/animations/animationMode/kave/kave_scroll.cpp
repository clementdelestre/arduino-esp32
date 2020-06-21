#include "headers/kave_scroll.hpp"
#include "../../../headers/leds_controller.hpp"

KaveScroll::KaveScroll(LedsController* ledsController, Microphone* microphone, int flag) : AnimationConstructor(ledsController, microphone, flag){  
    refreshMs = std::chrono::milliseconds(10); 
    lastSpawn = Utils::getTimeSinceEpoch();  
    ledsController->getKaveLeds()->ClearTo(0);
}

void KaveScroll::animationContent(){    
  
    if(((microphone->getMediumFrequency()>0.7 || microphone->getLowFrequency()>0.7) && lastSpawn+std::chrono::milliseconds(300) < Utils::getTimeSinceEpoch()) || lastSpawn+std::chrono::milliseconds(2000) < Utils::getTimeSinceEpoch()){
        float progress = 0;
        RgbColor targetColor = getColorWithDefault(Utils::getFixedRandomColor());
        for(int x = 0;x<10;x++){        
            RgbColor color = RgbColor().LinearBlend(RgbColor(0, 0, 0), targetColor, progress);
            ledsController->getKaveLeds()->SetPixelColor(ledsController->getKaveLeds()->PixelCount()/2 + x, color);
            ledsController->getKaveLeds()->SetPixelColor(ledsController->getKaveLeds()->PixelCount()/2 - x, color);
            progress = (x < 5) ? progress+0.2 : progress-0.2;
        }

        lastSpawn = Utils::getTimeSinceEpoch();
        
    } 
    
    for(int x = ledsController->getKaveLeds()->PixelCount()/2;x>0;x--){
        ledsController->getKaveLeds()->SetPixelColor(ledsController->getKaveLeds()->PixelCount()/2+x, ledsController->getKaveLeds()->GetPixelColor(ledsController->getKaveLeds()->PixelCount()/2+x-1));
        ledsController->getKaveLeds()->SetPixelColor(ledsController->getKaveLeds()->PixelCount()/2-x, ledsController->getKaveLeds()->GetPixelColor(ledsController->getKaveLeds()->PixelCount()/2-x+1));
    }

    ledsController->getKaveLeds()->Show();

}
