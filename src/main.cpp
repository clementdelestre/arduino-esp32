#include <Arduino.h>
#include "WiFi.h"
#include "WiFiMulti.h"
#include <ESPmDNS.h>
#include <WiFiManager.h>

#include "utils/headers/wifi_controller.hpp"
#include "headers/leds_controller.hpp"


//BUTTONS
#define BUTTON_STAIRS 35
#define BUTTON_KAVE 32

// WIFI
//Access Point
const char* ssid_AP = "Kave controller";

WiFiMulti wifiMulti;
WiFiServer wifiServer(2000);
WifiController* wifiController;
WiFiManager wm;

//END WIFI

LedsController* ledsController;

char ptrTaskList[250];

void setup() {
  Serial.begin(115200);
  
  wifiController = new WifiController(&wifiServer, &wifiMulti, &wm);
  ledsController = new LedsController(wifiController);

  wifiController->setLedsController(ledsController);

  //START WIFI
  WiFi.mode(WIFI_STA);

  wm.setAPStaticIPConfig(IPAddress(192,168,0,1), IPAddress(192,168,0,1), IPAddress(255,255,255,0));
  wm.setDebugOutput(false);

  if(!wm.autoConnect("The Kave")){
    Serial.println("Erreur de connexion.");
  } else {
    Serial.println("Connexion etablie!");
    wm.setConfigPortalTimeout(15);
    wm.startConfigPortal("The Kave - Network Configurator");

    wifiMulti.addAP(WiFi.SSID().c_str(), WiFi.psk().c_str());
  }

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

  if(!MDNS.begin("Kave Esp v4")) {
    Serial.println("Error starting mDNS");
    return;
  } 

  MDNS.addService("_kave", "_tcp", 2500);
  MDNS.addServiceTxt("_kave", "_tcp", "ip", WiFi.localIP().toString());


  //start the server
  wifiServer.begin();
  wifiServer.setNoDelay(true);

  ledsController->setMode(ModeLabel::simpleColor);

}

void loop() {
  //wifiController
  wifiController->scanClient();
  
}