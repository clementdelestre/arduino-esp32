#include "headers/wifi_loader.hpp"

#include "../leds/leds_controller.hpp"

WifiLoaderMode::WifiLoaderMode(LedsController* ledsController) : Mode(ledsController){
     this->ledsController = ledsController;
     this->modeLabel = ModeLabel::wifiLoader;

     lastAnim = std::chrono::duration_cast< std::chrono::seconds >(
          Utils::getTimeSinceEpoch()-std::chrono::seconds(1)
     );

     restartAnim = false;
}

void WifiLoaderMode::startMode(){
     ledsController->getKaveLeds()->clearTo(0);
     ledsController->getStairsLeds()->clearTo(color);

     ledsController->getKaveLeds()->show();
     ledsController->getStairsLeds()->show();
}

void WifiLoaderMode::displayMode(){

     if(restartAnim){
          ledsController->getKaveLeds()->clear();
          for(int x = 0;x<ledsController->getKaveLeds()->getLength();x++){
              ledsController->getKaveLeds()->setPixelColor(x, restartColor);
          }

          ledsController->getKaveLeds()->show();

          delay(100);
          return;
     }

     if(lastAnim + std::chrono::milliseconds(1500) < Utils::getTimeSinceEpoch()){
          for(int x = 0;x<lengthBar;x++){
              ledsController->getKaveLeds()->setPixelColor(x, color);
          }

          lastAnim = std::chrono::duration_cast< std::chrono::seconds >(
               Utils::getTimeSinceEpoch()
          );

          ledsController->getKaveLeds()->show();
     }
     ledsController->getKaveLeds()->shiftRight(1);

     ledsController->getKaveLeds()->show();

     delay(30);  
}

void WifiLoaderMode::needRestart(){
     restartAnim = true;
}