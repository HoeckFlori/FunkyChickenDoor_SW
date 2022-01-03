#pragma once

#include <WString.h>

/**
 * @brief The OperationModeManager has the task to hold the OperationMode for the system.
 *        The Mode gets also stored and restored from nonvolatile memory after a power
 *        loss or reset.
 */
class IOperationModeManager
{
  public:
    virtual ~IOperationModeManager() = default;

    enum class OpMode : int
    {
        UNDEFINED,
        AUTOMATIC,
        MANUAL
    };

    // /**
    //  * @brief The cycle for this module
    //  */
    // virtual void cycle() = 0;

    /**
     * @brief Get the actual system wide set OperationMode
     *
     * @return OperationMode The current Mode
     */
    virtual OpMode getMode() const = 0;

    /**
     * @brief The new system wide OperationMode
     *
     * @param newMode The new mode
     */
    virtual void changeMode(OpMode newMode) = 0;

    /**
     * @brief Return the current OperationMode in a human readable form
     *
     * @return String The Operation Mode
     */
    virtual String getOpModeHumanReadable() const = 0;
};