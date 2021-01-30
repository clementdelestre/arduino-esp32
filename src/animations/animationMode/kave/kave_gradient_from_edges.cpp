#include "headers/kave_gradient_from_edges.hpp"
#include "../../../leds/leds_controller.hpp"

KaveGradientFromEdges::KaveGradientFromEdges(LedsController* ledsController, Microphone* microphone, int flag) : AnimationConstructor(ledsController, microphone, flag){  
    refreshMs = std::chrono::milliseconds(20);      
}

void KaveGradientFromEdges::animationContent(){    
  
    if(microphone->getLowFrequency()>0.8 && position >= ledsController->getKaveLeds()->getLength()/2){   
        run();
    }

    if(position < ledsController->getKaveLeds()->getLength()/2){
        position+=min(ledsController->getKaveLeds()->getLength()/2-position, 3);
        for(int x = 0;x<=position;x++){
            RgbColor color = RgbColor().LinearBlend(colorFrom, colorTo,  (double)2*x/ledsController->getKaveLeds()->getLength());
            ledsController->getKaveLeds()->setPixelColor(x, color);
            ledsController->getKaveLeds()->setPixelColor(ledsController->getKaveLeds()->getLength()-x, color);
        }
        ledsController->getKaveLeds()->show();
    }

}

void KaveGradientFromEdges::init(){
    ledsController->getKaveLeds()->clearTo(0);
    ledsController->getKaveLeds()->show();
    position = 0;

    this->run();
}

void KaveGradientFromEdges::run(){
    colorFrom = Utils::getFixedRandomColor(); 
    colorTo = Utils::getFixedRandomColor();
    position = 0;  
}
