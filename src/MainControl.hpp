#pragma once

#include "IConsoleAgent.hpp"
#include "IGui.hpp"
#include "ITimeKeeper.hpp"
// #include "IDoorSteering.hpp"
// #include "ISleepingGuard.hpp"

class MainControl
{
public:
    MainControl();

    void init();
    void cycle();

private:
    IConsoleAgent *m_consoleAgent;
    // IDoorSteering *m_door;
    IGui *m_gui;
    // GuiSt7735 m_st7735;
    // ISleepingGuard *m_sleepingGuard;
    ITimeKeeper *m_timeKeeper;

    int m_counter;
};