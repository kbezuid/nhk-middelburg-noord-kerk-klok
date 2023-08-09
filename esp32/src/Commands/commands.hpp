#pragma once

#include <Arduino.h>
#include "Settings/settings.hpp"

#define CMD_PRINT "print"
#define CMD_SET "set"
#define CMD_SETH "seth"
#define CMD_SAVE "save"
#define CMD_RESET "reset"
#define CMD_HELP "help"

void commandHelp();
void commandPrintSettings(Settings *settings);
void commandSave(Settings *settings);
void commandReset(Settings *settings);
void commandSettingsHelp();
void commandSet(String command, Settings *settings);