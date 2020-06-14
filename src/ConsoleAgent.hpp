#pragma once
#include <CLI.h> // https://github.com/MajenkoLibraries/CLI
#include "IConsoleAgent.hpp"
#include "ITimeKeeper.hpp"
#include "IDataStorage.hpp"
#include "IDoorSteering.hpp"

class ConsoleAgent : public virtual IConsoleAgent
{
public:
    explicit ConsoleAgent(ITimeKeeper *timeKeeper, IDataStorage *dataStorage, IDoorSteering *doorSteering);
    void cycle() override;

private:
    static ConsoleAgent *m_mySelf;

    void printHelpScreen();

    // command handlers (! They have to be static. To access the class internal method and attributes use the m_myself pointer!)
    static int connectFunction(CLIClient *dev, int argc, char **argv);
    static int help(CLIClient *dev, int argc, char **argv);
    static int showMemory(CLIClient *dev, int argc, char **argv);
    static int getDateTime(CLIClient *dev, int argc, char **argv);
    static int setTime(CLIClient *dev, int argc, char **argv);
    static int setDaylightSaving(CLIClient *dev, int argc, char **argv);
    static int setPosition(CLIClient *dev, int argc, char **argv);
    static int initDoor(CLIClient *dev, int argc, char **argv);
    static int openDoor(CLIClient *dev, int argc, char **argv);
    static int closeDoor(CLIClient *dev, int argc, char **argv);
    static int showInfo(CLIClient *dev, int argc, char **argv);

    // connections to relevant softwareparts
    ITimeKeeper *m_timeKeeper;
    IDataStorage *m_dataStorage;
    IDoorSteering *m_doorSteering;
};