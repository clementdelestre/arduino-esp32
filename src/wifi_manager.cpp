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
            serverClients[i].readBytes(buf, sizeof(buf));            
          }
          uint8_t flag = buf[0];
          switch(flag){
            case Flags::CHANGE_MODE:
              Serial.println("change mode");
              int mode = buf[1];
              Serial.println(mode);
              break;
            case Flags::SENSOR_STAIRS:
              Serial.println("sensor stairs");
              break;
            case Flags::SC_KAVE_COLOR:
              Serial.println("sc kave color");
              break;

            default:
              Serial.println("socket: wrong data!");
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

/*void WifiManager::receiveMessage(WiFiClient* wifiClient, String message){
  Serial.println(message);
  
  if(message == "set-mode-simple-color"){
    ledsController->setMode(simpleColor);
  } else if(message == "set-mode-animation"){
    ledsController->setMode(animations);
  } else {
    Serial.println("other message");
  }

  wifiClient->write("ok");
  wifiClient->flush();
}*/

