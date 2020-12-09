#include "DoorSteering.hpp"
#include "Arduino.h"

DoorSteering::DoorSteering(int motorUpPin, int motorDownPin, int doorUpPin, int doorDownPin)
    : m_doorSwitchStatus(SwitchStatus::UNDEFINED),
      m_doorState(DoorState::UNDEFINED),
      c_motorUpPin(motorUpPin),
      c_motorDownPin(motorDownPin),
      m_doorSwitchUp(doorUpPin /*pin*/, m_defaultDebounceTime, true /* puEnable*/, true /*invert*/),
      m_doorSwitchDown(doorDownPin /*pin*/, m_defaultDebounceTime, true /* puEnable*/, true /*invert*/)
{
    m_doorSwitchUp.begin();
    m_doorSwitchDown.begin();

    pinMode(c_motorUpPin, OUTPUT);
    pinMode(c_motorDownPin, OUTPUT);
    stopMotorActions();
    readDoorSwitchStatus();
}

void DoorSteering::cycle()
{
    readDoorSwitchStatus();


    if( doorIsCurrentlyMoving() )
    {
        // something is going on -> check timeout
        if( timeOutOccureed() )
        {
            emergencyStop();
        }
    }

    
    switch (m_doorState)
    {
    case DoorState::UNDEFINED:
        /* code */
        break;
    case DoorState::INITIALIZING:
        /* code */
        break;
    case DoorState::OPEN:
        /* code */
        break;
    case DoorState::CLOSED:
        /* code */
        break;
    case DoorState::OPENING:
        if (m_doorSwitchStatus == SwitchStatus::OPEN)
        {
            stopMotorActions();
            m_doorState = DoorState::OPEN;
        }
        break;
    case DoorState::CLOSING:
        if (m_doorSwitchStatus == SwitchStatus::CLOSED)
        {
            stopMotorActions();
            m_doorState = DoorState::CLOSED;
        }
        break;
    case DoorState::ERROR:
        /* code */
        break;
    
    default:
        break;
    }
}

IDoorSteering::DoorState DoorSteering::getDoorState() const
{
    return m_doorState;
}

String DoorSteering::getDoorStateHumanReadable() const
{
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

void DoorSteering::emergencyStop()
{
    m_doorState = DoorState::ERROR;
    stopMotorActions();
}

void DoorSteering::initDoor()
{
    if (!doorIsCurrentlyMoving())
    {
        m_doorState = DoorState::INITIALIZING;
        // TODO(FHk)
    }
}

void DoorSteering::closeDoor()
{
//    if (!doorIsCurrentlyMoving())
//    {
        m_doorState = DoorState::CLOSING;
        startTimeoutHandler();
        activateMotorDown();
//    }
}

void DoorSteering::openDoor()
{
//    if (!doorIsCurrentlyMoving())
//    {
        m_doorState = DoorState::OPENING;
        startTimeoutHandler();
        activateMotorUp();
//    }
}

void DoorSteering::eventTimeKeeperListener(ITimeKeeperListener::Event event)
{
    if(event == ITimeKeeperListener::Event::openDoor)
    {
        stopMotorActions();
        openDoor();
    }
    else if(event == ITimeKeeperListener::Event::closeDoor)
    {
        stopMotorActions();
        closeDoor();
    }
}

void DoorSteering::stopMotorActions()
{
    digitalWrite(c_motorUpPin, LOW);
    digitalWrite(c_motorDownPin, LOW);
}

void DoorSteering::activateMotorUp()
{
    digitalWrite(c_motorUpPin, HIGH);
    digitalWrite(c_motorDownPin, LOW);
}

void DoorSteering::activateMotorDown()
{
    digitalWrite(c_motorUpPin, LOW);
    digitalWrite(c_motorDownPin, HIGH);
}


void DoorSteering::readDoorSwitchStatus()
{
    auto up = m_doorSwitchUp.read();
    auto down = m_doorSwitchDown.read(); 

    SwitchStatus retVal = SwitchStatus::UNDEFINED;

    if (up && !down)
    {
        retVal = SwitchStatus::OPEN;
    }
    else if(!up && down)
    {
        retVal = SwitchStatus::CLOSED;
    }

    m_doorSwitchStatus = retVal;
}

bool DoorSteering::doorIsCurrentlyMoving()
{
    if(    (m_doorState == DoorState::CLOSING)
        || (m_doorState == DoorState::OPENING)
        || (m_doorState == DoorState::INITIALIZING) )
    {
        return true;
    }
    else
    {
        return false;
    }
}


void DoorSteering::startTimeoutHandler()
{
    // todo
}

bool DoorSteering::timeOutOccureed()
{
    // todo
    return false;
}