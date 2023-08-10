#pragma once

#include <Arduino.h>
#include <Preferences.h>

#define PREFERENCES_KEY "settings"

#define T_STARTUP_CMD_KEY "ts"
#define T_STEADY_CMD_KEY "tss"
#define STARTUP_CYCLE_COUNT_CMD_KEY "sc"
#define CYCLE_COUNT_CMD_KEY "c"
#define DIR_SWITCH_DEBOUNCE_CMD_KEY "dsd"
#define RF_DEBOUNCE_CMD_KEY "rfd"
#define LED_MODE_CMD_KEY "led"

#include "../config.hpp"

#define LED_MODE_BLINK 0
#define LED_MODE_ON 1
#define LED_MODE_OFF 2
#define LED_MODE_DIRECTION 3

class Settings
{
private:
    Preferences _preferences;

public:
    int Tstartup;
    int Tsteady;
    int startupCycleCount;
    int cycleCount;
    unsigned long directionSwitchDebounce;
    unsigned long rfDebounce;
    int ledMode;
    Settings();
    void persist();
    void read();
    void print();
    void printHelp();
    void setByCmdKey(String cmdKey, String value);
};