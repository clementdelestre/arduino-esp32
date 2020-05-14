#include "headers/wifi_manager.hpp"
#include "headers/leds_controller.hpp"

WifiManager::WifiManager(WiFiServer* wifiServer, WiFiMulti* wifiMulti){
    this->wifiServer = wifiServer;
    this->wifiMulti = wifiMulti;
}

void WifiManager::setLedsController(LedsController* ledsController){
  this->ledsController = ledsController;
}

void WifiManager::scanClient(){
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
      }
    }
    //check clients for data
    for(i = 0; i < MAX_SRV_CLIENTS; i++){
      if (serverClients[i] && serverClients[i].connected()){
        if(serverClients[i].available()){
          //get data from the telnet client and push it to the UART
          
          uint8_t buf[4];
          while(serverClients[i].available()) {
            serverClients[i].readBytes(buf, 4);            
          }

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

void WifiManager::sendData(WiFiClient* client, uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4){
  uint8_t rep[4];
  rep[0] = data1;
  rep[1] = data2;
  rep[2] = data3;
  rep[3] = data4;
  client->write(rep, 4);
}

void WifiManager::sendAllClientData(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4){
  for(int i = 0; i < MAX_SRV_CLIENTS; i++) {
    if (serverClients[i]) sendData(&serverClients[i], data1, data2, data3, data4);
  }
}

