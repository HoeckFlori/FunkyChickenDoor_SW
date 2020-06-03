#pragma once
#include "IModelEventListener.hpp"
#include "../ITimeKeeper.hpp"

/**
 * @brief The central, UI independent data structure for the UI. The Model directly manages the
 *        data, logic and rules of the UI application part. It receives also user input from
 *        the controller. The Model do not know the actual View directly, just indirect via a 
 *        listener to inform it about data changes. 
 */
class IModel
{
public:
    virtual ~IModel() = default;

    /**
     * @brief The cycle method that must be called regulary from the 'main-cycle'
     */
    virtual void cycle() = 0;

    /**
     * @brief Register a Listener from View side to the model.
     * 
     * @param listener The listener. Normaly directly the View itself
     */
    virtual void registerModelEventListener(IModelEventListener *listener) = 0;

    /**
     * @brief Remove the View listener. Needed here because we use raw-pointer (in this Arduino environment)
     * 
     */
    virtual void removeModelEventListener() = 0;

    /**
     * @brief Get access to the Timerkeeper
     * 
     * @return Timekeeper* The Timekeeper
     */
    virtual ITimeKeeper *getTimeKeeper() = 0;
};