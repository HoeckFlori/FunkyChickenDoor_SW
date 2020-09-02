#include "BacklightControl.hpp"
#include "Arduino.h"


BacklightControl::BacklightControl(int outputPin)
 : c_tftDimmingControlPin(outputPin),
   m_defaultIlluminance(100),
   m_dimmedIlluminance(50)
{
    pinMode(c_tftDimmingControlPin, OUTPUT);
    activateDefaultIlluminance();
}

void BacklightControl::setDefaultIlluminance(uint8_t percent)
{
    m_defaultIlluminance = percent;
}

void BacklightControl::setDimmedIlluminance(uint8_t percent)
{
    m_dimmedIlluminance = percent;
}

void BacklightControl::activateDefaultIlluminance()
{
    analogWrite(c_tftDimmingControlPin, int16_t(m_defaultIlluminance) * 255 / 100); // analogWrite values from 0 to 255
}

void BacklightControl::activateDimmedIlluminance()
{
    analogWrite(c_tftDimmingControlPin, int16_t(m_dimmedIlluminance) * 255 / 100); // analogWrite values from 0 to 255
}

void BacklightControl::deactivateBacklight()
{
    analogWrite(c_tftDimmingControlPin, 0);
}

void BacklightControl::updateAboutSystemPowerState(SystemPowerStates newState)
{
    switch (newState)
    {
    case SystemPowerStates::NORMAL:
        activateDefaultIlluminance();
        break;
    case SystemPowerStates::ENERGYSAVING:
        activateDimmedIlluminance();
        break;
    }
}