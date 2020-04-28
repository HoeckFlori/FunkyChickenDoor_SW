#include <Arduino.h>
#include "MainControl.hpp"

MainControl m_mainControl = MainControl();

void setup(void)
{
  m_mainControl.init();
}

void loop()
{
  m_mainControl.cycle();
}
