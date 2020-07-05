#pragma once
#include <WString.h>

class IDoorSteering
{
public:
    virtual ~IDoorSteering() = default;

    enum class DoorState
    {
        UNDEFINED,
        INITIALIZING,
        OPEN,
        CLOSED,
        OPENING,
        CLOSING,
        ERROR
    };

    virtual void cycle() = 0;
    virtual DoorState getDoorState() const = 0;
    virtual String getDoorStateHumanReadable() const = 0;
    virtual void emergencyStop() = 0;
    virtual void initDoor() = 0;
    virtual void closeDoor() = 0;
    virtual void openDoor() = 0;
};