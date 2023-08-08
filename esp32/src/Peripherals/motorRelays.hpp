#pragma once

#include "Arduino.h"

class MotorRelays
{
private:
    uint8_t _relayA;
    uint8_t _relayB;

public:
    MotorRelays(uint8_t relayA, uint8_t relayB);
    void stop();
    void start(bool isA);
};