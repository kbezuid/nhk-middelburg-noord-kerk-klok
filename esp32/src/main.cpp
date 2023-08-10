#include <Arduino.h>
#include "config.hpp"
#include "Tasks/tasks.hpp"
#include "Settings/settings.hpp"
#include "Commands/commands.hpp"

MotorsQueueManager *motorsQueueManager = new MotorsQueueManager();
Settings *settings;
String command;
Input *directionSwitch = new Input(MOTORS_DIRECTION_SWITCH_PIN, DEFAULT_DIR_SWITCH_DEBOUNCE, INPUT_PULLUP);
Commands *commands;

// Task Parameters
BlinkyTaskParams blinkyTaskParams;
RfTaskParams rfTaskParams;
MotorsTaskParams motorsTaskParams;
DirectionSwitchTaskParams directionSwitchTaskParams;

void applySettings()
{
  directionSwitch->setDebounceTime(settings->directionSwitchDebounce);
}

void setup()
{
  Serial.begin(BUAD_RATE);
  Serial.println("Starting up...");
  Serial.println("Version: " VERSION);
  Serial.println("Author: " AUTHOR);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  settings = new Settings();
  commands = new Commands(settings, motorsQueueManager);

  // Create Task Params
  blinkyTaskParams.settings = settings;
  blinkyTaskParams.directionSwitch = directionSwitch;

  rfTaskParams.rfInput = new Input(RF_INPUT_PIN, RF_INPUT_DEBOUNCE);
  rfTaskParams.motorsQueueManager = motorsQueueManager;
  rfTaskParams.settings = settings;

  motorsTaskParams.directionSwitch = directionSwitch;
  motorsTaskParams.motorRelays = new MotorRelays(MOTOR_RELAY_A_PIN, MOTOR_RELAY_B_PIN);
  motorsTaskParams.motorsQueueManager = motorsQueueManager;
  motorsTaskParams.settings = settings;

  directionSwitchTaskParams.directionSwitch = directionSwitch;

  applySettings();
  commands->execute(CMD_HELP);

  // Create Tasks
  xTaskCreatePinnedToCore(blinkyTask, BLINKY_TASKNAME, BLINKY_HEAPSIZE, &blinkyTaskParams, BLINKY_PRIORITY, NULL, BLINKY_CORE);
  xTaskCreatePinnedToCore(rfTask, RF_TASKNAME, RF_HEAPSIZE, &rfTaskParams, RF_PRIORITY, NULL, RF_CORE);
  xTaskCreatePinnedToCore(directionSwitchTask, DIRECTION_SWITCH_TASKNAME, DIRECTION_SWITCH_HEAPSIZE, &directionSwitchTaskParams, DIRECTION_SWITCH_PRIORITY, NULL, DIRECTION_SWITCH_CORE);
  xTaskCreatePinnedToCore(motorsTask, MOTORS_TASKNAME, MOTORS_HEAPSIZE, &motorsTaskParams, MOTORS_PRIORITY, NULL, MOTORS_CORE);
}

void loop()
{
  if (Serial.available() > 0)
  {
    command = Serial.readStringUntil('\n');
    command.replace("\r", "");
    command.replace("\n", "");
    commands->execute(command);
    applySettings();
  }
}