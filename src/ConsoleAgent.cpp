#include "ConsoleAgent.hpp"
#include "FreeMemory.hpp"
#include "RTClib.h"
#include <Arduino.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>

// the ConsoleAgent gets handled in a similar form like a singleton to access the members from the static command methods
ConsoleAgent *ConsoleAgent::m_mySelf = 0;

ConsoleAgent::ConsoleAgent(ITimeKeeper *timeKeeper, IDataStorage *dataStorage, IDoorSteering *doorSteering,
                           IOperationModeManager *operationModeManager, ILightSteering *lightSteering)
    : m_timeKeeper(timeKeeper)
    , m_dataStorage(dataStorage)
    , m_doorSteering(doorSteering)
    , m_operationMode(operationModeManager)
    , m_lightSteering(lightSteering)
{
    m_mySelf = this;

    CLI.setDefaultPrompt("~");
    CLI.onConnect(connectFunction);
    CLI.addClient(Serial);

    // register commands
    // CLI.addCommand("help", (*function)(help(CLIClient * dev, int argc, char **argv)));
    CLI.addCommand("help", help);
    CLI.addCommand("memory", showMemory);
    CLI.addCommand("reset", reset);
    CLI.addCommand("factoryReset", factoryReset);
    CLI.addCommand("changeOpMode", changeOpMode);
    CLI.addCommand("getTime", getDateTime);
    CLI.addCommand("setTime", setTime);
    CLI.addCommand("setDaylightSaving", setDaylightSaving);
    CLI.addCommand("enableNotOpenBefore", enableNotOpenBefore);
    CLI.addCommand("disableNotOpenBefore", disableNotOpenBefore);
    CLI.addCommand("enableClosingDelay", enableClosingDelay);
    CLI.addCommand("disableClosingDelay", disableClosingDelay);
    CLI.addCommand("enableMorningLight", enableArtificalMorningLight);
    CLI.addCommand("disableMorningLight", disableArtificalMorningLight);
    CLI.addCommand("setPosition", setPosition);
    CLI.addCommand("openDoor", openDoor);
    CLI.addCommand("closeDoor", closeDoor);
    CLI.addCommand("setDoorTimeout", setDoorTimeout);
    CLI.addCommand("turnLightOn", turnLightOn);
    CLI.addCommand("turnLightOff", turnLightOff);
    CLI.addCommand("showInfo", showInfo);
}

void ConsoleAgent::cycle()
{
    CLI.process();
}

// CLI_COMMAND(connectFunction)
int ConsoleAgent::connectFunction(CLIClient *dev, int argc, char **argv)
{
    dev->println(F("\nHello to the Chicken door terminal"));
    dev->println(F("Type 'help' to list commands."));
    dev->println();
    return 0; // no error
}

int ConsoleAgent::help(CLIClient *dev, int argc, char **argv)
{
    dev->println(F(" Available commands for the Chicken Door Terminal:"));
    dev->println(F(" -> 'help'                 Show this help context"));
    dev->println(F(" -> 'memory'               Show available RAM in bytes"));
    dev->println(F(" -> 'reset'                Initiate a softreset"));
    dev->println(F(" -> 'factoryReset'         Do a factory reset. Attention, all settings get lost!"));
    dev->println(F(" -> 'changeOpMode          Change the door OperationMode"));
    dev->println(F(" -> 'getTime'              Show actual system time"));
    dev->println(F(" -> 'setTime'              Set new time"));
    dev->println(F(" -> 'setDaylightSaving'    Active the daylight option (summer time)"));
    dev->println(F(" -> 'enableNotOpenBefore'  Enable the 'do not open before option x:xx o'clock' option"));
    dev->println(F(" -> 'disableNotOpenBefore' Disable the 'do not open before ...' option"));
    dev->println(F(" -> 'enableClosingDelay'   Enable the 'closing delay in minutes after sunset' option"));
    dev->println(F(" -> 'disableClosingDelay'  Disable the 'closing delay in minutes after sunset' option"));
    dev->println(F(" -> 'enableMorningLight'   Enable the 'artifical morning light' option for the wintertime"));
    dev->println(F(" -> 'disableMorningLight'  Disable the 'artifical morning light' option"));
    dev->println(F(" -> 'setPosition'          Set geographical position of your chicken house"));
    dev->println(F(" -> 'openDoor'             Open door manually  (changes also the operation mode)"));
    dev->println(F(" -> 'closeDoor'            Close door manually (-\"-)"));
    dev->println(F(" -> 'setDoorTimeout'       Set the timeout for the door movement in seconds (-\"-)"));
    dev->println(F(" -> 'turnLightOn'          Switch on the (artificial/indoor) light manually"));
    dev->println(F(" -> 'turnLightOff'         Switch off ...      (-\"-)"));
    dev->println(F(" -> 'showInfo'             Show all relevant information (dynamic/static) of the system"));
    return 0; // no error
}

