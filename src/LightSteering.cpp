#include "LightSteering.hpp"
#include "Arduino.h"

LightSteering::LightSteering(int lightPin)
    : c_lightPin(lightPin)
    , m_lightStatus(false)
{
    pinMode(lightPin, OUTPUT);
    digitalWrite(c_lightPin, LOW);
}

void LightSteering::switchLightOn()
{
    m_lightStatus = true;
    digitalWrite(c_lightPin, HIGH);
}

void LightSteering::switchLightOff()
{
    m_lightStatus = false;
    digitalWrite(c_lightPin, LOW);
}

bool LightSteering::getLightStatus() const
{
    return m_lightStatus;
}

void LightSteering::eventTimeKeeperListener(ITimeKeeperListener::Event event)
{
    if (event == ITimeKeeperListener::Event::turnOnArtificialMorningLight)
    {
        switchLightOn();
    }
    else if (event == ITimeKeeperListener::Event::turnOffArtificialMorningLight)
    {
        switchLightOff();
    }
}
