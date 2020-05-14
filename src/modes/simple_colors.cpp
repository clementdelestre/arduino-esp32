#include "headers/simple_colors.hpp"

#include "../headers/leds_controller.hpp"

SimpleColorsMode::SimpleColorsMode(LedsController* ledsController) : Mode(ledsController){
     this->ledsController = ledsController;
     this->modeLabel = simpleColor;


     isAnimated = false;
     animationSpeed = 50;

     kaveCurrentColor = RgbColor(255, 255, 255);
     stairsCurrentColor = RgbColor(255, 255, 255);  

     //stairs enable
     posStairsColor = 0;
     isStairsDisplayed = true;

     //Animation
     posColor = 0;
     targetColor = Utils::getFixedRandomColor();

}


void SimpleColorsMode::displayMode(){

     if(isAnimated){
          kaveCurrentColor = RgbColor().LinearBlend(kaveCurrentColor, targetColor, posColor);

          ledsController->getKaveLeds()->ClearTo(kaveCurrentColor);
          ledsController->getKaveLeds()->Show();

          if(ledsController->canShowStairs()){
               if(posStairsColor >= 1 && isStairsDisplayed){ //Stairs is already on
                    stairsCurrentColor = kaveCurrentColor;              
               } else { //Stairs is turning on
                    stairsCurrentColor = RgbColor().LinearBlend(0, targetColor, posStairsColor);
                    posStairsColor += 0.05;
                    if(posStairsColor>=1) isStairsDisplayed = true;
               }

               ledsController->getStairsLeds()->ClearTo(stairsCurrentColor);
               ledsController->getStairsLeds()->Show();
          } else {
               isStairsDisplayed = false;
               posStairsColor = 0;
               ledsController->getStairsLeds()->ClearTo(0);
               ledsController->getStairsLeds()->Show();
          }         

          if(posColor >= 1){
               posColor = 0;
               targetColor = Utils::getFixedRandomColor();
          }

          posColor+=0.01;
          delay(5 + (200-animationSpeed));
     } else {
          ledsController->getKaveLeds()->ClearTo(kaveCurrentColor);
          ledsController->getKaveLeds()->Show();

          if(ledsController->canShowStairs()){
               ledsController->getStairsLeds()->ClearTo(stairsCurrentColor);
               ledsController->getStairsLeds()->Show();
          } else {
               ledsController->getStairsLeds()->ClearTo(0);
               ledsController->getStairsLeds()->Show();
          }   

          delay(40);
     }

     
}

void SimpleColorsMode::setKaveColor(RgbColor color){
     kaveCurrentColor = color;
     ledsController->getWifiManager()->sendAllClientData(Flags::SC_KAVE_COLOR, kaveCurrentColor.R, kaveCurrentColor.G, kaveCurrentColor.B);
}

void SimpleColorsMode::setStairsColor(RgbColor color){
     stairsCurrentColor = color;
     ledsController->getWifiManager()->sendAllClientData(Flags::SC_STAIRS_COLOR, stairsCurrentColor.R, stairsCurrentColor.G, stairsCurrentColor.B);
}

void SimpleColorsMode::sendModeData(){
     ledsController->getWifiManager()->sendAllClientData(Flags::SC_KAVE_COLOR, kaveCurrentColor.R, kaveCurrentColor.G, kaveCurrentColor.B);
     ledsController->getWifiManager()->sendAllClientData(Flags::SC_STAIRS_COLOR, stairsCurrentColor.R, stairsCurrentColor.G, stairsCurrentColor.B);
     ledsController->getWifiManager()->sendAllClientData(Flags::SC_ANIMATION, isAnimated ? 1 : 0, 0, 0);
     ledsController->getWifiManager()->sendAllClientData(Flags::SC_SPEED_ANIMATION, animationSpeed, 0, 0);
     ledsController->getWifiManager()->sendAllClientData(Flags::SENSOR_STAIRS, ledsController->getUseStairsSensor() ? 1 : 0, 0, 0);
}

void SimpleColorsMode::changeAnimated(bool animated){
     isAnimated = animated;
     sendModeData();
}

void SimpleColorsMode::changeAnimationSpeed(int speed){
     animationSpeed = speed;
}
