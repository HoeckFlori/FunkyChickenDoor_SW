#include "MainControl.hpp"
#include <Arduino.h>

MainControl *m_mainControl;

void setup(void)
{
    m_mainControl = new MainControl();
}

void loop()
{
    m_mainControl->cycle();
}