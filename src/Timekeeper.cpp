#include "Timekeeper.hpp"
#include "IDataStorage.hpp"

Timekeeper::Timekeeper(IDataStorage *dataStorage) : m_dataStorage(dataStorage),
                                                    m_daylightSaving(false)
{
    if (!m_myClock.begin())
        Serial.println(F("Could not contact RTC"));
    if (m_dataStorage)
    {
        m_daylightSaving = m_dataStorage->getDayLightSavingSetting();
    }
    else
    {
        Serial.println(F("ERROR - Timekeeper: no access to IDataStorage"));
    }
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

void Timekeeper::setDaylightSaving(bool daylightSaving)
{
    m_daylightSaving = daylightSaving;
    if (m_dataStorage)
    {
        m_dataStorage->setDayLightSavingSetting(daylightSaving);
    }
}

bool Timekeeper::getDaylightSaving() const
{
    return m_daylightSaving;
}

void Timekeeper::setPositionAndTimezone(float latitude, float longitude, float timezone)
{
    // build new Dusk2Dawn engine
    m_dusk2Dawn = Dusk2Dawn(latitude, longitude, timezone);

    // store new position information in the DataStorage
    if (m_dataStorage)
    {
        m_dataStorage->setPosition(latitude, longitude, timezone);
    }
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