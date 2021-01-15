#include "headers/wifi_controller.hpp"
#include "leds/leds_controller.hpp"

WifiController::WifiController(WiFiServer* wifiServer, WiFiMulti* wifiMulti, WiFiManager* wifiManager){
    this->wifiServer = wifiServer;
    this->wifiMulti = wifiMulti;
    this->wifiManager = wifiManager;
}

void WifiController::setLedsController(LedsController* ledsController){
  this->ledsController = ledsController;
}

void WifiController::scanClient(){
  uint8_t i;

  if (wifiMulti->run() == WL_CONNECTED) {
    //check if there are any new clients
    if (wifiServer->hasClient()){
      for(i = 0; i < MAX_SRV_CLIENTS; i++){
        //find free/disconnected spot
        if (!serverClients[i] || !serverClients[i].connected()){
          if(serverClients[i]) serverClients[i].stop();
          serverClients[i] = wifiServer->available();
          if (!serverClients[i]) Serial.println("available broken");
          Serial.print("New client: ");
          Serial.print(i); Serial.print(' ');
          Serial.println(serverClients[i].remoteIP());
          break;
        }
      }
      if (i >= MAX_SRV_CLIENTS) {
        //no free/disconnected spot so reject
        wifiServer->available().stop();
        disconnectAllClient();
      }
    }
    //check clients for data
    for(i = 0; i < MAX_SRV_CLIENTS; i++){
      if (serverClients[i] && serverClients[i].connected()){
        if(serverClients[i].available() >= 4){
          
          //get data from the telnet client and push it to the UART         
          uint8_t buf[4];
          serverClients[i].readBytes(buf, 4);            

          uint8_t flag = buf[0];

          switch(flag){
            case Flags::CHANGE_MODE: {                        
              //sendData(&serverClients[i], 11, 0, 255, 0);  
              ledsController->setMode(buf[1]);     
                      
              break;
            }
            case Flags::SENSOR_STAIRS:
              ledsController->setUseStairsSensor(buf[1] == 1);
              break;
            case Flags::SC_KAVE_COLOR:
              ledsController->getSimpleColorMode()->setKaveColor(RgbColor(buf[1], buf[2], buf[3]));            
              break;
            case Flags::SC_STAIRS_COLOR:
              ledsController->getSimpleColorMode()->setStairsColor(RgbColor(buf[1], buf[2], buf[3]));            
              break;
            case Flags::SC_ANIMATION:
              ledsController->getSimpleColorMode()->changeAnimated(buf[1] == 1);
              break;
            case Flags::SC_SPEED_ANIMATION:
              ledsController->getSimpleColorMode()->changeAnimationSpeed(buf[1]);
              break;
            case Flags::A_NEXT_ANIMATION:
              ledsController->getAnimationMode()->nextKaveAnimation();
              break;
            case Flags::A_KEEP_ANIMATION:
              ledsController->getAnimationMode()->setKeepAnimation(buf[1]==1);
              break;
            case Flags::A_STAIRS_RANDOM_ANIM:
              ledsController->getAnimationMode()->setStairsRandomAnim(buf[1]==1);
              break;
            case Flags::A_STAIRS_CURRENT_ANIM:
              ledsController->getAnimationMode()->setStairsAnim(buf[1]);
              break;
            case Flags::A_MAIN_COLOR_AUT0:
              ledsController->getAnimationMode()->setMainAutoColor(buf[1]==1);
              break;
            case Flags::A_MAIN_COLOR:
              ledsController->getAnimationMode()->setMainColor(RgbColor(buf[1], buf[2], buf[3]));
              break;
            case Flags::A_SET_ENABLE_ANIMATION:
              ledsController->getAnimationMode()->setEnableAnimation(buf[1], buf[2] == 1);
              break;
            case Flags::A_GET_ENABLED_ANIMATIONS:
              ledsController->getAnimationMode()->sendEnabledAnimations(&serverClients[i]);
              break;
            case Flags::A_SET_CATEGORY_ANIMATION:
              ledsController->getAnimationMode()->setCategory(buf[1]);
              break;
            case Flags::A_SELECT_ANIMATION:
              ledsController->getAnimationMode()->setKaveAnimation(buf[1]);
              break;
            case Flags::A_START_STROBOSCOPE:
              ledsController->getAnimationMode()->startStroboscope();
              break;
            case Flags::A_STROBOSCOPE_SPEED:
              ledsController->getAnimationMode()->setStroboscopeSpeed(buf[1]);
              break;
            case Flags::A_STOP_AUTO_STROBOSCOPE:
              ledsController->getAnimationMode()->setStroboscopeAutoStop(buf[1] == 1);
              break;
            case Flags::A_STROBOSCOPE_LUMINOSITY:
              ledsController->getAnimationMode()->setStroboscopeLuminosity(buf[1]);
              break;
            
            //CINEKAVE
            case Flags::CK_MODE:
              ledsController->getCineKaveMode()->setPlayMode(buf[1]);
              break;
            case Flags::CK_SCREEN_COLOR:
              ledsController->getCineKaveMode()->setScreenColor(RgbColor(buf[1], buf[2], buf[3]));
              break;
            case Flags::CK_LUMINOSITY:
              ledsController->getCineKaveMode()->setLuminosity(buf[1]);
              break;
            case Flags::CK_IS_CONNECTED:
              ledsController->getCineKaveMode()->setComputerClient(&serverClients[i]);
              break;
            
            //OTHERS
            case Flags::CHECK_CONNECTION:
              break;
            case Flags::ACCESS_POINT:
              wifiManager->setConfigPortalTimeout(30);
              wifiManager->startConfigPortal("The Kave - Network Configurator");
              break;
            case Flags::MAX_LUMINOSITY:
              Utils::maxLuminosity = buf[1];
              break;

            default:
              Serial.println("socket: wrong data!");
              Serial.println(buf[0]);
              Serial.println(buf[1]);
              Serial.println(buf[2]);
              Serial.println(buf[3]);
              break;
          }
        }
      }
      else {
        if (serverClients[i]) {
          Serial.println("Client disconnected");
          serverClients[i].stop();
        }
      }
    }
  }
  else {
    Serial.println("WiFi not connected!");
    for(i = 0; i < MAX_SRV_CLIENTS; i++) {
      if (serverClients[i]) serverClients[i].stop();
    }
    delay(1000);
  }
}

void WifiController::disconnectAllClient(){
  for(int i = 0; i < MAX_SRV_CLIENTS; i++) {
    serverClients[i].stop();
  }
}

void WifiController::sendData(WiFiClient* client, uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4){
  uint8_t rep[4];
  rep[0] = data1;
  rep[1] = data2;
  rep[2] = data3;
  rep[3] = data4;
  client->write(rep, 4);
}

void WifiController::sendAllClientData(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4){
  for(int i = 0; i < MAX_SRV_CLIENTS; i++) {
    if (serverClients[i]) sendData(&serverClients[i], data1, data2, data3, data4);
  }
}

