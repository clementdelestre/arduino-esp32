#include "headers/simple_colors.hpp"

#include "../leds/leds_controller.hpp"

SimpleColorsMode::SimpleColorsMode(LedsController* ledsController) : Mode(ledsController){
     this->ledsController = ledsController;
     this->modeLabel = ModeLabel::simpleColor;

     animInitColor = 0;

     kaveCurrentColor = RgbColor(150, 150, 150);
     stairsCurrentColor = RgbColor(150, 150, 150);  

     //stairs enable
     posStairsColor = 0;
     isStairsDisplayed = true;

}

void SimpleColorsMode::startMode(){
     sendModeData();
}

void SimpleColorsMode::displayMode(){

     ledsController->getKaveLeds()->clearTo(kaveCurrentColor);
     ledsController->getKaveLeds()->show();

     if(ledsController->canShowStairs()){
          ledsController->getStairsLeds()->clearTo(stairsCurrentColor);
          ledsController->getStairsLeds()->show();
     } else {
          ledsController->getStairsLeds()->clearTo(0);
          ledsController->getStairsLeds()->show();
     }   

     delay(40);
 
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
     ledsController->getWifiManager()->sendAllClientData(Flags::SENSOR_STAIRS, ledsController->getUseStairsSensor() ? 1 : 0, 0, 0);
     ledsController->getWifiManager()->sendAllClientData(Flags::MAX_LUMINOSITY, Utils::maxLuminosity, 0, 0);
}