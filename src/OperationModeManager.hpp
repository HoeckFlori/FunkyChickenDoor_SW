#pragma once

#include "IOperationModeManager.hpp"
#include "IDataStorage.hpp"
#include "IDoorSteering.hpp"

class OperationModeManager : public virtual IOperationModeManager
{
public:
    OperationModeManager(IDataStorage *dataStorageAccess, IDoorSteering *doorSteering);
    virtual ~OperationModeManager() = default;

    // IOperationModeManager
    void cycle() override;
    IOperationModeManager::OpMode getMode() const override;
    void changeMode(OpMode newMode) override;
    String getOpModeHumanReadable() const override;

private:
    IDataStorage *m_dataStorage;
    IDoorSteering *m_doorSteering;
    OpMode m_mode;
};