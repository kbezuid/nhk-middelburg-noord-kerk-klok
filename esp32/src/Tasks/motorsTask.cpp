#include "tasks.hpp"

void motorsTask(void *parameters)
{
    MotorsTaskParams *params = (MotorsTaskParams *)parameters;

    QueueHandle_t motorsInstructions = *params->motorsQueueManager->GetInstructionQueue();
    MotorInstruction instruction;

    while (true)
    {
        if (xQueueReceive(motorsInstructions, (void *)&instruction, 0) == pdTRUE)
        {
            if (instruction == MotorInstruction::Test)
            {
                Serial.println("Test Instruction Received");
                testMotors(params->motorRelays);
            }

            if (instruction == MotorInstruction::Ring)
            {
                Serial.println("Ring Instruction Received");
                ringMotors(params->motorRelays, params->directionSwitch, params->settings);
            }
        }
    }
}

void testMotors(MotorRelays *motorRelays)
{
    Serial.println("Testing");
    motorRelays->start(true);
    vTaskDelay(200 / portTICK_PERIOD_MS);
    motorRelays->stop();
    vTaskDelay(5000 / portTICK_PERIOD_MS);
    motorRelays->start(false);
    vTaskDelay(200 / portTICK_PERIOD_MS);
    motorRelays->stop();
}

void ringMotors(MotorRelays *motors, Input *directionSwitch, Settings *settings)
{
    Serial.println("Ringing");
    uint32_t currentTime = 0;
    uint32_t deltaTime = 0;
    bool currentDirection = false;
    int tOn = settings->Tstartup;
    int cycles = settings->cycleCount;

    for (int cycle = 0; cycle < cycles; cycle++)
    {
        currentDirection = directionSwitch->getState();
        deltaTime = 0;
        currentTime = millis();
        motors->start(currentDirection);

        if (cycle == settings->startupCycleCount)
        {
            tOn = settings->Tsteady;
        }

        while (deltaTime < tOn)
        {
            deltaTime = millis() - currentTime;
        }

        motors->stop();
        currentTime = millis();

        while (directionSwitch->getState() == currentDirection)
        {
            deltaTime = millis() - currentTime;

            if (deltaTime >= 15000)
            {
                Serial.println("Direction Switch Stuck! Restarting...");
                ESP.restart();
            }
        }
    }

    Serial.println("Ring Complete");
}