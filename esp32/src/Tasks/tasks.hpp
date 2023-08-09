#pragma once

#include <Arduino.h>
#include "../Peripherals/input.hpp"
#include "../Peripherals/motorRelays.hpp"
#include "../QueueManagers/motorsQueueManager.hpp"

// Blinky Task
#define BLINKY_TASKNAME "blinky"
#define BLINKY_HEAPSIZE 1024
#define BLINKY_CORE 1
#define BLINKY_PRIORITY 1

void blinkyTask(void *parameters);

// RF Task
#define RF_TASKNAME "rf"
#define RF_HEAPSIZE 1024
#define RF_CORE 1
#define RF_PRIORITY 1

void rfTask(void *parameters);

struct RfTaskParams
{
    Input *rfInput;
    MotorsQueueManager *motorsQueueManager;
};

// Motors Task
#define MOTORS_TASKNAME "motors"
#define MOTORS_HEAPSIZE 2048
#define MOTORS_CORE 1
#define MOTORS_PRIORITY 1

struct MotorsTaskParams
{
    Input *directionSwitch;
    MotorRelays *motorRelays;
    MotorsQueueManager *motorsQueueManager;
};

void motorsTask(void *parameters);
void testMotors(MotorRelays *motorRelays);
void ringMotors(MotorRelays *motors, Input *directionSwitch);