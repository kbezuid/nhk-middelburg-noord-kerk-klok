#include "settings.hpp"

Settings::Settings()
{
    _preferences.begin(PREFERENCES_KEY);
    read();
}

void Settings::read()
{
    _preferences.begin(PREFERENCES_KEY);
    Tstartup = _preferences.getInt(T_STARTUP_CMD_KEY, DEFAULT_T_STARTUP);
    Tsteady = _preferences.getInt(T_STEADY_CMD_KEY, DEFAULT_T_STEADY);
    cycleCount = _preferences.getInt(CYCLE_COUNT_CMD_KEY, DEFAULT_CYCLE_COUNT);
    startupCycleCount = _preferences.getInt(STARTUP_CYCLE_COUNT_CMD_KEY, DEFAULT_STARTUP_CYCLE_COUNT);
    directionSwitchDebounce = _preferences.getULong(DIR_SWITCH_DEBOUNCE_CMD_KEY, DEFAULT_DIR_SWITCH_DEBOUNCE);
    _preferences.end();
}

void Settings::persist()
{
    _preferences.begin(PREFERENCES_KEY);
    _preferences.putInt(T_STARTUP_CMD_KEY, Tstartup);
    _preferences.putInt(T_STEADY_CMD_KEY, Tsteady);
    _preferences.putInt(CYCLE_COUNT_CMD_KEY, cycleCount);
    _preferences.putInt(STARTUP_CYCLE_COUNT_CMD_KEY, startupCycleCount);
    _preferences.putULong(DIR_SWITCH_DEBOUNCE_CMD_KEY, directionSwitchDebounce);
    _preferences.end();
}

void Settings::print()
{
    Serial.println("Startup Time (" T_STARTUP_CMD_KEY "): " + String(Tstartup) + " (ms)");
    Serial.println("Steady Time (" T_STEADY_CMD_KEY "): " + String(Tsteady) + " (ms)");
    Serial.println("Startup Cycle Count: (" STARTUP_CYCLE_COUNT_CMD_KEY "): " + String(startupCycleCount));
    Serial.println("Cycle Count: (" CYCLE_COUNT_CMD_KEY "): " + String(cycleCount));
    Serial.println("Direction Switch Debounce : (" DIR_SWITCH_DEBOUNCE_CMD_KEY "): " + String(directionSwitchDebounce) + "(ms)");
}

void Settings::setByCmdKey(String cmdKey, String value)
{
    if (cmdKey == T_STARTUP_CMD_KEY)
    {
        Tstartup = value.toInt();
    }
    else if (cmdKey == T_STEADY_CMD_KEY)
    {
        Tsteady = value.toInt();
    }
    else if (cmdKey == STARTUP_CYCLE_COUNT_CMD_KEY)
    {
        startupCycleCount = value.toInt();
    }
    else if (cmdKey == CYCLE_COUNT_CMD_KEY)
    {
        cycleCount = value.toInt();
    }
    else if (cmdKey == DIR_SWITCH_DEBOUNCE_CMD_KEY)
    {
        directionSwitchDebounce = value.toInt();
    }
    else
    {
        Serial.println("Unknown setting: " + cmdKey + " with value: " + value);
    }
}