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

void commandHelp();
void commandPrintSettings(Settings *settings);
void commandSave(Settings *settings);
void commandReset(Settings *settings);
void commandSettingsHelp(Settings *settings);
void commandSet(String command, Settings *settings);
void commandTest(MotorsQueueManager *motorsQueueManager);