#include "tasks.hpp"

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
            vTaskDelay(5000 / portTICK_PERIOD_MS);
        }
    }
}