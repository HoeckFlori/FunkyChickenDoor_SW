#include "Timekeeper.hpp"

Timekeeper::Timekeeper()
    : m_daylightSaving(true) //!!! make this setable
{
    if (!m_myClock.begin())
        Serial.println(F("Could not contact RTC"));
}

DateTime Timekeeper::getCurrentTime()
{
    return m_myClock.now();
}

DateTime Timekeeper::getTodaysSunrise()
{
    DateTime today = m_myClock.now();
    int eventInMinutes = m_dusk2Dawn.sunrise(today.year(), today.month(), today.day(), m_daylightSaving);
    addMinutesToDate(today, eventInMinutes);
    return today;
}

DateTime Timekeeper::getTodaysSunset()
{
    DateTime today = m_myClock.now();
    int eventInMinutes = m_dusk2Dawn.sunset(today.year(), today.month(), today.day(), m_daylightSaving);
    addMinutesToDate(today, eventInMinutes);
    return today;
}

void Timekeeper::setTime(const DateTime &newTime)
{
    m_myClock.adjust(newTime);
}

bool Timekeeper::daylightSavingOn()
{
    return m_daylightSaving;
}

void Timekeeper::addMinutesToDate(DateTime &date, int32_t minutes, bool startOnMidnight)
{
    TimeSpan timeOffset(minutes * 60);
    if (startOnMidnight)
    {
        DateTime newTime(date.year(), date.month(), date.day(),
                         0, 0, 0);
        date = newTime;
    }
    date = date + timeOffset;
}

void Timekeeper::printTimeToConsole(DateTime &date) const
{
    String timeBuffer(F("DD.MM.YYYY hh:mm:ss"));
    date.toString(timeBuffer.begin());
    Serial.println(timeBuffer);
}