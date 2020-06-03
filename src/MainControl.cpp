#include <Arduino.h>
#include "MainControl.hpp"
#include "GuiSt7735.hpp"
#include "Timekeeper.hpp"
#include "ConsoleAgent.hpp"
#include "DataStorage.hpp"
#include "views/ViewController.hpp"

MainControl::MainControl()
    : m_counter(0)
{
    // !!! Do not place initialization of anything in here. It doesn't work, I don't know why. FHk
    Serial.begin(115200, SERIAL_8N1);

    // init participants
    m_dataStorage = new DataStorage();
    m_timeKeeper = new Timekeeper(m_dataStorage);
    m_consoleAgent = new ConsoleAgent(m_timeKeeper, m_dataStorage);
    m_viewController = new ViewController(m_timeKeeper);
}

void MainControl::cycle()
{
    // kick all cycles of the components
    m_consoleAgent->cycle();
    m_viewController->cycle();
}