#include "commands.hpp"

Commands::Commands(Settings *settings, MotorsQueueManager *motorsQueueManager)
{
    _settings = settings;
    _motorQueueManager = motorsQueueManager;
}

void Commands::execute(String command)
{
    if (command == CMD_HELP)
    {
        commandHelp();
    }
    else if (command == CMD_PRINT)
    {
        commandPrintSettings();
    }
    else if (command == CMD_SAVE)
    {
        commandSave();
    }
    else if (command == CMD_RESET)
    {
        commandReset();
    }
    else if (command == CMD_TEST)
    {
        commandTest();
    }
    else if (command.startsWith(CMD_SET))
    {
        commandSet(command);
    }
    else if (command.startsWith(CMD_SETH))
    {
        commandSettingsHelp();
    }
    else
    {
        Serial.println("Unknown command");
    }
}

void Commands::commandHelp()
{
    Serial.println("Commands:");
    Serial.println(CMD_PRINT " - print settings");
    Serial.println(CMD_SET " - set setting/s");
    Serial.println(CMD_SETH " - help for set command");
    Serial.println(CMD_SAVE " - save settings to memory");
    Serial.println(CMD_RESET " - reset settings to what is saved in memory");
    Serial.println(CMD_TEST " - test bell motors by moving in both directions");
}

void Commands::commandPrintSettings()
{
    Serial.println("Printing settings...");
    _settings->print();
}

void Commands::commandSave()
{
    Serial.println("Saving settings...");
    _settings->persist();
    _settings->print();
}

void Commands::commandReset()
{
    Serial.println("Resetting settings...");
    _settings->read();
    _settings->print();
}

void Commands::commandSettingsHelp()
{
    Serial.println(CMD_SET " <setting> <value>");
    Serial.println("Settings:");
    _settings->printHelp();
    Serial.println("Example: set " T_STARTUP_CMD_KEY " 1000");
    Serial.println("Multiple settings can be set at once by seperating them with a space");
    Serial.println("Example: set " T_STARTUP_CMD_KEY " 1000 " T_STEADY_CMD_KEY " 400");
}

void Commands::commandSet(String command)
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
                _settings->setByCmdKey(currentCmdKey, currentCmdValue);
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

    _settings->print();
}

void Commands::commandTest()
{
    Serial.println("Testing motors...");
    _motorQueueManager->sendTestInstruction();
}