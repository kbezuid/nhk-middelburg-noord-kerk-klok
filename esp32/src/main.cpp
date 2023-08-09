#include <Arduino.h>
#include "config.hpp"
#include "Tasks/tasks.hpp"
#include "Settings/settings.hpp"
#include "Commands/commands.hpp"

RfTaskParams rfTaskParams;
MotorsTaskParams motorsTaskParams;
MotorsQueueManager *motorsQueueManager = new MotorsQueueManager();
Settings *settings;
String command;

void setup()
{
  Serial.begin(BUAD_RATE);
  Serial.println("Starting up...");
  Serial.println("Version: " VERSION);
  Serial.println("Author: " AUTHOR);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  settings = new Settings();

  // Create Task Params
  rfTaskParams.rfInput = new Input(RF_INPUT_PIN, RF_INPUT_DEBOUNCE);
  rfTaskParams.motorsQueueManager = motorsQueueManager;

  motorsTaskParams.directionSwitch = new Input(MOTORS_DIRECTION_SWITCH_PIN, MOTORS_DIRECTION_SWITCH_DEBOUNCE);
  motorsTaskParams.motorRelays = new MotorRelays(MOTOR_RELAY_A_PIN, MOTOR_RELAY_B_PIN);
  motorsTaskParams.motorsQueueManager = motorsQueueManager;

  // Create Tasks
  xTaskCreatePinnedToCore(blinkyTask, BLINKY_TASKNAME, BLINKY_HEAPSIZE, NULL, BLINKY_PRIORITY, NULL, BLINKY_CORE);
  // xTaskCreatePinnedToCore(rfTask, RF_TASKNAME, RF_HEAPSIZE, &rfTaskParams, RF_PRIORITY, NULL, RF_CORE);
  xTaskCreatePinnedToCore(motorsTask, MOTORS_TASKNAME, MOTORS_HEAPSIZE, &motorsTaskParams, MOTORS_PRIORITY, NULL, MOTORS_CORE);
}

void loop()
{
  if (Serial.available() > 0)
  {
    command = Serial.readStringUntil('\n');
    command.replace("\r", "");
    command.replace("\n", "");

    if (command.indexOf(CMD_PRINT) >= 0)
    {
      commandPrintSettings(settings);
    }
    else if (command.indexOf(CMD_SAVE) >= 0)
    {
      commandSave(settings);
    }
    else if (command.indexOf(CMD_RESET) >= 0)
    {
      commandReset(settings);
    }
    else if (command.indexOf(CMD_HELP) >= 0)
    {
      commandHelp();
    }
    else if (command.indexOf(CMD_SETH) >= 0)
    {
      commandSettingsHelp();
    }
    else if (command.indexOf(CMD_SET) >= 0)
    {
      commandSet(command, settings);
    }
    else
    {
      Serial.println("Unknown command. Use 'help' to see available commands.");
    }
  }
}