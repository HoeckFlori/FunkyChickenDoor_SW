#include "BacklightControl.hpp"
#include "Arduino.h"


BacklightControl::BacklightControl(int outputPin, uint8_t initialDefaultIlluminance, uint8_t initialDimmedIlluminance)
 : c_tftDimmingControlPin(outputPin),
   m_defaultIlluminance(initialDefaultIlluminance),
   m_dimmedIlluminance(initialDimmedIlluminance)
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
    analogWrite(c_tftDimmingControlPin, int16_t(100-m_defaultIlluminance) * 255 / 100); // analogWrite values from 0 to 255
}

void BacklightControl::activateDimmedIlluminance()
{
    analogWrite(c_tftDimmingControlPin, int16_t(100-m_dimmedIlluminance) * 255 / 100); // analogWrite values from 0 to 255
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