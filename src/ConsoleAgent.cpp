#include "ConsoleAgent.hpp"
#include <Arduino.h>
#include <avr/pgmspace.h>
#include "RTClib.h"

// helper to check the available RAM
extern unsigned int __bss_end;
extern unsigned int __heap_start;
extern void *__brkval;
uint16_t getFreeSram()
{
    uint8_t newVariable;
    // heap is empty, use bss as start memory address
    if ((uint16_t)__brkval == 0)
        return (((uint16_t)&newVariable) - ((uint16_t)&__bss_end));
    // use heap end as the start of the memory address
    else
        return (((uint16_t)&newVariable) - ((uint16_t)__brkval));
};

// the ConsoleAgent gets handled in a similar form like a singleton to access the members from the static command methods
ConsoleAgent *ConsoleAgent::m_mySelf = 0;

ConsoleAgent::ConsoleAgent(ITimeKeeper *timeKeeper) : m_timeKeeper(timeKeeper)
{
    m_mySelf = this;

    CLI.setDefaultPrompt("~");
    CLI.onConnect(connectFunction);
    CLI.addClient(Serial);

    // register commands
    //CLI.addCommand("help", (*function)(help(CLIClient * dev, int argc, char **argv)));
    CLI.addCommand("help", help);
    CLI.addCommand("memory", showMemory);
    CLI.addCommand("getTime", getDateTime);
    CLI.addCommand("setTime", setTime);
}

void ConsoleAgent::cycle()
{
    CLI.process();
}

// CLI_COMMAND(connectFunction)
int ConsoleAgent::connectFunction(CLIClient *dev, int argc, char **argv)
{
    dev->println(F("Hello to the Chicken door terminal"));
    dev->println(F("Type 'help' to list commands."));
    dev->println();
    return 0; // no error
}

int ConsoleAgent::help(CLIClient *dev, int argc, char **argv)
{
    dev->println(F(" Available commands for the Chicken Door Terminal:"));
    dev->println(F(" -> 'help'    Show this help context"));
    dev->println(F(" -> 'memory'  Show available RAM in bytes"));
    dev->println(F(" -> 'getTime' Show actual system time"));
    dev->println(F(" -> 'setTime' Set new time"));
    return 0; // no error
}

int ConsoleAgent::showMemory(CLIClient *dev, int argc, char **argv)
{
    dev->print(F("Available RAM: "));
    dev->print(getFreeSram());
    dev->println(F(" bytes"));
    return 0;
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
        dev->println(F("-> Usage: setTime 28.04.2020 02:30"));
        return -1;
    }
    else
    {
        // extract date
        {
            String date = argv[1];
            d = date.toInt();
            int indexOfColon1 = date.indexOf(F("."));
            m = date.substring(indexOfColon1 + 1).toInt();
            int indexOfColon2 = date.lastIndexOf(F("."));
            y = date.substring(indexOfColon2 + 1).toInt();
        }
        // extract time
        {
            String time = argv[2];
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
