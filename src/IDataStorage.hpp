#pragma once

class IDataStorage
{
public:
    virtual ~IDataStorage() = default;

    virtual bool getDayLightSavingSetting() = 0;
    virtual void setDayLightSavingSetting(bool daylightsaving) = 0;

    /*
    Settings we will need to persist
    [ ] Daylight saving option, yes/no
    [ ] Opening delay sunrise, +/- minutes
    [ ] 'Do not open before' option, yes/no
    [ ] 'Do not open before' time, Time
    [ ] Closing delay sunset,  +- minutes
    [ ] 'Open close timeout', seconds
    */

    /*
   proposals for the CLI:
    
    setDoNotOpenBefore(06:00)
    disableDoNotOpenBefore()

    // das Daylightsaving muss noch irgendwie in die cli rein rein, die Uhrzeit selbst braucht es nicht und speichert es auch nicht


    setClosingDelay(int minutes)
    setOpeningDelay(int minutes)

   */
};