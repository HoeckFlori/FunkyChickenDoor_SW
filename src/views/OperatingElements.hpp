#pragma once

#include <JC_Button.h>
#include "IOperatingElements.hpp"

class OperatingElements : public virtual IOperatingElements
{
public:
    OperatingElements();
    ~OperatingElements() = default;

    void cycle() override;

private:
    // Button(pin, dbTime, puEnable, invert) instantiates a button object.
    //
    // Required parameter:
    // pin      The Arduino pin the button is connected to
    //
    // Optional parameters:
    // dbTime   Debounce time in milliseconds (default 25ms)
    // puEnable true to enable the AVR internal pullup resistor (default true)
    // invert   true to interpret a low logic level as pressed (default true)

    const int m_defaultDebounceTime = 40; // ms

    Button m_backButton;
    Button m_enterButton;
    Button m_upButton;
    Button m_downButton;
};