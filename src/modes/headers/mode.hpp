#include <Arduino.h>
#include <NeoPixelBus.h>

#ifndef MODE_H_INCLUDED
#define MODE_H_INCLUDED

class LedsController;


class Mode {

    protected:
        LedsController *ledsController;
        
    public:
        
        Mode(LedsController* ledsController);
        void init();

        virtual void displayMode();

};

#endif