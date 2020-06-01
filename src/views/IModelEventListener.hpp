#pragma once

class IModelEventListener
{
public:
    virtual ~IModelEventListener() = default;

    enum class Event
    {
        TIME_UPDATE,
        SUNRISE_SUNSET_UPDATE,
        MODE_CHANGED,
        DOOR_STATE_CHANGED,
        NEW_ERROR_AVAILABLE
    };
};