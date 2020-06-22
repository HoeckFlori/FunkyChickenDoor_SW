#pragma once

#include "IOperationModeManager.hpp"
#include "IDataStorage.hpp"

class OperationModeManager : public virtual IOperationModeManager
{
public:
    OperationModeManager(IDataStorage *dataStorageAccess);
    virtual ~OperationModeManager() = default;

    // IOperationModeManager
    IOperationModeManager::OpMode getMode() const override;
    void changeMode(OpMode newMode) override;
    String getOpModeHumanReadable() const override;

private:
    IDataStorage *m_dataStorage;
    OpMode m_mode;
};