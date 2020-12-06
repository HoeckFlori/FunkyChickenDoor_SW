#include <Arduino.h>
#include "MainControl.hpp"
#include "Timekeeper.hpp"
#include "ConsoleAgent.hpp"
#include "DataStorage.hpp"
#include "DoorSteering.hpp"
#include "OperationModeManager.hpp"
#include "EnergySavingMaster.hpp"
#include "views/ViewController.hpp"

MainControl::MainControl()
{
    Serial.begin(115200, SERIAL_8N1);

    // init participants
    m_energySavingMaster = new EnergySavingMaster(30 /*sec to Energysaving*/);
    m_dataStorage = new DataStorage();
    m_door = new DoorSteering(6 /* motor UP pin */, 7 /* motor DOWN pin */,
                              26 /* door UP pin */, 27 /*  door DOWN pin */);
    m_operationMode = new OperationModeManager(m_dataStorage, m_door);
    m_timeKeeper = new Timekeeper(m_dataStorage);
    m_consoleAgent = new ConsoleAgent(m_timeKeeper, m_dataStorage, m_door, m_operationMode);
    m_viewController = new ViewController(m_operationMode, m_timeKeeper, m_door, m_energySavingMaster);
}

void MainControl::cycle()
{
    // kick all cycles of the components
    m_consoleAgent->cycle();
    m_viewController->cycle();
    m_door->cycle();
    m_energySavingMaster->cycle();
    m_operationMode->cycle();
    m_timeKeeper->cycle();
}