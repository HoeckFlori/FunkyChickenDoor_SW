#pragma once

#include "IDataStorage.hpp"

class DataStorage : public virtual IDataStorage
{
  public:
    explicit DataStorage();
    virtual ~DataStorage() = default;

    // IDataStorage
    void formatMemory() override;

    void setDayLightSavingSetting(bool daylightsaving) override;
    bool getDayLightSavingSetting() const override;

    void setPosition(const IDataStorage::positionOption &position) override;
    IDataStorage::positionOption getPosition() const override;

    void setOperationMode(int opMode) override;
    int getOperationMode() const override;

    void setDoNotOpenBeforeOption(const IDataStorage::doNotOpenBeforeOption &setting) override;
    IDataStorage::doNotOpenBeforeOption getDoNotOpenBeforeOption() override;

    void setClosingDelayOption(const IDataStorage::closingDelayOption &setting) override;
    IDataStorage::closingDelayOption getClosingDelayOption() override;

    void setArtificialMorningLightOption(const IDataStorage::artificialMorningLightOption &setting) override;
    IDataStorage::artificialMorningLightOption getArtificialMorningLightOption() override;

    void setDoorMovingTimeout(uint16_t timeoutSec) override;
    uint16_t getDoorMovingTimeout() override;

  private:
    // memory mapping
    const int _formatInfo = 0;
    const int _daylightSaving = sizeof(int);
    const int _position = _daylightSaving + sizeof(int);
    const int _operationMode = _position + sizeof(IDataStorage::positionOption);
    const int _doNotOpenBeforeOption = _operationMode + sizeof(int);
    const int _closingDelayOption = _doNotOpenBeforeOption + sizeof(IDataStorage::doNotOpenBeforeOption);
    const int _artificialMorningLightOption = _closingDelayOption + sizeof(IDataStorage::closingDelayOption);
    const int _doorMovingTimeout = _artificialMorningLightOption + sizeof(IDataStorage::artificialMorningLightOption);
};