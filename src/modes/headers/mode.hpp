#include <Arduino.h>
#include <NeoPixelBus.h>
#include "../../headers/utils.hpp"

#ifndef MODE_H_INCLUDED
#define MODE_H_INCLUDED

class LedsController;


class Mode {

    protected:
        LedsController *ledsController;
        ModeLabel modeLabel;
        
    public:
        
        Mode(LedsController* ledsController);
        void init();

        virtual void displayMode();
        ModeLabel getModeLabel();

};

#endif