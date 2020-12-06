#pragma once
#include <stdint.h>
#include "ITimeKeeperListener.hpp"

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

    // 'static' stuff
    virtual DateTime &getCurrentTime() = 0;
    virtual DateTime &getTodaysSunrise() = 0;
    virtual DateTime &getTodaysSunset() = 0;
    virtual void setTime(const DateTime &newTime) = 0;
    virtual void setDaylightSaving(bool daylightSaving) = 0;
    virtual bool getDaylightSaving() const = 0;
    virtual void setPositionAndTimezone(float latitude, float longitude, float timezone) = 0;


    virtual void setDoNotOpenBefore(int hour, int minute) = 0;
    virtual void disableDoNotOpenBefore() = 0;
    virtual void setClosingDelay(uint16_t mm) = 0;
    virtual void disableClosingDelay() = 0;
    virtual DateTime &getTodayOpeningTime() = 0;
    virtual DateTime &getTodayClosingTime() = 0;
    /**
     * @brief Get the normal 'Door State' in the automatic mode
     * 
     * @return true Door should be 'open'
     * @return false Door should be 'closed'
     */
    virtual bool getAutomaticDoorState() = 0;


    virtual void setArtificialMorningLight(int hour, int minute) = 0;
    virtual void disableArtificialMorningLight() = 0;
    /**
     * @brief Get the normal 'Artificial Light' State in automatic mode
     * 
     * @return true Light is 'on'
     * @return false Light is 'off'
     */
    virtual bool getArtificialLightState() = 0;


    
    // 'dynamic' stuff
    virtual void cycle() = 0;
    virtual void registerEventListener(ITimeKeeperListener *listener) = 0;
};