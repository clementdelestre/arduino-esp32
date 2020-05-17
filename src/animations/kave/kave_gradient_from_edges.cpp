#include "headers/kave_gradient_from_edges.hpp"
#include "../../headers/leds_controller.hpp"

KaveGradientFromEdges::KaveGradientFromEdges(LedsController* ledsController, Microphone* microphone, int flag) : AnimationConstructor(ledsController, microphone, flag){  

    refreshMs = std::chrono::milliseconds(20);    
    ledsController->getKaveLeds()->ClearTo(0);
    ledsController->getKaveLeds()->Show();

    position = 0;
    
}

void KaveGradientFromEdges::animationContent(){    
  
    if(microphone->getLowFrequency()>0.8 && position >= ledsController->getKaveLeds()->PixelCount()/2){   
        colorFrom = Utils::getFixedRandomColor(); 
        colorTo = Utils::getFixedRandomColor();
        position = 0;  
    }

    if(position < ledsController->getKaveLeds()->PixelCount()/2){
        position+=3;
        for(int x = 0;x<=position;x++){
            RgbColor color = RgbColor().LinearBlend(colorFrom, colorTo,  (double)2*x/ledsController->getKaveLeds()->PixelCount());
            ledsController->getKaveLeds()->SetPixelColor(x, color);
            ledsController->getKaveLeds()->SetPixelColor(ledsController->getKaveLeds()->PixelCount()-x, color);
        }
        ledsController->getKaveLeds()->Show();
    }

}
