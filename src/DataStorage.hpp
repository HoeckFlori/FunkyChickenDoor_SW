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

    void setClosingDelayOption(const IDataStorage::closingDelayOption &setting) override;
    IDataStorage::closingDelayOption getClosingDelayOption() override;

    void setArtificialMorningLightOption(const IDataStorage::artificialMorningLightOption &setting) override;
    IDataStorage::artificialMorningLightOption getArtificialMorningLightOption() override;

  private:
    // memory mapping
    const int _formatInfo = 0;
    const int _daylightSaving = 1;
    const int _latitude = _daylightSaving + 1;
    const int _longitude = _latitude + sizeof(float);
    const int _timeZone = _longitude + sizeof(float);
    const int _operationMode = _timeZone + sizeof(float);
    const int _doNotOpenBeforeOption = _operationMode + sizeof(int);
    const int _closingDelayOption = _doNotOpenBeforeOption + sizeof(IDataStorage::doNotOpenBeforeOption);
    const int _artificialMorningLightOption = _closingDelayOption + sizeof(IDataStorage::closingDelayOption);
};