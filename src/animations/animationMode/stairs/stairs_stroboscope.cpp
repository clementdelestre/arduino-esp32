#include "headers/stairs_stroboscope.hpp"
#include "../../../leds/leds_controller.hpp"

StairsStroboscope::StairsStroboscope(LedsController* ledsController, Microphone* microphone, int flag) : AnimationConstructor(ledsController, microphone, flag){
      
    init();
    refreshMs = std::chrono::milliseconds(40); 
}


void StairsStroboscope::animationContent(){
    if(progress <1){
        ledsController->getStairsLeds()->clearTo(RgbColor().LinearBlend(0, color, progress));
        ledsController->getStairsLeds()->show();
        progress+=0.05;
    }

    if(progress == 1){
        refreshMs = std::chrono::milliseconds(100); ;
    }
}

void StairsStroboscope::init(){
    progress = 0;
    color = RgbColor(30, 30, 30);
}
