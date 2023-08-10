#include "commands.hpp"

void commandHelp()
{
    Serial.println("Commands:");
    Serial.println(CMD_PRINT " - print settings");
    Serial.println(CMD_SET " - set setting/s");
    Serial.println(CMD_SETH " - help for set command");
    Serial.println(CMD_SAVE " - save settings to memory");
    Serial.println(CMD_RESET " - reset settings to what is saved in memory");
    Serial.println(CMD_TEST " - test bell motors by moving in both directions");
}

void commandPrintSettings(Settings *settings)
{
    Serial.println("Printing settings...");
    settings->print();
}

void commandSave(Settings *settings)
{
    Serial.println("Saving settings...");
    settings->persist();
    settings->print();
}

void commandReset(Settings *settings)
{
    Serial.println("Resetting settings...");
    settings->read();
    settings->print();
}

void commandSettingsHelp(Settings *settings)
{
    Serial.println(CMD_SET " <setting> <value>");
    Serial.println("Settings:");
    settings->printHelp();
    Serial.println("Example: set " T_STARTUP_CMD_KEY " 1000");
    Serial.println("Multiple settings can be set at once by seperating them with a space");
    Serial.println("Example: set " T_STARTUP_CMD_KEY " 1000 " T_STEADY_CMD_KEY " 400");
}

void commandSet(String command, Settings *settings)
{
    Serial.println("Setting settings...");
    command.replace(CMD_SET " ", "");
    String currentCmdKey = "";
    String currentCmdValue = "";
    int i = 0;
    char currentChar = '!';
    bool valueStarted = false;
    bool isEnd = false;

    while (i < command.length())
    {
        currentChar = command.charAt(i);

        isEnd = i == command.length() - 1;

        if (currentChar == ' ' || isEnd)
        {
            if (isEnd)
            {
                if (valueStarted)
                {
                    currentCmdValue += currentChar;
                }
                else
                {
                    currentCmdKey += currentChar;
                }
            }

            if (valueStarted)
            {
                settings->setByCmdKey(currentCmdKey, currentCmdValue);
                valueStarted = false;
                currentCmdKey = "";
                currentCmdValue = "";
            }
            else
            {
                valueStarted = true;
            }
        }
        else if (valueStarted)
        {
            currentCmdValue += currentChar;
        }
        else
        {
            currentCmdKey += currentChar;
        }

        i++;
    }

    settings->print();
}

void commandTest(MotorsQueueManager *motorsQueueManager)
{
    Serial.println("Testing motors...");
    motorsQueueManager->sendTestInstruction();
}