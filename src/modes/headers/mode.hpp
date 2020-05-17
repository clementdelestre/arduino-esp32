#include <Arduino.h>
#include <NeoPixelBus.h>
#include "../../utils/headers/utils.hpp"

#ifndef MODE_H_INCLUDED
#define MODE_H_INCLUDED

class LedsController;


class Mode {

    protected:
        LedsController *ledsController;
        ModeLabel modeLabel;
        
    public:
        
        Mode(LedsController* ledsController);
        virtual void init();

        virtual void displayMode();
        
        virtual void startMode();
        virtual void stopMode();

        virtual void sendModeData();

        ModeLabel getModeLabel();

};

#endif