#pragma once
#include "IConsoleAgent.hpp"
#include "IDataStorage.hpp"
#include "IDoorSteering.hpp"
#include "ILightSteering.hpp"
#include "IOperationModeManager.hpp"
#include "ITimeKeeper.hpp"
#include <CLI.h> // https://github.com/MajenkoLibraries/CLI

/**
 * @brief The ConsoleAgent is the class for the command line interface handling, therefore another form of UI.
 *        Unfortunately, the class now has godlike supreme power, as it can reach very deeply into the
 *        system. (headbang) every time it happens again...
 */
class ConsoleAgent : public virtual IConsoleAgent
{
  public:
    explicit ConsoleAgent(ITimeKeeper *timeKeeper, IDataStorage *dataStorage, IDoorSteering *doorSteering,
                          IOperationModeManager *operationModeManager, ILightSteering *lightSteering);
    void cycle() override;

  private:
    static ConsoleAgent *m_mySelf;

    void printHelpScreen();

    // command handlers (! They have to be static. To access the class internal method and attributes use the m_myself pointer!)
    static int connectFunction(CLIClient *dev, int argc, char **argv);
    static int help(CLIClient *dev, int argc, char **argv);
    static int showMemory(CLIClient *dev, int argc, char **argv);
    static int reset(CLIClient *dev, int argc, char **argv);
    static int factoryReset(CLIClient *dev, int argc, char **argv);
    static int changeOpMode(CLIClient *dev, int argc, char **argv);
    static int getDateTime(CLIClient *dev, int argc, char **argv);
    static int setTime(CLIClient *dev, int argc, char **argv);
    static int setDaylightSaving(CLIClient *dev, int argc, char **argv);
    static int enableNotOpenBefore(CLIClient *dev, int argc, char **argv);
    static int disableNotOpenBefore(CLIClient *dev, int argc, char **argv);
    static int enableClosingDelay(CLIClient *dev, int argc, char **argv);
    static int disableClosingDelay(CLIClient *dev, int argc, char **argv);
    static int enableArtificalMorningLight(CLIClient *dev, int argc, char **argv);
    static int disableArtificalMorningLight(CLIClient *dev, int argc, char **argv);
    static int setPosition(CLIClient *dev, int argc, char **argv);
    static int openDoor(CLIClient *dev, int argc, char **argv);
    static int closeDoor(CLIClient *dev, int argc, char **argv);
    static int setDoorTimeout(CLIClient *dev, int argc, char **argv);
    static int turnLightOn(CLIClient *dev, int argc, char **argv);
    static int turnLightOff(CLIClient *dev, int argc, char **argv);
    static int showInfo(CLIClient *dev, int argc, char **argv);

    // connections to relevant softwareparts
    ITimeKeeper *m_timeKeeper;
    IDataStorage *m_dataStorage;
    IDoorSteering *m_doorSteering;
    IOperationModeManager *m_operationMode;
    ILightSteering *m_lightSteering;
};