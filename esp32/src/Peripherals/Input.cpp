#include "Input.hpp"

Input::Input(uint8_t pin, unsigned long debounce, int mode)
{
    _input = new ezButton(pin, mode);
    setDebounceTime(debounce);
}

void Input::process()
{
    _input->loop();
}

void Input::setDebounceTime(unsigned long debounce)
{
    _input->setDebounceTime(debounce);
}

bool Input::getState()
{
    return _input->getStateRaw();
}