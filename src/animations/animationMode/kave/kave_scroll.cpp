#include "headers/kave_scroll.hpp"
#include "../../../leds/leds_controller.hpp"

KaveScroll::KaveScroll(LedsController* ledsController, Microphone* microphone, int flag) : AnimationConstructor(ledsController, microphone, flag){  
    refreshMs = std::chrono::milliseconds(10); 
    lastSpawn = Utils::getTimeSinceEpoch();  
    ledsController->getKaveLeds()->clearTo(0);
}

void KaveScroll::animationContent(){    
  
    if((microphone->getLowFrequency()>0.75 && lastSpawn+std::chrono::milliseconds(500) < Utils::getTimeSinceEpoch()) || lastSpawn+std::chrono::milliseconds(2000) < Utils::getTimeSinceEpoch()){
        float progress = 0;
        RgbColor targetColor = getColorWithDefault(Utils::getFixedRandomColor());
        for(int x = 0;x<this->length;x++){        
            RgbColor color = RgbColor().LinearBlend(RgbColor(0, 0, 0), targetColor, progress);
            ledsController->getKaveLeds()->setPixelColor(ledsController->getKaveLeds()->getLength()/2 + x, color);
            ledsController->getKaveLeds()->setPixelColor(ledsController->getKaveLeds()->getLength()/2 - x, color);
            progress = (x < this->length/2) ? x/(this->length/2) : 1-(x-this->length/2)/(this->length/2);
        }

        lastSpawn = Utils::getTimeSinceEpoch();
        
    } 
    
    for(int x = ledsController->getKaveLeds()->getLength()/2;x>0;x--){
        ledsController->getKaveLeds()->setPixelColor(ledsController->getKaveLeds()->getLength()/2+x, ledsController->getKaveLeds()->getPixelColor(ledsController->getKaveLeds()->getLength()/2+x-1));
        ledsController->getKaveLeds()->setPixelColor(ledsController->getKaveLeds()->getLength()/2-x, ledsController->getKaveLeds()->getPixelColor(ledsController->getKaveLeds()->getLength()/2-x+1));
    }

    ledsController->getKaveLeds()->show();

}
