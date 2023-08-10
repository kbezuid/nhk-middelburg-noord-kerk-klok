#include "tasks.hpp"

void blinkyTask(void *parameters)
{
    BlinkyTaskParams *params = (BlinkyTaskParams *)parameters;

    while (true)
    {
        if (params->settings->ledMode == LED_MODE_BLINK)
        {
            digitalWrite(LED_BUILTIN, LOW);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            digitalWrite(LED_BUILTIN, HIGH);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }

        if (params->settings->ledMode == LED_MODE_ON)
        {
            digitalWrite(LED_BUILTIN, LOW);
            vTaskDelay(3000 / portTICK_PERIOD_MS);
        }

        if (params->settings->ledMode == LED_MODE_OFF)
        {
            digitalWrite(LED_BUILTIN, HIGH);
            vTaskDelay(3000 / portTICK_PERIOD_MS);
        }

        if (params->settings->ledMode == LED_MODE_DIRECTION)
        {
            digitalWrite(LED_BUILTIN, params->directionSwitch->getState());
            vTaskDelay(100 / portTICK_PERIOD_MS);
        }
    }
}