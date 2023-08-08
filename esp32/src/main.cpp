#include <Arduino.h>
#include "config.hpp"
#include "Tasks/tasks.hpp"

int myFunction(int, int);

void setup()
{
  Serial.begin(BUAD_RATE);
  Serial.println("Starting up...");
  Serial.println("Version: " VERSION);
  Serial.println("Author: " AUTHOR);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  // Create Tasks
  xTaskCreatePinnedToCore(blinkyTask, BLINKY_TASKNAME, BLINKY_HEAPSIZE, NULL, BLINKY_PRIORITY, NULL, BLINKY_CORE);
}

void loop()
{
}