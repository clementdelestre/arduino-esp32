#include "headers/cinekave.hpp"

#include "../headers/leds_controller.hpp"

CineKaveMode::CineKaveMode(LedsController* ledsController) : Mode(ledsController){
     this->ledsController = ledsController;
     this->modeLabel = ModeLabel::cinekave;

     //set mode initial values
     screenColor = RgbColor(150,0,150);
     luminosity = 30;
     
     currentAnimation = new WaitingCineKaveAnim(ledsController);  
}

void CineKaveMode::startMode(){
     //reset values each launch
     //save the sensor state
     this->resetStairsSensorValue = ledsController->getUseStairsSensor();
     ledsController->setUseStairsSensor(true);
     lastConnectionReceive = Utils::getTimeSinceEpoch()-std::chrono::seconds(connectionTimeOut);    
}

void CineKaveMode::stopMode(){
     //reset the sensor state
     ledsController->setUseStairsSensor(resetStairsSensorValue);
}

void CineKaveMode::displayMode(){
     currentAnimation->displayAnimation();
}

void CineKaveMode::sendModeData(){
     ledsController->getWifiManager()->sendAllClientData(Flags::CK_IS_CONNECTED, isConnected ? 1 : 0, 0, 0);
     ledsController->getWifiManager()->sendAllClientData(Flags::CK_MODE, currentAnimation->getFlag(), 0, 0);
     ledsController->getWifiManager()->sendAllClientData(Flags::CK_LUMINOSITY, luminosity, 0, 0);
     ledsController->getWifiManager()->sendAllClientData(Flags::CK_IS_CONNECTED, getConnectionState() ? 1 : 0, 0, 0);
}

bool CineKaveMode::getConnectionState(){
     return lastConnectionReceive+std::chrono::seconds(connectionTimeOut)>Utils::getTimeSinceEpoch();
}

int CineKaveMode::getPlayMode(){
     return currentAnimation->getFlag();
}

void CineKaveMode::setPlayMode(int playMode){

     currentAnimation->eventClose();

     switch(playMode){
          case CinePlayMode::WAITING:
               currentAnimation = new WaitingCineKaveAnim(ledsController);
               break;
          case CinePlayMode::PLAYING:
               currentAnimation = new PlayingCineKaveAnim(ledsController);
               break;
          case CinePlayMode::PAUSED:
               currentAnimation = new PausedCineKaveAnim(ledsController);
               break;
     }

     currentAnimation->init();
     ledsController->getWifiManager()->sendAllClientData(Flags::CK_MODE, currentAnimation->getFlag(), 0, 0);
}

void CineKaveMode::setScreenColor(RgbColor screenColor){
     this->screenColor = screenColor;
     lastConnectionReceive = Utils::getTimeSinceEpoch();
}

RgbColor CineKaveMode::getScreenColor(){
     return screenColor;
}

void CineKaveMode::setLuminosity(int luminosity){
     this->luminosity = luminosity;
}

int CineKaveMode::getLuminosity(){
     return luminosity;
}

