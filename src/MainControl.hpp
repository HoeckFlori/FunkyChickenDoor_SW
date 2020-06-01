#pragma once

#include "IConsoleAgent.hpp"
#include "IGui.hpp"
#include "ITimeKeeper.hpp"
#include "IDataStorage.hpp"
#include "views/IViewController.hpp"
// #include "IDoorSteering.hpp"
// #include "ISleepingGuard.hpp"

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
    // IDoorSteering *m_door;
    // ISleepingGuard *m_sleepingGuard;
    ITimeKeeper *m_timeKeeper;
    IDataStorage *m_dataStorage;

    IGui *m_gui;
    IViewController *m_viewController;

    int m_counter;
};