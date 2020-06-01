#pragma once

class IViewController
{
public:
    virtual ~IViewController() = default;

    virtual void cycle() = 0;
};