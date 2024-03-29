#include "Timekeeper.hpp"
#include "IDataStorage.hpp"

Timekeeper::Timekeeper(IDataStorage *dataStorage, IOperationModeManager *operationModeManager)
    : m_dataStorage(dataStorage)
    , m_operationModeManager(operationModeManager)
    , m_previousOperationMode(operationModeManager->getMode())
    , m_lastQueriedTime(DateTime())
    , m_todaysSunrise(DateTime())
    , m_todaysSunset(DateTime())
    , m_todayOpeningTime(DateTime())
    , m_todayClosingTime(DateTime())
    , m_daylightSaving(false)
{
    // clear listener array
    for (int i = 0; i < c_listenerArraySize; i++)
    {
        m_listenerPtr[i] = NULL;
    }

    // start RTC
    if (!m_myClock.begin())
        Serial.println(F("Could not contact RTC"));

    // setup internals with informations from the non-volatile memory
    if (m_dataStorage)
    {
        auto position = m_dataStorage->getPosition();
        m_dusk2Dawn = new Dusk2Dawn(position._positionLatitude, position._positionLongitude, position._timeZone);

        m_daylightSaving = m_dataStorage->getDayLightSavingSetting();
        m_doNotOpenBeforeOption = m_dataStorage->getDoNotOpenBeforeOption();
        m_closingDelayOption = m_dataStorage->getClosingDelayOption();
        m_artificialMorningLightOption = m_dataStorage->getArtificialMorningLightOption();
    }
    else
    {
        Serial.println(F("ERROR - Timekeeper: no access to IDataStorage"));
    }
}

DateTime &Timekeeper::getCurrentTime()
{
    return m_lastQueriedTime;
}

