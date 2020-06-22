#include <Arduino.h>
#include "MainControl.hpp"
#include "Timekeeper.hpp"
#include "ConsoleAgent.hpp"
#include "DataStorage.hpp"
#include "views/ViewController.hpp"
#include "DoorSteering.hpp"
#include "OperationModeManager.hpp"

MainControl::MainControl()
{
    // !!! Do not place initialization of anything in here. It doesn't work, I don't know why. FHk
    Serial.begin(115200, SERIAL_8N1);

    // init participants
    m_dataStorage = new DataStorage();
    m_operationMode = new OperationModeManager(m_dataStorage);
    m_door = new DoorSteering();
    m_timeKeeper = new Timekeeper(m_dataStorage);
    m_consoleAgent = new ConsoleAgent(m_timeKeeper, m_dataStorage, m_door, m_operationMode);
    m_viewController = new ViewController(m_timeKeeper, m_door);
}

void MainControl::cycle()
{
    // kick all cycles of the components
    m_consoleAgent->cycle();
    m_viewController->cycle();
    m_door->cycle();
}