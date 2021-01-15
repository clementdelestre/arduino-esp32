#include "headers/stairs_rainbow.hpp"
#include "../../../leds/leds_controller.hpp"

StairsRainbow::StairsRainbow(LedsController* ledsController, Microphone* microphone, int flags) : AnimationConstructor(ledsController, microphone, flags){  
    refreshMs = std::chrono::milliseconds(30); 
    dimEffect = 0;
}


void StairsRainbow::animationContent(){
    int luminosity = max(35, Utils::maxLuminosity);

    if(dimEffect <= luminosity){
        for(float x = 0;x<ledsController->getStairsLeds()->getLength();x+=1){
            if(x<=ledsController->getStairsLeds()->getLength()/3){
                ledsController->getStairsLeds()->setPixelColor(x, RgbColor().LinearBlend(RgbColor(luminosity, 0, 0), RgbColor(0, luminosity, 0), (3*x)/ledsController->getStairsLeds()->getLength()).Dim(dimEffect));
            } else if(x<=ledsController->getStairsLeds()->getLength()*2/3){
                ledsController->getStairsLeds()->setPixelColor(x, RgbColor().LinearBlend(RgbColor(0, luminosity, 0), RgbColor(0, 0, luminosity), (3*x)/ledsController->getStairsLeds()->getLength()-1).Dim(dimEffect));
            } else {
                ledsController->getStairsLeds()->setPixelColor(x, RgbColor().LinearBlend(RgbColor(0, 0, luminosity), RgbColor( luminosity, 0, 0), (3*x)/ledsController->getStairsLeds()->getLength()-2).Dim(dimEffect));
            }
        }       
        dimEffect+=15;

        if(dimEffect>= luminosity){
            refreshMs = std::chrono::milliseconds(70);
        }
    } else {
        ledsController->getStairsLeds()->rotateRight(1);
    }

    ledsController->getStairsLeds()->show();
    
}

void StairsRainbow::init(){
    dimEffect = 0;
}
