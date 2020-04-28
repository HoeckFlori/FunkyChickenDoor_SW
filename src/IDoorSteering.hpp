#pragma once

class IDoorSteering
{
public:
    virtual ~IDoorSteering() = default;

    enum class DoorState
    {
        UNDEFINED,
        CLOSED,
        OPENING,
        OPEN,
        CLOSING
    };

    virtual DoorState getDoorState() = 0;
    virtual void initDoor() = 0;
    virtual void closeDoor() = 0;
    virtual void openDoor() = 0;
};