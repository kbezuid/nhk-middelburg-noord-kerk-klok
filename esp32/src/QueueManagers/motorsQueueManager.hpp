#pragma once

#include <Arduino.h>
#include "../Instructions/motorInstructions.hpp"

class MotorsQueueManager
{
private:
    QueueHandle_t _motorsInstructions;
    MotorInstruction _instruction;
    bool _sendInstruction();

public:
    MotorsQueueManager();
    bool sendTestInstruction();
    bool sendRingInstruction();
    QueueHandle_t *GetInstructionQueue();
};
