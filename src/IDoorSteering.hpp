#pragma once
#include <WString.h>

class IDoorSteering
{
  public:
    virtual ~IDoorSteering() = default;

    enum class DoorState
    {
        UNDEFINED,
        ERROR,
        OPEN,
        CLOSED,
        OPENING,
        ERROR_OPENING,
        CLOSING,
        ERROR_CLOSING
    };

    /**
     * @brief The cylce for the daily work
     *
     */
    virtual void cycle() = 0;

    /**
     * @brief Return the status of the door
     *
     * @return DoorState The actual door state
     */
    virtual DoorState getDoorState() const = 0;

    /**
     * @brief Return the status of the door in a human readable form
     *
     * @return String The door state as string
     */
    virtual String getDoorStateHumanReadable() const = 0;

    /**
     * @brief Stop motor steering immediately and set error state
     *
     */
    virtual void emergencyStop() = 0;

    /**
     * @brief Start door closing process
     *
     */
    virtual void closeDoor() = 0;

    /**
     * @brief Start door opening process
     *
     */
    virtual void openDoor() = 0;

    /**
     * @brief Get the used timeout for door movements in seconds.
     *
     * @return uint16_t The time in seconds
     */
    virtual uint16_t getTimeoutForDoorMoving() = 0;

    /**
     * @brief Set the timeout for door movements in seconds. The value is also stored non-volatile in the memory
     *        and will be used again at the next system start. The value must be in a range between 1 second and
     *        600 seconds (10 minute), otherwise it will be moved there.
     *
     * @param seconds The new timeout in seconds
     */
    virtual void setTimeoutForDoorMoving(uint16_t seconds) = 0;
};