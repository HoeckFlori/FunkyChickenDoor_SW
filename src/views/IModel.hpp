#pragma once

#include "../IDoorSteering.hpp"
#include "../IOperationModeManager.hpp"
#include "../ITimeKeeper.hpp"
#include "IModelEventListener.hpp"

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
    virtual ITimeKeeper *getTimeKeeper() const = 0;

    /**
     * @brief Get the current status of the Door
     *
     * @return IDoorSteering::DoorState
     */
    virtual IDoorSteering::DoorState getDoorState() const = 0;

    /**
     * @brief Request a request of the OperationMode
     *
     */
    virtual void requestModeChange() = 0;

    /**
     * @brief Get the operation mode
     *
     * @return IOperationModeManager::OpMode
     */
    virtual IOperationModeManager::OpMode getMode() const = 0;

    /**
     * @brief Request to open the door. (It is just a request, several other things (e.g. the mode, the current status ...) can deny this request)
     */
    virtual void requestDoorOpen() = 0;

    /**
     * @brief Request to close the door. (It is just a request, several other things (e.g. the mode, the current status ...) can deny this request)
     */
    virtual void requestDoorClose() = 0;

    /**
     * @brief Commands an emergency stop for all componenets that perform potentially dangerous interactions (e.g. door movements).
     */
    virtual void orderEmergencyStop() = 0;

    /**
     * @brief Get the status of the 'Arificial Light'
     *
     * @return true  Light is on
     * @return false Light is off
     */
    virtual bool getLightState() const = 0;
};