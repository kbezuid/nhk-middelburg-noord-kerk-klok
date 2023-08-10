#pragma once

#include <Arduino.h>
#include "Settings/settings.hpp"
#include "../QueueManagers/motorsQueueManager.hpp"

#define CMD_PRINT "print"
#define CMD_SET "set"
#define CMD_SETH "seth"
#define CMD_SAVE "save"
#define CMD_RESET "reset"
#define CMD_HELP "help"
#define CMD_TEST "test"
#define CMD_RING "ring"

class Commands
{
private:
    Settings *_settings;
    MotorsQueueManager *_motorQueueManager;

    void commandHelp();
    void commandPrintSettings();
    void commandSave();
    void commandReset();
    void commandSettingsHelp();
    void commandSet(String command);
    void commandTest();
    void commandRing();

public:
    Commands(Settings *settings, MotorsQueueManager *motorsQueueManager);
    void execute(String command);
};
