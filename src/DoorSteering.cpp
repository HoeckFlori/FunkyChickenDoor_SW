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
    case DoorState::INITIALIZING:
        return F("INITIALIZING");
        break;
    case DoorState::OPEN:
        return F("OPEN");
        break;
    case DoorState::CLOSED:
        return F("CLOSED");
        break;
    case DoorState::OPENING:
        return F("OPENING");
        break;
    case DoorState::CLOSING:
        return F("CLOSING");
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
    m_doorState = DoorState::INITIALIZING;
    // TODO(FHk)
}

void DoorSteering::closeDoor()
{
    m_doorState = DoorState::CLOSING;
    // TODO(FHk)
}

void DoorSteering::openDoor()
{
    m_doorState = DoorState::OPENING;
    // TODO(FHk)
}