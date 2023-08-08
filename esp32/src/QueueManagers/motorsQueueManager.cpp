#include "motorsQueueManager.hpp"

MotorsQueueManager::MotorsQueueManager() {
  _motorsInstructions = xQueueCreate(1, sizeof(MotorInstruction));
}

bool MotorsQueueManager::sendTestInstruction() {
  _instruction = MotorInstruction::Test;
  return _sendInstruction();
}

bool MotorsQueueManager::sendRingInstruction() {
  _instruction = MotorInstruction::Ring;
  return _sendInstruction();
}

QueueHandle_t* MotorsQueueManager::GetInstructionQueue() {
  return &_motorsInstructions;
}

bool MotorsQueueManager::_sendInstruction() {
  if (xQueueSend(_motorsInstructions, (void *)&_instruction, 10) != pdTRUE) {
    Serial.println("Motor Instructions Full");
    return false;
  }

  return true;
}