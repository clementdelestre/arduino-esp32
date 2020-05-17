#include "headers/stairs_stroboscope.hpp"
#include "../../headers/leds_controller.hpp"

StairsStroboscope::StairsStroboscope(LedsController* ledsController, Microphone* microphone, int flag) : AnimationConstructor(ledsController, microphone, flag){
      
    init();
    refreshMs = std::chrono::milliseconds(40); 
}


void StairsStroboscope::animationContent(){
    if(progress <1){
        ledsController->getStairsLeds()->ClearTo(RgbColor().LinearBlend(0, color, progress));
        ledsController->getStairsLeds()->Show();
        progress+=0.05;
    }
}

void StairsStroboscope::init(){
    progress = 0;
    color = RgbColor(50, 50, 50);
}
