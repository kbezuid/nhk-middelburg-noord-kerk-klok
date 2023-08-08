#pragma once

#include <ezButton.h>

class Input
{
private:
    ezButton *_input;

public:
    Input(uint8_t pin, unsigned long debounde);
    void process();
    void setDebounceTime(unsigned long debounce);
    bool getState();
};