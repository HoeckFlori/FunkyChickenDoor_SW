#pragma once

#include "IConsoleAgent.hpp"
#include "IDataStorage.hpp"
#include "IDoorSteering.hpp"
#include "ITimeKeeper.hpp"
#include "views/IViewController.hpp"
// #include "ISleepingGuard.hpp"
#include "IEnergySavingMaster.hpp"
#include "ILightSteering.hpp"
#include "IOperationModeManager.hpp"

class MainControl
{
  public:
    explicit MainControl();
    ~MainControl() = default;

    MainControl(const MainControl &obj);              // copy constructor
    MainControl &operator=(const MainControl &other); // assigment constructor

    void cycle();

  private:
    IConsoleAgent *m_consoleAgent;
    IDoorSteering *m_door;
    // ISleepingGuard *m_sleepingGuard;
    ILightSteering *m_lighting;
    ITimeKeeper *m_timeKeeper;
    IDataStorage *m_dataStorage;
    IViewController *m_viewController;
    IOperationModeManager *m_operationMode;
    IEnergySavingMaster *m_energySavingMaster;
};