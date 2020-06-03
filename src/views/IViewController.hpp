#pragma once

class IViewController
{
public:
    virtual ~IViewController() = default;

    /**
     * @brief The cycle method that must be called regulary from the 'main-cycle'
     */
    virtual void cycle() = 0;
};