#include "tasks.hpp"

void motorsTask(void *parameters)
{
    Serial.println("Motors Task Started");
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
                ringMotors(params->motorRelays, params->directionSwitch);
            }
        }
    }
}

void testMotors(MotorRelays *motorRelays)
{
    motorRelays->start(true);
    vTaskDelay(200 / portTICK_PERIOD_MS);
    motorRelays->stop();
    vTaskDelay(5000 / portTICK_PERIOD_MS);
    motorRelays->start(false);
    vTaskDelay(200 / portTICK_PERIOD_MS);
    motorRelays->stop();
}

void ringMotors(MotorRelays *motors, Input *directionSwitch)
{
    uint32_t currentTime = 0;
    uint32_t deltaTime = 0;
    bool currentDirection = false;
    int tOn = 600;

    for (int cycle = 0; cycle < 6; cycle++)
    {
        Serial.println(currentDirection);
        currentDirection = directionSwitch->getState();
        deltaTime = 0;
        currentTime = millis();
        motors->start(currentDirection);

        if (cycle == 6)
        {
            tOn = 120;
        }

        while (deltaTime < tOn)
        {
            deltaTime = millis() - currentTime;
        }

        motors->stop();
        currentTime = millis();

        currentDirection = !currentDirection;
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
}