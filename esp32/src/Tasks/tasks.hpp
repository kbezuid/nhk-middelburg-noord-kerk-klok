#pragma once

#define BLINKY_TASKNAME "blinky"
#define BLINKY_HEAPSIZE 1024
#define BLINKY_CORE 1
#define BLINKY_PRIORITY 1

void blinkyTask(void *parameters);