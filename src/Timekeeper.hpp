#pragma once

#include "ITimeKeeper.hpp"
#include "RTClib.h"
#include "Dusk2Dawn.h"

// forward declaration
class IDataStorage;

class Timekeeper : public virtual ITimeKeeper
{
public:
    explicit Timekeeper(IDataStorage *dataStorage);

    // ITimeKeeper
    DateTime getCurrentTime() override;
    DateTime getTodaysSunrise() override;
    DateTime getTodaysSunset() override;
    void setTime(const DateTime &newTime) override;
    void setDaylightSaving(bool daylightSaving) override;
    bool getDaylightSaving() const override;
    void setPositionAndTimezone(float latitude, float longitude, float timezone) override;

private:
    RTC_DS3231 m_myClock = RTC_DS3231();
    Dusk2Dawn m_dusk2Dawn = Dusk2Dawn(47.8144, 12.6352, +1); // todo(FHk) remove this, when the DataStorage is available and initialize it in the ctor

    IDataStorage *m_dataStorage;

    bool m_daylightSaving;

    /**
     * @brief Adds a offset in minutes to a given date
     * 
     * @param date The input to manipulate.
     * @param minutes the Minutes to add
     * @param startOnMidnight Resets the hours, minutes, seconds of the handed TimeDate object (default true)
     */
    void addMinutesToDate(DateTime &date, int32_t minutes, bool startOnMidnight = true);

    /**
    * @brief Helper function to print the parameter date to the serial console
    * 
    * @param date The to printed DateTime object
    */
    void printTimeToConsole(DateTime &date) const;
};