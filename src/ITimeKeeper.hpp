#pragma once

// forward declaration
class DateTime;

class ITimeKeeper
{
public:
    virtual ~ITimeKeeper() = default;

    enum class DoorState
    {
        OPEN,
        CLOSED
    };

    virtual DateTime &getCurrentTime() = 0;
    virtual DateTime &getTodaysSunrise() = 0;
    virtual DateTime &getTodaysSunset() = 0;
    virtual void setTime(const DateTime &newTime) = 0;
    virtual void setDaylightSaving(bool daylightSaving) = 0;
    virtual bool getDaylightSaving() const = 0;
    virtual void setPositionAndTimezone(float latitude, float longitude, float timezone) = 0;
};