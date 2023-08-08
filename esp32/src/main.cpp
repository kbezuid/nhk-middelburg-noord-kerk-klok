#include <Arduino.h>
#include "config.hpp"
#include "Tasks/tasks.hpp"

RfTaskParams rfTaskParams;
MotorsTaskParams motorsTaskParams;
MotorsQueueManager *motorsQueueManager = new MotorsQueueManager();

void setup()
{
  Serial.begin(BUAD_RATE);
  Serial.println("Starting up...");
  Serial.println("Version: " VERSION);
  Serial.println("Author: " AUTHOR);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  // Create Task Params
  rfTaskParams.rfInput = new Input(RF_INPUT_PIN, RF_INPUT_DEBOUNCE);
  rfTaskParams.motorsQueueManager = motorsQueueManager;

  motorsTaskParams.directionSwitch = new Input(MOTORS_DIRECTION_SWITCH_PIN, MOTORS_DIRECTION_SWITCH_DEBOUNCE);
  motorsTaskParams.motorRelays = new MotorRelays(MOTOR_RELAY_A_PIN, MOTOR_RELAY_B_PIN);
  motorsTaskParams.motorsQueueManager = motorsQueueManager;

  // Create Tasks
  xTaskCreatePinnedToCore(blinkyTask, BLINKY_TASKNAME, BLINKY_HEAPSIZE, NULL, BLINKY_PRIORITY, NULL, BLINKY_CORE);
  xTaskCreatePinnedToCore(rfTask, RF_TASKNAME, RF_HEAPSIZE, &rfTaskParams, RF_PRIORITY, NULL, RF_CORE);
  xTaskCreatePinnedToCore(motorsTask, MOTORS_TASKNAME, MOTORS_HEAPSIZE, &motorsTaskParams, MOTORS_PRIORITY, NULL, MOTORS_CORE);
}

void loop()
{
}