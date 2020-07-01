#include "Timekeeper.hpp"
#include "IDataStorage.hpp"

Timekeeper::Timekeeper(IDataStorage *dataStorage) : m_lastQueriedTime(DateTime()),
                                                    m_todaysSunrise(DateTime()),
                                                    m_todaysSunset(DateTime()),
                                                    m_dataStorage(dataStorage),
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

DateTime &Timekeeper::getCurrentTime()
{
    m_lastQueriedTime = m_myClock.now();
    return m_lastQueriedTime;
}

DateTime &Timekeeper::getTodaysSunrise()
{
    // The here shown solution takes ~1050µ if no new sunrise has to be calculated. The calculation which
    // each call would need ~9000µ.
    DateTime today = m_lastQueriedTime;
    if ((today.day() != m_todaysSunset.day()) || (today.year() != m_todaysSunset.year()))
    { // current sunrise not up to date -> update it
        int eventInMinutes = m_dusk2Dawn.sunrise(today.year(), today.month(), today.day(), m_daylightSaving);
        m_todaysSunrise = today;
        addMinutesToDate(m_todaysSunrise, eventInMinutes);
    }
    return m_todaysSunrise;
}

DateTime &Timekeeper::getTodaysSunset()
{
    // The here shown solution takes ~1050µ if no new sunrise has to be calculated. The calculation which
    // each call would need ~9000µ.
    DateTime today = m_lastQueriedTime;
    if ((today.day() != m_todaysSunset.day()) || (today.year() != m_todaysSunset.year()))
    { // current sunrise not up to date -> update it
        int eventInMinutes = m_dusk2Dawn.sunset(today.year(), today.month(), today.day(), m_daylightSaving);
        m_todaysSunset = today;
        addMinutesToDate(m_todaysSunset, eventInMinutes);
    }
    return m_todaysSunset;
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