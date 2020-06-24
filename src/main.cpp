#include <Arduino.h>
#include "WiFi.h"
#include "WiFiMulti.h"

#include "utils/headers/wifi_manager.hpp"
#include "headers/leds_controller.hpp"

//BUTTONS
#define BUTTON_STAIRS 35
#define BUTTON_KAVE 32

// WIFI
const char* ssid = "Devolo";
const char* password = "Tatatoum";

WiFiMulti wifiMulti;
WiFiServer wifiServer(2000);
WifiManager* wifiManager;

//END WIFI

LedsController* ledsController;

char ptrTaskList[250];

void setup() {
  Serial.begin(115200);
  
  wifiManager = new WifiManager(&wifiServer, &wifiMulti);
  ledsController = new LedsController(wifiManager);

  wifiManager->setLedsController(ledsController);

  //START WIFI
  wifiMulti.addAP(ssid, password);

  ledsController->init();

  Serial.println("Connecting Wifi ");
  for (int loops = 10; loops > 0; loops--) {
    if (wifiMulti.run() == WL_CONNECTED) {
      Serial.println("");
      Serial.print("WiFi connected ");
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
      break;
    }
    else {
      Serial.println(loops);
      delay(1000);
    }
  }
  if (wifiMulti.run() != WL_CONNECTED) {
    Serial.println("WiFi connect failed");
    ledsController->getWifiLoaderMode()->needRestart();
    delay(1000);
    ESP.restart();
  }

  //start the server
  wifiServer.begin();
  wifiServer.setNoDelay(true);

  ledsController->setMode(ModeLabel::simpleColor);

}

void loop() {
  //WifiManager
  wifiManager->scanClient();
  
}