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

    // --- 'static' stuff

    /**
     * @brief Get the current system time
     * 
     * @return A reference to the current system time
     */
    virtual DateTime &getCurrentTime() = 0;

    /**
     * @brief Get the todays sunrise time (with date)
     * 
     * @return A reference to todays sunrise
     */
    virtual DateTime &getTodaysSunrise() = 0;
    
    /**
     * @brief Get the todays sunset time (with date)
     * 
     * @return A reference to todays sunset
     */
    virtual DateTime &getTodaysSunset() = 0;

    /**
     * @brief Set a new system time/date for the RTC
     * 
     * @param newTime The new time/date
     */
    virtual void setTime(const DateTime &newTime) = 0;

    /**
     * @brief Set the 'daylight saving option' (German: Sommerzeit)
     * 
     * @param daylightSaving True if 'daylight saving option'
     */
    virtual void setDaylightSaving(bool daylightSaving) = 0;

    /**
     * @brief Query the current set 'daylight saving option' (German: Sommerzeit)
     * 
     * @return true   'daylight saving option' activ
     * @return false  'daylight saving option' NOT activ
     */
    virtual bool getDaylightSaving() const = 0;

    /**
     * @brief Set the position of the chickenhouse and the correct timezone.
     *        eg. 48.12999 (latitude) 11.12999 (longitude) +1 (timezone) -> You are at the Oktoberfest, wascheins Hendlbraderei
     * 
     * @param latitude 
     * @param longitude 
     * @param timezone 
     */
    virtual void setPositionAndTimezone(float latitude, float longitude, float timezone) = 0;

    /**
     * @brief Set the 'do not open before option'. This means it will not open before the time set here.
     *        This is useful if your rooster should not wake the neighbourhood before a certain time. 
     *        This could preserve neighbourhood peace. The time setting here also activates the functioanlity 
     *        itself.
     * 
     * @param hour 
     * @param minute 
     */
    virtual void setDoNotOpenBefore(int hour, int minute) = 0;

    /**
     * @brief Turn off the 'do not open before option'. This means the door opens again with the regular sunrise. 
     * 
     */
    virtual void disableDoNotOpenBefore() = 0;

    /**
     * @brief Activate a 'closing delay'. Means closing at sunrise + the here defined time in minutes.
     * 
     * @param mm Time in minutes for the closing delay.
     */
    virtual void setClosingDelay(uint16_t mm) = 0;

    /**
     * @brief Turn of the 'closing delay' option
     * 
     */
    virtual void disableClosingDelay() = 0;

    /**
     * @brief Get the todays door opening time/date. The time can be influenced by the 'do not open before option'.
     * 
     * @return DateTime& 
     */
    virtual DateTime &getTodayOpeningTime() = 0;

    /**
     * @brief Get the today door closing time/date. The time can be influended by the 'closing delay' option
     * 
     * @return DateTime& 
     */
    virtual DateTime &getTodayClosingTime() = 0;

    /**
     * @brief Get the normal 'Door State' according the automatic mode
     * 
     * @return true  Door should be 'open'
     * @return false Door should be 'closed'
     */
    virtual bool getAutomaticDoorState() = 0;

    /**
     * @brief Activate the 'artificial morning light option' at a certain time. A possibility to wake up the chickens 
     *        to work earlier in winter. The light is switched off at sunrise.
     * 
     * @param hour
     * @param minute 
     */
    virtual void setArtificialMorningLight(int hour, int minute) = 0;

    /**
     * @brief Turn off the 'artificial morning light option'
     * 
     */
    virtual void disableArtificialMorningLight() = 0;

    /**
     * @brief Get the normal 'Artificial Light' State in automatic mode
     * 
     * @return true Light is 'on'
     * @return false Light is 'off'
     */
    virtual bool getArtificialLightState() = 0;

    
    // --- 'dynamic' stuff

    /**
     * @brief The cycle to keep it running
     * 
     */
    virtual void cycle() = 0;

    /**
     * @brief Register a listener for TimeKeeper events. The Listener class has to derive from ITimeKeeperListener
     * 
     * @param listener 
     */
    virtual void registerEventListener(ITimeKeeperListener *listener) = 0;
};