int ConsoleAgent::showMemory(CLIClient *dev, int argc, char **argv)
{
    GetMemoryInformation();
    GetFreeMemory(true /*withExploitation*/);
    return 0;
}

int ConsoleAgent::reset(CLIClient *dev, int argc, char **argv)
{
    dev->println(F("Reset gets done ..."));
    // fake watchdog failure to generate a reset
    wdt_disable();
    wdt_enable(WDTO_15MS);
    while (1)
    {
        // PNR
    }
    return 0;
}

int ConsoleAgent::factoryReset(CLIClient *dev, int argc, char **argv)
{
    if (argc < 2)
    {
        // The command alone is not valid. Show hint to prevent missuse.
        dev->println(F("-> Are you really sure to reset the device? Type 'factoryReset now' to be sure."));
        return 0;
    }

    String input(argv[1]);
    if (input.equals(F("now")))
    {
        dev->println(F("Memory gets erased ..."));
        m_mySelf->m_dataStorage->formatMemory();
        dev->println(F("... reset gets done ..."));
        // fake watchdog failure to generate a reset
        wdt_disable();
        wdt_enable(WDTO_15MS);
        while (1)
        {
            // PNR
        }
        return 0;
    }
    else
    {
        dev->println(F("Input command unknown!"));
        return -1;
    }
}

int ConsoleAgent::changeOpMode(CLIClient *dev, int argc, char **argv)
{
    if (argc == 1)
    {
        // argument is not valid, show error message and skip command
        dev->println(F("-> Usage: 'changeOpMode auto' (options are 'auto' or 'manual')"));
        return -1;
    }

    String input(argv[1]);
    if (input.equals(F("auto")))
    {
        dev->println(F("... set to 'AutomaticMode'"));
        m_mySelf->m_operationMode->changeMode(IOperationModeManager::OpMode::AUTOMATIC);
        return 0;
    }
    else if (input.equals(F("manual")))
    {
        dev->println(F("... set to 'ManualMode'"));
        m_mySelf->m_operationMode->changeMode(IOperationModeManager::OpMode::MANUAL);
        return 0;
    }
    else
    {
        // argument is not valid, show error message and skip command
        dev->print(F("-> Input error! '"));
        dev->print(input);
        dev->println("' not found.");
        return -1;
    }
}

int ConsoleAgent::getDateTime(CLIClient *dev, int argc, char **argv)
{
    dev->print(F("Current date/time: "));
    auto currentTime = m_mySelf->m_timeKeeper->getCurrentTime();
    String timeBuffer(F("DD.MM.YYYY hh:mm:ss"));
    currentTime.toString(timeBuffer.begin());
    dev->println(timeBuffer);
    return 0;
}

