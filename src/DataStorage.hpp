#pragma once

#include "IDataStorage.hpp"

class DataStorage : public virtual IDataStorage
{
public:
    explicit DataStorage();
    virtual ~DataStorage() = default;

    // IDataStorage
    bool getDayLightSavingSetting() const override;
    void setDayLightSavingSetting(bool daylightsaving) override;
    void setPosition(float latitude, float longitude, float timezone) override;
    float getPositionLatitude() const override;
    float getPositionLongitude() const override;
    float getTimeZone() const override;
    void setOperationMode(int opMode) override;
    int getOperationMode() const override;

    void setDoNotOpenBeforeOption(const IDataStorage::doNotOpenBeforeOption &setting) override;
    IDataStorage::doNotOpenBeforeOption getDoNotOpenBeforeOption() override;

    // void setDoNotOpenBeforeOption(bool);
    // bool getDoNotOpenBeforeOption();
    // void setDoNotOpenBeforeHour(int hour);
    // void setDoNotOpenBeforeMinute(int minute);
    // int  getDoNotOpenBeforeHour();
    // int  getDoNotOpenBeforeMinute();

private:
    // memory mapping
    const int _formatInfo = 0;
    const int _daylightSaving = 1;
    const int _latitude = _daylightSaving + 1;
    const int _longitude = _latitude + sizeof(float);
    const int _timeZone = _longitude + sizeof(float);
    const int _operationMode = _timeZone + sizeof(float);
    const int _doNotOpenBeforeOption = _operationMode + sizeof(int);

    // const int _doNotOpenBeforeOption = _operationMode + sizeof(int);
    // const int _doNotOpenBeforeHour = _doNotOpenBeforeOption + sizeof(int);
    // const int _doNotOpenBeforeMinute = _doNotOpenBeforeHour + sizeof(int);
};