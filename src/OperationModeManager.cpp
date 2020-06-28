#include "OperationModeManager.hpp"

OperationModeManager::OperationModeManager(IDataStorage *dataStorageAccess)
    : m_dataStorage(dataStorageAccess)
{
    // Restore last known OperationMode
    m_mode = static_cast<OpMode>(m_dataStorage->getOperationMode());

    // set a defined mode
    if (m_mode == OpMode::UNDEFINED)
    {
        changeMode(OpMode::MANUAL);
    }
}

IOperationModeManager::OpMode OperationModeManager::getMode() const
{
    return m_mode;
}

void OperationModeManager::changeMode(OpMode newMode)
{
    m_mode = newMode;
    m_dataStorage->setOperationMode(static_cast<int>(m_mode));
}

String OperationModeManager::getOpModeHumanReadable() const
{
    switch (m_mode)
    {
    case OpMode::UNDEFINED:
        return F("undefined");
        break;
    case OpMode::AUTOMATIC:
        return F("AutomaticMode");
        break;
    case OpMode::MANUAL:
        return F("ManualMode");
        break;
    default:
        return F("__error__"); // this should never happen
    }
}