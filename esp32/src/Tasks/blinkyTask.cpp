#include "tasks.hpp"

void blinkyTask(void *parameters)
{
    Serial.println("Blinky task started");

    while (true)
    {
        digitalWrite(LED_BUILTIN, LOW);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        digitalWrite(LED_BUILTIN, HIGH);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}