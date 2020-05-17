#include "headers/kave_white_dots.hpp"
#include "../../headers/leds_controller.hpp"

WhiteDots::WhiteDots(LedsController* ledsController, Microphone* microphone, int flag) : AnimationConstructor(ledsController, microphone, flag){  

    init();
    
    refreshMs = std::chrono::milliseconds(20);   
}

void WhiteDots::init(){

    backColor = getColorWithDefault(Utils::getFixedRandomColor()); 
    
}

void WhiteDots::animationContent(){    
  
    ledsController->getKaveLeds()->ClearTo(backColor.Dim(max(255*microphone->getLowFrequency(), (float) 30)));

    int numDots = 12*microphone->getLowFrequency();

    for(int x = 0;x<numDots; x++){
        ledsController->getKaveLeds()->SetPixelColor(random(ledsController->getKaveLeds()->PixelCount()), RgbColor(255, 255, 255));
    }

    ledsController->getKaveLeds()->Show();

}