int ConsoleAgent::setTime(CLIClient *dev, int argc, char **argv)
{
    uint8_t hh(0); // Hours 0-23
    uint8_t mm(0); // Minutes 0-59
    uint8_t d(0);  // Day 1-31
    uint8_t m(0);  // Month 1-12
    uint16_t y;    // Year

    if (!((argc > 1) && (argc < 4)))
    {
        // arguments are not valid, show error message and skip command
        dev->println(F("-> Usage: 'setTime 28.04.2020 02:30'"));
        return -1;
    }
    else
    {
        // extract date
        {
            String date(argv[1]);
            d = date.toInt();
            int indexOfColon1 = date.indexOf(F("."));
            m = date.substring(indexOfColon1 + 1).toInt();
            int indexOfColon2 = date.lastIndexOf(F("."));
            y = date.substring(indexOfColon2 + 1).toInt();
        }
        // extract time
        {
            String time(argv[2]);
            hh = time.toInt();
            int indexOfColon = time.indexOf(F(":"));
            mm = time.substring(indexOfColon + 1).toInt();
        }
    }

    // Build date/time class and initialize RTC
    DateTime newTime(y, m, d, hh, mm, 0);
    String timeBuffer(F("DD.MM.YYYY hh:mm:ss"));
    newTime.toString(timeBuffer.begin());
    dev->print(F("new Time: "));
    dev->println(timeBuffer);
    m_mySelf->m_timeKeeper->setTime(newTime);

    return 0;
}

int ConsoleAgent::setDaylightSaving(CLIClient *dev, int argc, char **argv)
{
    if (argc == 1)
    {
        // argument is not valid, show error message and skip command
        dev->println(F("-> Usage: 'setDaylightSaving on' (or off)"));
        return -1;
    }
    String daylightSavingInput(argv[1]);
    if (daylightSavingInput.equals(F("on")))
    {
        dev->println(F("... set on"));
        m_mySelf->m_timeKeeper->setDaylightSaving(true);
        return 0;
    }
    else if (daylightSavingInput.equals(F("off")))
    {
        dev->println(F("... set off"));
        m_mySelf->m_timeKeeper->setDaylightSaving(false);
        return 0;
    }
    else
    {
        // argument is not valid, show error message and skip command
        dev->print(F("-> Input error! '"));
        dev->print(daylightSavingInput);
        dev->println("' not found.");
        return -1;
    }
}

int ConsoleAgent::enableNotOpenBefore(CLIClient *dev, int argc, char **argv)
{
    if ((argc == 1) || (argc > 2))
    {
        // argument is not valid, show error message and skip command
        dev->println(F("-> Usage: 'enableNotOpenBefore 6:00'"));
        return -1;
    }

    uint8_t hh(0);
    uint8_t mm(0);

    // extract time
    String time(argv[1]);
    hh = time.toInt();
    int indexOfColon = time.indexOf(F(":"));
    mm = time.substring(indexOfColon + 1).toInt();

    m_mySelf->m_timeKeeper->setDoNotOpenBefore(hh, mm);
    return 0;
}
int ConsoleAgent::disableNotOpenBefore(CLIClient *dev, int argc, char **argv)
{
    if (argc != 1)
    {
        // argument is not valid, show error message and skip command
        dev->println(F("-> error, too many arguments"));
        return -1;
    }
    m_mySelf->m_timeKeeper->disableDoNotOpenBefore();
    dev->println(F("-> 'NotOpenBefore' option turned off"));
    return 0;
}

int ConsoleAgent::enableClosingDelay(CLIClient *dev, int argc, char **argv)
{
    if ((argc == 1) || (argc > 2))
    {
        // argument is not valid, show error message and skip command
        dev->println(F("-> Usage: 'enableClosingDelay 20 (min)'"));
        return -1;
    }

    // extract time
    uint16_t mm(0);
    String time(argv[1]);
    mm = time.toInt();

    m_mySelf->m_timeKeeper->setClosingDelay(mm);

    dev->print(F(" -> ClosingDelayOption enabled and set to '"));
    dev->print(mm);
    dev->print(F(" minute(s)' after sunset"));

    return 0;
}

