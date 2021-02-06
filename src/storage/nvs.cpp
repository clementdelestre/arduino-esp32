#include "nvs.hpp"

NVSStorage::NVSStorage(){

}

void NVSStorage::init(){
    NVS.begin();
}


/* SETTERS */

bool NVSStorage::setInt(const char* key, int val){
    return NVS.setInt(key, val);
}

bool NVSStorage::setFloat(const char* key, float val){
    return NVS.setFloat(key, val);
}

bool NVSStorage::setString(const char* key, String string){
    return NVS.setString(key, string);
}

bool NVSStorage::setBlob(const char* key, uint8_t* blob){
    return NVS.setBlob(key, blob, sizeof(blob));
}

/* GETTERS */

int NVSStorage::getInt(const char* key){
    return NVS.getInt(key);
}

float NVSStorage::getFloat(const char* key){
    return NVS.getFloat(key);
}

String NVSStorage::getString(const char* key){
    return NVS.getString(key);
}

uint8_t NVSStorage::getBlobSize(const char* key){
    return NVS.getBlobSize(key);
}

uint8_t* NVSStorage::getBlob(const char* key, uint8_t* blob, uint8_t length){
    NVS.getBlob(key, blob, length);
    return blob;
}