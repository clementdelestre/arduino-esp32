#include "headers/wifi_loader.hpp"

#include "../headers/leds_controller.hpp"

WifiLoaderMode::WifiLoaderMode(LedsController* ledsController) : Mode(ledsController){
     this->ledsController = ledsController;
     this->modeLabel = ModeLabel::wifiLoader;

     lastAnim = std::chrono::duration_cast< std::chrono::seconds >(
          Utils::getTimeSinceEpoch()-std::chrono::seconds(1)
     );

     restartAnim = false;
}

void WifiLoaderMode::startMode(){
     ledsController->getKaveLeds()->ClearTo(0);
     ledsController->getStairsLeds()->ClearTo(0);

     ledsController->getKaveLeds()->Show();
     ledsController->getStairsLeds()->Show();
}

void WifiLoaderMode::displayMode(){

     if(restartAnim){
          for(int x = 0;x<ledsController->getKaveLeds()->PixelCount();x++){
              ledsController->getKaveLeds()->SetPixelColor(x, restartColor);
          }

          ledsController->getKaveLeds()->Show();

          delay(100);
          return;
     }

    if(lastAnim + std::chrono::seconds(1) < Utils::getTimeSinceEpoch()){
          for(int x = 0;x<lengthBar;x++){
              ledsController->getKaveLeds()->SetPixelColor(x, color);
          }

          ledsController->getKaveLeds()->Show();
          lastAnim = std::chrono::duration_cast< std::chrono::seconds >(
               Utils::getTimeSinceEpoch()
          );
    }

     for(int x = ledsController->getKaveLeds()->PixelCount();x>=0;x--){
          ledsController->getKaveLeds()->SetPixelColor(x, ledsController->getKaveLeds()->GetPixelColor(x-1));
     }

     ledsController->getKaveLeds()->Show();

     delay(30);  
}

void WifiLoaderMode::needRestart(){
     restartAnim = true;
}