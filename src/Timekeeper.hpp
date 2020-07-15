#pragma once

#include "ITimeKeeper.hpp"
#include "IDataStorage.hpp"
#include "RTClib.h"
#include "Dusk2Dawn.h"

class Timekeeper : public virtual ITimeKeeper
{
public:
    explicit Timekeeper(IDataStorage *dataStorage);

    // ITimeKeeper
    DateTime &getCurrentTime() override;
    DateTime &getTodaysSunrise() override;
    DateTime &getTodaysSunset() override;
    void setTime(const DateTime &newTime) override;
    void setDoNotOpenBefore(int hour, int minute) override;
    void disableDoNotOpenBefore() override;
    DateTime &getTodayOpeningTime() override;
    DateTime &getTodayClosingTime() override;
    void setDaylightSaving(bool daylightSaving) override;
    bool getDaylightSaving() const override;
    void setPositionAndTimezone(float latitude, float longitude, float timezone) override;

private:
    RTC_DS3231 m_myClock = RTC_DS3231();
    Dusk2Dawn m_dusk2Dawn = Dusk2Dawn(47.8144, 12.6352, +1); // todo(FHk) remove this, when the DataStorage is available and initialize it in the ctor

    IDataStorage *m_dataStorage;

    DateTime m_lastQueriedTime;
    DateTime m_todaysSunrise;
    DateTime m_todaysSunset;
    DateTime m_todayOpeningTime;
    DateTime m_todayClosingTime;
    IDataStorage::doNotOpenBeforeOption m_doNotOpenBeforeOption;
    bool m_daylightSaving;

    /**
     * @brief Adds a offset in minutes to a given date
     * 
     * @param date The input to manipulate.
     * @param minutes the Minutes to add
     * @param startOnMidnight Resets the hours, minutes, seconds of the handed TimeDate object (default true)
     */
    void addMinutesToDate(DateTime &date, int32_t minutes, bool startOnMidnight = true);
};