int ConsoleAgent::disableClosingDelay(CLIClient *dev, int argc, char **argv)
{
    if (argc != 1)
    {
        // argument is not valid, show error message and skip command
        dev->println(F("-> error, too many arguments"));
        return -1;
    }
    m_mySelf->m_timeKeeper->disableClosingDelay();
    dev->println(F("-> 'ClosingDelay' option turned off"));
    return 0;
}

int ConsoleAgent::enableArtificalMorningLight(CLIClient *dev, int argc, char **argv)
{
    if ((argc == 1) || (argc > 2))
    {
        // argument is not valid, show error message and skip command
        dev->println(F("-> Usage: 'enableMorningLight 6:20'"));
        return -1;
    }

    uint8_t hh(0);
    uint8_t mm(0);

    // extract time
    String time(argv[1]);
    hh = time.toInt();
    int indexOfColon = time.indexOf(F(":"));
    mm = time.substring(indexOfColon + 1).toInt();

    m_mySelf->m_timeKeeper->setArtificialMorningLight(hh, mm);

    dev->print(F("-> Light turns on at "));
    dev->print(hh);
    dev->print(":");
    dev->print(mm);
    dev->print(F(" o'clock, when the sun has not yet risen."));
    return 0;
}

int ConsoleAgent::disableArtificalMorningLight(CLIClient *dev, int argc, char **argv)
{
    m_mySelf->m_timeKeeper->disableArtificialMorningLight();
    dev->println(F("-> 'ArtificalMorningLight' option turned off"));
    return 0;
}

int ConsoleAgent::setPosition(CLIClient *dev, int argc, char **argv)
{
    float latitude;
    float longitude;
    float timezone;

    if (!((argc > 1) && (argc < 5)))
    {
        // arguments are not valid, show error message and skip command
        dev->println(F("-> Usage: 'setPosition 47.81440 12.63520 +1' (latitude longitude timezone)"));
        return -1;
    }
    else
    {
        // extract latitude
        {
            String lat(argv[1]);
            latitude = lat.toFloat();
        }
        // extract longitude
        {
            String longi(argv[2]);
            longitude = longi.toFloat();
        }
        // extract timezone
        {
            String timez(argv[3]);
            timezone = timez.toFloat();
        }

        dev->print(F("latitude:  "));
        dev->println(latitude, 5);
        dev->print(F("longitude: "));
        dev->println(longitude, 5);
        dev->print(F("timezone:  "));
        dev->println(timezone, 0);

        m_mySelf->m_timeKeeper->setPositionAndTimezone(latitude, longitude, timezone);
        return 0;
    }
}

int ConsoleAgent::openDoor(CLIClient *dev, int argc, char **argv)
{
    if (!(m_mySelf->m_doorSteering))
        return -1; // error

    m_mySelf->m_doorSteering->openDoor();
    return 0;
}

int ConsoleAgent::closeDoor(CLIClient *dev, int argc, char **argv)
{
    if (!(m_mySelf->m_doorSteering))
        return -1; // error

    m_mySelf->m_doorSteering->closeDoor();
    return 0;
}

int ConsoleAgent::setDoorTimeout(CLIClient *dev, int argc, char **argv)
{
    if (!(m_mySelf->m_doorSteering))
        return -1; // error

    if ((argc == 1) || (argc > 2))
    {
        // argument is not valid, show error message and skip command
        dev->println(F("-> Usage: 'setDoorTimeout 30 (sec)'"));
        return -1;
    }

    // extract time
    uint16_t seconds(0);
    String time(argv[1]);
    seconds = time.toInt();

    m_mySelf->m_doorSteering->setTimeoutForDoorMoving(seconds);
    dev->print(F("-> Set the timeout for the door moving action to "));
    dev->print(seconds);
    dev->println(F(" sec"));
    return 0;
}

int ConsoleAgent::turnLightOn(CLIClient *dev, int argc, char **argv)
{
    dev->println(F("-> Light ON"));
    m_mySelf->m_lightSteering->switchLightOn();
    return 0;
}

int ConsoleAgent::turnLightOff(CLIClient *dev, int argc, char **argv)
{
    dev->println(F("-> Light OFF"));
    m_mySelf->m_lightSteering->switchLightOff();
    return 0;
}