DateTime &Timekeeper::getTodaysSunrise()
{
    // The here shown solution takes ~1050µ if no new sunrise has to be calculated. The calculation which
    // each call would need ~9000µ.
    DateTime today = m_lastQueriedTime;
    if ((today.day() != m_todaysSunrise.day()) || (today.year() != m_todaysSunrise.year()))
    { // current sunrise not up to date -> update it
        int eventInMinutes = m_dusk2Dawn->sunrise(today.year(), today.month(), today.day(), m_daylightSaving);
        if (eventInMinutes < 0)
        {
            Serial.println("No sunrise expected!");
        }

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
        int eventInMinutes = m_dusk2Dawn->sunset(today.year(), today.month(), today.day(), m_daylightSaving);
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

void Timekeeper::setArtificialMorningLight(int hour, int minute)
{
    m_artificialMorningLightOption._optionEnabled = true;
    m_artificialMorningLightOption._hour = hour;
    m_artificialMorningLightOption._minute = minute;

    if (m_dataStorage)
    {
        m_dataStorage->setArtificialMorningLightOption(m_artificialMorningLightOption);
    }
};

void Timekeeper::disableArtificialMorningLight()
{
    m_artificialMorningLightOption._optionEnabled = false;
    if (m_dataStorage)
    {
        m_dataStorage->setArtificialMorningLightOption(m_artificialMorningLightOption);
    }
};

bool Timekeeper::getArtificialLightState()
{
    // precheck settings, nothing to do if the option is disabled
    if (m_artificialMorningLightOption._optionEnabled == false)
        return false;

    // check light state

    DateTime artificialLightOnTime(m_lastQueriedTime.year(), m_lastQueriedTime.month(), m_lastQueriedTime.day(), m_artificialMorningLightOption._hour,
                                   m_artificialMorningLightOption._minute, 0);

    if ((m_lastQueriedTime >= artificialLightOnTime) && (m_lastQueriedTime <= getTodaysSunrise()))
    { // shall be On
        return true;
    }
    else
    { // shall be Off
        return false;
    }
}

bool Timekeeper::getArtificialLightOptionEnabled() const
{
    return m_artificialMorningLightOption._optionEnabled;
}

DateTime &Timekeeper::getTodayOpeningTime()
{
    if (m_doNotOpenBeforeOption._optionEnabled)
    {
        DateTime doNotOpenBeforeTemp(getTodaysSunrise().year(), getTodaysSunrise().month(), getTodaysSunrise().day(), m_doNotOpenBeforeOption._hour,
                                     m_doNotOpenBeforeOption._minute, 0);

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
    m_todayClosingTime = getTodaysSunset();
    if (m_closingDelayOption._optionEnabled)
    {
        addMinutesToDate(m_todayClosingTime, m_closingDelayOption._minutes, false);
    }
    return m_todayClosingTime;
}

bool Timekeeper::getAutomaticDoorState()
{
    if ((m_lastQueriedTime >= getTodayOpeningTime()) && (m_lastQueriedTime <= getTodayClosingTime()))
    { // shall be open
        return true;
    }
    else
    { // shall be closed
        return false;
    }
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
    delete m_dusk2Dawn;
    m_dusk2Dawn = new Dusk2Dawn(latitude, longitude, timezone);

    // store new position information in the DataStorage
    if (m_dataStorage)
    {
        IDataStorage::positionOption position(latitude, longitude, timezone);
        m_dataStorage->setPosition(position);
    }

    // force to update sunrise/sunset
    m_todaysSunrise = DateTime(2000, 1, 1);
    getTodaysSunrise();
    m_todaysSunset = DateTime(2000, 1, 1);
    getTodaysSunset();
}

void Timekeeper::cycle()
{
    // Query time from RTC
    m_lastQueriedTime = m_myClock.now();

    // check if mode changed during last call
    if (m_previousOperationMode != m_operationModeManager->getMode())
    {
        m_eventHistory.clearHistory();
    }

    // do all the automatic stuff, if the OpMode allows it
    if (m_operationModeManager->getMode() == IOperationModeManager::OpMode::AUTOMATIC)
    {
        // Door activities
        if (getAutomaticDoorState())
        { // shall be open
            m_eventHistory.firedDoorClosing = false;
            if (!m_eventHistory.firedDoorOpening)
            {
                m_eventHistory.firedDoorOpening = true;
                fireAllListener(ITimeKeeperListener::Event::openDoor);
            }
        }
        else
        { // shall be closed
            m_eventHistory.firedDoorOpening = false;
            if (!m_eventHistory.firedDoorClosing)
            {
                m_eventHistory.firedDoorClosing = true;
                fireAllListener(ITimeKeeperListener::Event::closeDoor);
            }
        }

        // Artificial Morning Light activities
        if (getArtificialLightState())
        { // shall be on
            m_eventHistory.firedArtificialLightOff = false;
            if (!m_eventHistory.firedArtificialLightOn)
            {
                m_eventHistory.firedArtificialLightOn = true;
                fireAllListener(ITimeKeeperListener::Event::turnOnArtificialMorningLight);
            }
        }
        else
        { // shall be off
            m_eventHistory.firedArtificialLightOn = false;
            if (!m_eventHistory.firedArtificialLightOff)
            {
                m_eventHistory.firedArtificialLightOff = true;
                fireAllListener(ITimeKeeperListener::Event::turnOffArtificialMorningLight);
            }
        }
    }
}

void Timekeeper::registerEventListener(ITimeKeeperListener *listener)
{
    // find empty position
    bool notPlaceForNewListener(true);
    for (int i(0); i < c_listenerArraySize; i++)
    {
        if (m_listenerPtr[i] == NULL)
        {
            // found empty place for new pointer
            m_listenerPtr[i] = listener;
            notPlaceForNewListener = false;
            break;
        }
    }
    if (notPlaceForNewListener)
    {
        // errorhandling if predefined pointer array is full
        Serial.println("ERROR: No place for a additional TimeKeeper listener!");
    }
}

void Timekeeper::addMinutesToDate(DateTime &date, int32_t minutes, bool startOnMidnight)
{
    TimeSpan timeOffset(minutes * 60);
    if (startOnMidnight)
    {
        DateTime newTime = DateTime(date.year(), date.month(), date.day(), 0, 0, 0);
        date = newTime;
    }
    date = date + timeOffset;
}

void Timekeeper::fireAllListener(ITimeKeeperListener::Event eventToSignalize)
{
    // Fire all existing listeners
    for (int i(0); i < c_listenerArraySize; i++)
    {
        auto listener = m_listenerPtr[i];
        if (listener != NULL)
        {
            listener->eventTimeKeeperListener(eventToSignalize);
        }
    }
}