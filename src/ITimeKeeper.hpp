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

    virtual DateTime getCurrentTime() = 0;
    virtual void setTime(const DateTime &newTime) = 0;
};