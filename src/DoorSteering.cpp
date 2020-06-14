#include "DoorSteering.hpp"

DoorSteering::DoorSteering()
    : m_doorState(DoorState::UNDEFINED)
{
}

void DoorSteering::cycle()
{
    // TODO(FHk)
}

IDoorSteering::DoorState DoorSteering::getDoorState() const
{
    return m_doorState;
}

String DoorSteering::getDoorStateHumanReadable() const
{
    // return "test";

    switch (m_doorState)
    {
    case DoorState::UNDEFINED:
        return F("UNDEFINED");
        break;
    case DoorState::OPEN:
        return F("OPEN");
        break;
    case DoorState::CLOSED:
        return F("CLOSED");
        break;
    case DoorState::MOVING_UP:
        return F("MOVING UP");
        break;
    case DoorState::MOVING_DOWN:
        return F("MOVING DOWN");
        break;
    case DoorState::ERROR:
        return F("ERROR");
        break;
    default:
        return F(""); // this should never happen
    }
}

void DoorSteering::initDoor()
{
    // TODO(FHk)
}

void DoorSteering::closeDoor()
{
    // TODO(FHk)
}

void DoorSteering::openDoor()
{
    // TODO(FHk)
}