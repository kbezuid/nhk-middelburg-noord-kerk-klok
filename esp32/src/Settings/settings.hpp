#pragma once

#include <Arduino.h>
#include <Preferences.h>

#define PREFERENCES_KEY "settings"

#define T_STARTUP_CMD_KEY "ts"
#define T_STEADY_CMD_KEY "tss"
#define STARTUP_CYCLE_COUNT_CMD_KEY "sc"
#define CYCLE_COUNT_CMD_KEY "c"

#include "../config.hpp"

class Settings
{
private:
    Preferences _preferences;

public:
    int Tstartup;
    int Tsteady;
    int startupCycleCount;
    int cycleCount;
    Settings();
    void persist();
    void read();
    void print();
    void setByCmdKey(String cmdKey, String value);
};