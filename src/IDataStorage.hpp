#pragma once
#include <stdint.h>

class IDataStorage
{
  public:
    virtual ~IDataStorage() = default;

    struct positionOption
    {
        positionOption(float latitude = 0, float longitude = 0, float timeZone = 0)
            : _positionLatitude(latitude)
            , _positionLongitude(longitude)
            , _timeZone(timeZone)
        {
        }
        float _positionLatitude;
        float _positionLongitude;
        float _timeZone;
    };

    struct doNotOpenBeforeOption
    {
        doNotOpenBeforeOption(bool enabled = false, uint8_t hour = 0, uint8_t minute = 0)
            : _optionEnabled(enabled)
            , _hour(hour)
            , _minute(minute)
        {
        }
        bool _optionEnabled;
        uint8_t _hour;
        uint8_t _minute;
    };

    struct closingDelayOption
    {
        closingDelayOption(bool enabled = false, uint16_t minutes = 0)
            : _optionEnabled(enabled)
            , _minutes(minutes)
        {
        }
        bool _optionEnabled;
        uint16_t _minutes;
    };

    struct artificialMorningLightOption
    {
        artificialMorningLightOption(bool enabled = false, uint8_t hour = 0, uint8_t minute = 0)
            : _optionEnabled(enabled)
            , _hour(hour)
            , _minute(minute)
        {
        }
        bool _optionEnabled;
        uint8_t _hour;
        uint8_t _minute;
    };

    /**
     * @brief Format/reset complete memory (each cell).
     *        A system reset afterwards is recommended! Otherwise, undefined behaviour may occur.
     *
     */
    virtual void formatMemory() = 0;

    virtual void setDayLightSavingSetting(bool daylightsaving) = 0;
    virtual bool getDayLightSavingSetting() const = 0;

    virtual void setPosition(const IDataStorage::positionOption &position) = 0;
    virtual IDataStorage::positionOption getPosition() const = 0;

    virtual void setOperationMode(int opMode) = 0;
    virtual int getOperationMode() const = 0;

    virtual void setDoNotOpenBeforeOption(const IDataStorage::doNotOpenBeforeOption &setting) = 0;
    virtual IDataStorage::doNotOpenBeforeOption getDoNotOpenBeforeOption() = 0;

    virtual void setClosingDelayOption(const IDataStorage::closingDelayOption &setting) = 0;
    virtual IDataStorage::closingDelayOption getClosingDelayOption() = 0;

    virtual void setArtificialMorningLightOption(const IDataStorage::artificialMorningLightOption &setting) = 0;
    virtual IDataStorage::artificialMorningLightOption getArtificialMorningLightOption() = 0;

    virtual void setDoorMovingTimeout(uint16_t timeoutSec) = 0;
    virtual uint16_t getDoorMovingTimeout() = 0;

    /*
    Settings we will need to persist
    [X] Daylight saving option, yes/no
    [X] Position
    [X] Operation mode
    [ ] Opening delay sunrise, +/- minutes
    [x] 'Do not open before' option, yes/no
    [x] 'Do not open before' time, Time
    [X] Closing delay sunset,  +- minutes
    [X] 'Open close timeout', seconds (maybe)
    [X]  artificialMorningLightOption
    */
};