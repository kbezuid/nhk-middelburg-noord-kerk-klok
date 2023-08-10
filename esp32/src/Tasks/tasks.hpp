#pragma once

#include <Arduino.h>
#include "../Peripherals/input.hpp"
#include "../Peripherals/motorRelays.hpp"
#include "../QueueManagers/motorsQueueManager.hpp"
#include "../Settings/settings.hpp"

// Blinky Task
#define BLINKY_TASKNAME "blinky"
#define BLINKY_HEAPSIZE 1024
#define BLINKY_CORE 1
#define BLINKY_PRIORITY 1

void blinkyTask(void *parameters);

struct BlinkyTaskParams
{
    Settings *settings;
    Input *directionSwitch;
};

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
    Settings *settings;
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
    Settings *settings;
};

void motorsTask(void *parameters);
void testMotors(MotorRelays *motorRelays);
void ringMotors(MotorRelays *motors, Input *directionSwitch, Settings *settings);

// Direction Switch Task
#define DIRECTION_SWITCH_TASKNAME "directionSwitch"
#define DIRECTION_SWITCH_HEAPSIZE 1024
#define DIRECTION_SWITCH_CORE 1
#define DIRECTION_SWITCH_PRIORITY 1

void directionSwitchTask(void *parameters);

struct DirectionSwitchTaskParams
{
    Input *directionSwitch;
};