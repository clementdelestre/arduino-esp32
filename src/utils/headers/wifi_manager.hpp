#include "WiFi.h"
#include "WiFiMulti.h"

#define MAX_SRV_CLIENTS 5

#ifndef WIFI_MANAGER_H_INCLUDED
#define WIFI_MANAGER_H_INCLUDED

enum Flags : int {
    CHANGE_MODE = 0,
    SENSOR_STAIRS = 1,

    //SIMPLE COLOR MODE
    SC_KAVE_COLOR = 10,
    SC_STAIRS_COLOR = 11,
    SC_ANIMATION = 12,
    SC_SPEED_ANIMATION = 13,
    //ANIMATION MODE
    A_KAVE_CURRENT_ANIM = 20,
    A_KEEP_ANIMATION = 21,
    A_NEXT_ANIMATION = 22,
    A_SELECT_ANIMATION = 23,
    A_START_STROBOSCOPE = 24,
    A_STOP_AUTO_STROBOSCOPE = 25,
    A_STROBOSCOPE_SPEED = 26,
    A_STAIRS_RANDOM_ANIM = 27,
    A_STAIRS_CURRENT_ANIM = 28,
    A_MAIN_COLOR_AUT0 = 29,
    A_MAIN_COLOR = 30,
    A_GET_ENABLED_ANIMATIONS = 31,
    A_SET_ENABLE_ANIMATION = 32,

};

class LedsController;

class WifiManager {
    
    private:
        WiFiServer* wifiServer;
        WiFiMulti* wifiMulti;
        WiFiClient serverClients[MAX_SRV_CLIENTS];
        LedsController* ledsController;
        
        void disconnectAllClient();
    public:
        WifiManager(WiFiServer* wifiServer, WiFiMulti* wifiMulti);
        void setLedsController(LedsController* ledsController);
        void scanClient();

        static void sendData(WiFiClient* client, uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4);
        void sendAllClientData(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4);
};

#endif