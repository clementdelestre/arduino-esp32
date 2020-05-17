#include <Arduino.h>
#include "mode.hpp"

#ifndef POWER_OFF_MODE_H_INCLUDED
#define POWER_OFF_MODE_H_INCLUDED

class LedsController;


class PowerOffMode : public Mode {

    public:
        PowerOffMode(LedsController* ledsController);
        void displayMode() override; 
        void startMode() override;

};

#endif