#include "MainControl.hpp"
#include "ConsoleAgent.hpp"
#include "DataStorage.hpp"
#include "DoorSteering.hpp"
#include "EnergySavingMaster.hpp"
#include "ITimeKeeperListener.hpp"
#include "LightSteering.hpp"
#include "OperationModeManager.hpp"
#include "Timekeeper.hpp"
#include "views/ViewController.hpp"
#include <Arduino.h>

MainControl::MainControl()
{
    Serial.begin(115200, SERIAL_8N1);

    // init participants
    m_energySavingMaster = new EnergySavingMaster(30 /*sec to Energysaving*/);
    m_dataStorage = new DataStorage();
    DoorSteering *plainDoor =
        new DoorSteering(m_dataStorage, 6 /* motor UP pin */, 7 /* motor DOWN pin */, 26 /* door UP pin */, 27 /*  door DOWN pin */);
    m_door = plainDoor;
    LightSteering *plainLightSteering = new LightSteering(5 /* 'IndoorLighting' pin*/);
    m_lighting = plainLightSteering;
    m_operationMode = new OperationModeManager(m_dataStorage, m_door);
    m_timeKeeper = new Timekeeper(m_dataStorage, m_operationMode);
    m_timeKeeper->registerEventListener(plainDoor);
    m_timeKeeper->registerEventListener(plainLightSteering);
    m_consoleAgent = new ConsoleAgent(m_timeKeeper, m_dataStorage, m_door, m_operationMode, m_lighting);
    m_viewController = new ViewController(m_operationMode, m_timeKeeper, m_door, m_energySavingMaster, m_lighting);
}

void MainControl::cycle()
{
    // kick all cycles of the components
    m_consoleAgent->cycle();
    m_viewController->cycle();
    m_door->cycle();
    m_energySavingMaster->cycle();
    // m_operationMode->cycle();
    m_timeKeeper->cycle();
}