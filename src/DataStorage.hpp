#pragma once

#include "IDataStorage.hpp"

class DataStorage : public virtual IDataStorage
{
public:
    explicit DataStorage();
    virtual ~DataStorage() = default;

    // IDataStorage
    void doFactoryReset() override;
    bool getDayLightSavingSetting() const override;
    void setDayLightSavingSetting(bool daylightsaving) override;
    void setPosition(float latitude, float longitude, float timezone) override;
    float getPositionLatitude() const override;
    float getPositionLongitude() const override;
    float getTimeZone() const override;

private:
    // memory mapping
    const int _formatInfo = 0;
    const int _daylightSaving = 1;
    const int _latitude = _daylightSaving + 1;
    const int _longitude = _latitude + sizeof(float);
    const int _timeZone = _longitude + sizeof(float);
};