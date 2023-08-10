#pragma once

#include "Settings/settings.hpp"

#define VERSION "0.1.0"
#define AUTHOR "Kerneels Bezuidenhout"
#define BUAD_RATE 115200

#define RF_INPUT_PIN 2
#define RF_INPUT_DEBOUNCE 50

#define MOTORS_DIRECTION_SWITCH_PIN 15
#define MOTOR_RELAY_A_PIN 12
#define MOTOR_RELAY_B_PIN 13

#define DEFAULT_T_STARTUP 10
#define DEFAULT_T_STEADY 10
#define DEFAULT_CYCLE_COUNT 10
#define DEFAULT_STARTUP_CYCLE_COUNT 10
#define DEFAULT_DIR_SWITCH_DEBOUNCE 50
#define DEFAULT_RF_DEBOUNCE 1
#define DEFAULT_LED_MODE (LED_MODE_BLINK)