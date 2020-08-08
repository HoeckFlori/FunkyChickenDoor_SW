#include "Timekeeper.hpp"
#include "IDataStorage.hpp"

Timekeeper::Timekeeper(IDataStorage *dataStorage) : m_dataStorage(dataStorage),
                                                    m_lastQueriedTime(DateTime()),
                                                    m_todaysSunrise(DateTime()),
                                                    m_todaysSunset(DateTime()),
                                                    m_todayOpeningTime(DateTime()),
                                                    m_todayClosingTime(DateTime()),
                                                    m_daylightSaving(false)
{
    if (!m_myClock.begin())
        Serial.println(F("Could not contact RTC"));
    if (m_dataStorage)
    {
        m_daylightSaving = m_dataStorage->getDayLightSavingSetting();
        m_doNotOpenBeforeOption = m_dataStorage->getDoNotOpenBeforeOption();
        m_closingDelayOption = m_dataStorage->getClosingDelayOption();
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

void Timekeeper::setDoNotOpenBefore(int hour, int minute)
{
    m_doNotOpenBeforeOption._optionEnabled = true;
    m_doNotOpenBeforeOption._hour = hour;
    m_doNotOpenBeforeOption._minute = minute;

    if (m_dataStorage)
    {
        m_dataStorage->setDoNotOpenBeforeOption(m_doNotOpenBeforeOption);
    }
}

void Timekeeper::disableDoNotOpenBefore()
{
    m_doNotOpenBeforeOption._optionEnabled = false;
    if (m_dataStorage)
    {
        m_dataStorage->setDoNotOpenBeforeOption(m_doNotOpenBeforeOption);
    }
}

void Timekeeper::setClosingDelay(uint16_t mm)
{
    m_closingDelayOption._optionEnabled = true;
    m_closingDelayOption._minutes = mm;

    if (m_dataStorage)
    {
        m_dataStorage->setClosingDelayOption(m_closingDelayOption);
    }
}

void Timekeeper::disableClosingDelay()
{
    m_closingDelayOption._optionEnabled = false;
    if (m_dataStorage)
    {
        m_dataStorage->setClosingDelayOption(m_closingDelayOption);
    }
}


DateTime &Timekeeper::getTodayOpeningTime()
{
    if (m_doNotOpenBeforeOption._optionEnabled)
    {
        DateTime doNotOpenBeforeTemp(getTodaysSunrise().year(),
                                     getTodaysSunrise().month(),
                                     getTodaysSunrise().day(),
                                     m_doNotOpenBeforeOption._hour,
                                     m_doNotOpenBeforeOption._minute,
                                     0);

        if (m_todaysSunrise >= doNotOpenBeforeTemp)
        { // the today sunrise is later the the 'not open before limitation'
            m_todayOpeningTime = m_todaysSunrise;
        }
        else
        { // the todays sunrise would be before the allowed opening time. Limit this.
            m_todayOpeningTime = doNotOpenBeforeTemp;
        }
    }
    else
    { // opening time is the sunrise time, like the cock prefers
        m_todayOpeningTime = m_todaysSunrise;
    }
    return m_todayOpeningTime;
}

DateTime &Timekeeper::getTodayClosingTime()
{
    m_todayClosingTime = m_todaysSunset;
    if (m_closingDelayOption._optionEnabled)
    {
        addMinutesToDate(m_todayClosingTime, m_closingDelayOption._minutes, false);
    }
    return m_todayClosingTime;
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
        DateTime newTime = DateTime(date.year(), date.month(), date.day(), 0, 0, 0 );
        date = newTime;
    }
    date = date + timeOffset;
}