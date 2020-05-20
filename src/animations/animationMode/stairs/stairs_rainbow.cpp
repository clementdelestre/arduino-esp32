#include "headers/stairs_rainbow.hpp"
#include "../../../headers/leds_controller.hpp"

StairsRainbow::StairsRainbow(LedsController* ledsController, Microphone* microphone, int flags) : AnimationConstructor(ledsController, microphone, flags){  
    refreshMs = std::chrono::milliseconds(40); 
    dimEffect = 0;
}


void StairsRainbow::animationContent(){
    if(dimEffect <= 255){
        for(float x = 0;x<ledsController->getStairsLeds()->PixelCount();x+=1){
            if(x<ledsController->getStairsLeds()->PixelCount()/3){
                ledsController->getStairsLeds()->SetPixelColor(x, RgbColor().LinearBlend(RgbColor(255, 0, 0), RgbColor(0, 255, 0), (3*x)/ledsController->getStairsLeds()->PixelCount()).Dim(dimEffect));
            } else if(x<ledsController->getStairsLeds()->PixelCount()*2/3){
                ledsController->getStairsLeds()->SetPixelColor(x, RgbColor().LinearBlend(RgbColor(0, 255, 0), RgbColor(0, 0, 255), (3*x)/ledsController->getStairsLeds()->PixelCount() -1).Dim(dimEffect));
            } else {
                ledsController->getStairsLeds()->SetPixelColor(x, RgbColor().LinearBlend(RgbColor(0, 0, 255), RgbColor(255, 0, 0), (3*x)/ledsController->getStairsLeds()->PixelCount() -2).Dim(dimEffect));
            }
        }       
        dimEffect+=10;

        if(dimEffect>=255){
            refreshMs = std::chrono::milliseconds(80);
        }
    } else {
        ledsController->getStairsLeds()->RotateRight(1);
    }

    ledsController->getStairsLeds()->Show();
    
}

void StairsRainbow::init(){
    dimEffect = 0;
}
