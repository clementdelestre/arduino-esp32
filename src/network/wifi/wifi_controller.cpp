#include "wifi_controller.hpp"
#include "../../leds/leds_controller.hpp"

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

  //TODO: Supprimer la première condition, car le reboot est effectué dans un event dans main (à tester)

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
          
          //read data        
          uint8_t buf[4];
          serverClients[i].readBytes(buf, 4);            

          
          //TODO: Faire le read (merci Léo :D :D :D)
          
         
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
    disconnectAllClient();
    ESP.restart();
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

