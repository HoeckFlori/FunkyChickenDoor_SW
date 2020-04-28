#pragma once

class IConsoleAgent
{
public:
    virtual ~IConsoleAgent() = default;

    virtual void cycle() = 0;
    // virtual char *getConsoleInput() = 0;
    // virtual void writeToConsole(const char *cstr) = 0;
};