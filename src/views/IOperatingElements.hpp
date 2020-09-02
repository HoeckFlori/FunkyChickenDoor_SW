#pragma once

#include "IKeyEventListener.hpp"

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

    /**
     * @brief Register listener for user-triggered key events.
     *        (a previously registered listener is deleted!)
     * 
     * @param listener The listener
     */
    virtual void registerKeyEventListener(IKeyEventListener *listener) = 0;

    /**
     * @brief Remove the listener again.
     */
    virtual void removeKeyEventListener() = 0;
};