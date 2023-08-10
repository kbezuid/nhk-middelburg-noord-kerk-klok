#include "tasks.hpp"

#define MINUTE_IN_MS 60000

void rfTask(void *parameters)
{
    RfTaskParams *params = (RfTaskParams *)parameters;

    while (true)
    {
        params->rfInput->process();

        if (params->rfInput->getState())
        {
            Serial.println("RF Remote Button Pressed");
            params->motorsQueueManager->sendRingInstruction();
            vTaskDelay(params->settings->rfDebounce * MINUTE_IN_MS / portTICK_PERIOD_MS);
        }
    }
}