int ConsoleAgent::showInfo(CLIClient *dev, int argc, char **argv)
{
    // show OperationMode status
    dev->print(F("OperationMode:     '"));
    dev->print(m_mySelf->m_operationMode->getOpModeHumanReadable());
    dev->println(F("'"));

    // show current time
    getDateTime(dev, argc, argv);

    // show sunrise and sunset
    String timeBuffer(F("DD.MM.YYYY hh:mm"));
    dev->print(F("Sunrise:           "));
    m_mySelf->m_timeKeeper->getTodaysSunrise().toString(timeBuffer.begin());
    dev->println(timeBuffer);
    dev->print(F("Sunset:            "));
    timeBuffer = F("DD.MM.YYYY hh:mm");
    m_mySelf->m_timeKeeper->getTodaysSunset().toString(timeBuffer.begin());
    dev->println(timeBuffer);

    // show daylight saving option
    dev->print(F("Daylightsaving:    "));
    if (m_mySelf->m_timeKeeper->getDaylightSaving())
        dev->println(F("on (summertime)"));
    else
        dev->println(F("off (wintertime)"));

    if (m_mySelf->m_dataStorage)
    {
        // show position and timezone
        auto position = m_mySelf->m_dataStorage->getPosition();
        dev->print(F("Position:          "));
        dev->print(position._positionLatitude, 5);
        dev->print(F(", "));
        dev->println(position._positionLongitude, 5);
        dev->print(F("Timezone:          "));
        dev->println(position._timeZone, 0);

        // show doNotOpenBefore
        auto doNotOpenBefore = m_mySelf->m_dataStorage->getDoNotOpenBeforeOption();
        dev->print(F("DoNotOpenBeforeOption:  '"));
        dev->print(doNotOpenBefore._optionEnabled ? F("enabled'") : F("off'"));
        if (doNotOpenBefore._optionEnabled)
        {
            dev->print(F(" @ "));
            dev->print(doNotOpenBefore._hour);
            dev->print(F(":"));
            if (doNotOpenBefore._minute < 10)
                dev->print(F("0"));
            dev->print(doNotOpenBefore._minute);
            dev->print(F(" o'clock"));
        }
        dev->println(F(""));

        // show closingDelay
        auto closingDelay = m_mySelf->m_dataStorage->getClosingDelayOption();
        dev->print(F("ClosingDelayOption:     '"));
        dev->print(closingDelay._optionEnabled ? F("enabled' to ") : F("off'"));
        if (closingDelay._optionEnabled)
        {
            dev->print(closingDelay._minutes);
            dev->print(F(" minute(s) after sunset"));
        }
        dev->println(F(""));

        // show artificialMorningLight
        auto artificialMorningLight = m_mySelf->m_dataStorage->getArtificialMorningLightOption();
        dev->print(F("ArtificialMorningLight: '"));
        dev->print(artificialMorningLight._optionEnabled ? F("enabled' on from ") : F("off'"));
        if (artificialMorningLight._optionEnabled)
        {
            dev->print(artificialMorningLight._hour);
            dev->print(F(":"));
            if (artificialMorningLight._minute < 10)
                dev->print(F("0"));
            dev->print(artificialMorningLight._minute);
            dev->print(F(" o'clock to sunrise"));
        }
        dev->println(F(""));
    }

    // show door status
    dev->print(F("Doorstatus:        '"));
    dev->print(m_mySelf->m_doorSteering->getDoorStateHumanReadable());
    dev->println(F("'"));
    dev->print(F("DoorTimeout:       '"));
    dev->print(m_mySelf->m_doorSteering->getTimeoutForDoorMoving());
    dev->println(F(" sec'"));

    // show light status
    dev->print(F("Lightstatus        '"));
    if (m_mySelf->m_lightSteering->getLightStatus())
        dev->println(F("ON'"));
    else
        dev->println(F("OFF'"));

    return 0;
}
