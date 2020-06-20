#pragma once

/**
 * @brief The interface for the user input operating elements.
 */
class IOperatingElements
{
public:
    virtual ~IOperatingElements() = default;

    /**
     * @brief The cycle method that must be called regulary from the 'main-cycle'
     */
    virtual void cycle() = 0;
};