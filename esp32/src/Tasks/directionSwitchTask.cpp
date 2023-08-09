#include "tasks.hpp"

void directionSwitchTask(void *parameters)
{
    DirectionSwitchTaskParams *params = (DirectionSwitchTaskParams *)parameters;

    while (true)
    {
        params->directionSwitch->process();
    }
}