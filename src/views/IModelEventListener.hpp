#pragma once

class IModelEventListener
{
public:
    virtual ~IModelEventListener() = default;

    enum class Event
    {
        TIME_UPDATE,
        DATE_UPDATE,
        SUNRISE_SUNSET_UPDATE,
        MODE_CHANGED,
        DOOR_STATE_CHANGED,
        NEW_ERROR_AVAILABLE,
        RELOAD_EVERYTHING
    };

    /**
     * @brief The 'callback' method, that can be registred to the model.
     * 
     * @param event The information about events from the Model.
     */
    virtual void modelListener(IModelEventListener::Event event) = 0;
};