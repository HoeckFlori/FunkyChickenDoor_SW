#pragma once

#include "ITimeKeeper.hpp"
//#include <DS3232RTC.h> // https://github.com/JChristensen/DS3232RTC
#include "RTClib.h"

class Timekeeper : public virtual ITimeKeeper
{
public:
    explicit Timekeeper();

    // ITimeKeeper
    DateTime getCurrentTime() override;
    void setTime(const DateTime &newTime) override;

private:
    RTC_DS3231 m_myClock = RTC_DS3231();
};