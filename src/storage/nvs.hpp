#include <Arduino.h>
#include "ArduinoNvs.h"


#ifndef NVS_STORAGE_H_INCLUDED
#define NVS_STORAGE_H_INCLUDED

class LedsController;


class NVSStorage {

    private:
        

    public:
        NVSStorage();
        void init();

        bool setInt(const char* key, int val);
        bool setFloat(const char* key, float val);
        bool setString(const char* key, String string);
        bool setBlob(const char* key, uint8_t* blob);
        
        int getInt(const char* key);
        float getFloat(const char* key);
        String getString(const char* key);

        uint8_t getBlobSize(const char* key);
        uint8_t* getBlob(const char* key, uint8_t* blob, uint8_t length);
        
};

#endif