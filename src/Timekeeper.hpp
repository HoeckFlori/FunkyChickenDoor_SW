#pragma once

#include "Dusk2Dawn.h"
#include "IDataStorage.hpp"
#include "IOperationModeManager.hpp"
#include "ITimeKeeper.hpp"
#include "RTClib.h"

class Timekeeper : public virtual ITimeKeeper
{
  public:
    explicit Timekeeper(IDataStorage *dataStorage, IOperationModeManager *operationModeManager);

    // ITimeKeeper
    DateTime &getCurrentTime() override;
    DateTime &getTodaysSunrise() override;
    DateTime &getTodaysSunset() override;
    void setTime(const DateTime &newTime) override;
    void setDaylightSaving(bool daylightSaving) override;
    bool getDaylightSaving() const override;
    void setPositionAndTimezone(float latitude, float longitude, float timezone) override;

    void setDoNotOpenBefore(int hour, int minute) override;
    void disableDoNotOpenBefore() override;
    void setClosingDelay(uint16_t mm) override;
    void disableClosingDelay() override;
    DateTime &getTodayOpeningTime() override;
    DateTime &getTodayClosingTime() override;
    bool getAutomaticDoorState() override;

    void setArtificialMorningLight(int hour, int minute) override;
    void disableArtificialMorningLight() override;
    bool getArtificialLightState() override;

    void cycle() override;
    void registerEventListener(ITimeKeeperListener *listener) override;

  private:
    RTC_DS3231 m_myClock = RTC_DS3231();
    Dusk2Dawn m_dusk2Dawn = Dusk2Dawn(47.8144, 12.6352, +1); // todo(FHk) remove this, when the DataStorage is available and initialize it in the ctor

    IDataStorage *m_dataStorage;
    IOperationModeManager *m_operationModeManager;

    DateTime m_lastQueriedTime;
    DateTime m_todaysSunrise;
    DateTime m_todaysSunset;
    DateTime m_todayOpeningTime;
    DateTime m_todayClosingTime;
    IDataStorage::doNotOpenBeforeOption m_doNotOpenBeforeOption;
    IDataStorage::closingDelayOption m_closingDelayOption;
    IDataStorage::artificialMorningLightOption m_artificialMorningLightOption;
    bool m_daylightSaving;

    struct todaysEventRegister
    {
        todaysEventRegister()
            : firedDoorOpening(false)
            , firedDoorClosing(false)
            , firedArtificialLightOn(false)
            , firedArtificialLightOff(false)
        {
        }
        bool firedDoorOpening;
        bool firedDoorClosing;
        bool firedArtificialLightOn;
        bool firedArtificialLightOff;
    } m_eventHistory;

    static const int c_listenerArraySize = 10;
    ITimeKeeperListener *m_listenerPtr[c_listenerArraySize]; // The max amount of possible listener is defined here! We do not have a std:vector. What
                                                             // a pitty, we have to do it old school

    /**
     * @brief Adds a offset in minutes to a given date
     *
     * @param date The input to manipulate.
     * @param minutes the Minutes to add
     * @param startOnMidnight Resets the hours, minutes, seconds of the handed TimeDate object (default true)
     */
    void addMinutesToDate(DateTime &date, int32_t minutes, bool startOnMidnight = true);

    /**
     * @brief Inform all registrated listener about a event
     *
     * @param eventToSignalize The event of interest
     */
    void fireAllListener(ITimeKeeperListener::Event eventToSignalize);
};