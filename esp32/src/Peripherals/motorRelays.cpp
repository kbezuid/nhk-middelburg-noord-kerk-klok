#include "motorRelays.hpp"

MotorRelays::MotorRelays(uint8_t relayA, uint8_t relayB)
{
    _relayA = relayA;
    _relayB = relayB;
    pinMode(_relayA, OUTPUT);
    pinMode(_relayB, OUTPUT);
    stop();
}

void MotorRelays::stop()
{
    digitalWrite(_relayA, false);
    digitalWrite(_relayB, false);
}

void MotorRelays::start(bool isA)
{
    if (isA)
    {
        digitalWrite(_relayA, true);
        digitalWrite(_relayB, false);
    }
    else
    {
        digitalWrite(_relayB, true);
        digitalWrite(_relayA, false);
    }
}