#pragma once

class IConsoleAgent
{
  public:
    virtual ~IConsoleAgent() = default;

    virtual void cycle() = 0;
};