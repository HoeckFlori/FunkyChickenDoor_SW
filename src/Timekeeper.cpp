#include "Timekeeper.hpp"

Timekeeper::Timekeeper()
{
    if (!m_myClock.begin())
        Serial.println(F("Could not contact RTC"));
}

DateTime Timekeeper::getCurrentTime()
{
    return m_myClock.now();
}

void Timekeeper::setTime(const DateTime &newTime)
{
    m_myClock.adjust(newTime);
}

// ITimeKeeper::DoorState Timekeeper::getTimeDependentDoorState()
// {
//     // fill me with code
// }