#pragma once

class IDataStorage
{
public:
    virtual ~IDataStorage() = default;

    virtual bool getDayLightSavingSetting() const = 0;
    virtual void setDayLightSavingSetting(bool daylightsaving) = 0;

    virtual void setPosition(float latitude, float longitude, float timezone) = 0;
    virtual float getPositionLatitude() const = 0;
    virtual float getPositionLongitude() const = 0;
    virtual float getTimeZone() const = 0;

    virtual void setOperationMode(int opMode) = 0;
    virtual int getOperationMode() const = 0;

    /*
    Settings we will need to persist
    [X] Daylight saving option, yes/no
    [X] Position
    [X] Operation mode
    [ ] Opening delay sunrise, +/- minutes
    [ ] 'Do not open before' option, yes/no
    [ ] 'Do not open before' time, Time
    [ ] Closing delay sunset,  +- minutes
    [ ] 'Open close timeout', seconds (maybe)
    */

    /*
   proposals for the CLI:
    
    setDoNotOpenBefore(06:00)
    disableDoNotOpenBefore()


    setClosingDelay(int minutes)
    setOpeningDelay(int minutes)

   */
};