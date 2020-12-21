#include "DoorSteering.hpp"
#include "Arduino.h"
#include "IDataStorage.hpp"

DoorSteering::DoorSteering(IDataStorage *dataStorage, int motorUpPin, int motorDownPin, int doorUpPin, int doorDownPin)
    : m_doorSwitchStatus(SwitchStatus::UNDEFINED)
    , m_dataStorage(dataStorage)
    , m_doorState(DoorState::UNDEFINED)
    , c_motorUpPin(motorUpPin)
    , c_motorDownPin(motorDownPin)
    , m_doorSwitchUp(doorUpPin /*pin*/, c_defaultDebounceTime, true /* puEnable*/, true /*invert*/)
    , m_doorSwitchDown(doorDownPin /*pin*/, c_defaultDebounceTime, true /* puEnable*/, true /*invert*/)
    , m_timeoutHandlerActive(false)
    , m_lastTimeoutStartTimestamp_msec(0)
{
    m_doorSwitchUp.begin();
    m_doorSwitchDown.begin();

    pinMode(c_motorUpPin, OUTPUT);
    pinMode(c_motorDownPin, OUTPUT);
    stopMotorActions();
    readDoorSwitchStatus();

    // load timeout settings, write a default if not already done
    if (m_dataStorage)
    {
        auto timeoutFromMemory = m_dataStorage->getDoorMovingTimeout();
        if (timeoutFromMemory < c_timeoutMinimum || timeoutFromMemory > c_timeoutMaximum)
        { // Set default if value is not initialized in non-volatile memory
            m_timeout_sec = c_defaultTimeoutDoorMoving;
            m_dataStorage->setDoorMovingTimeout(m_timeout_sec);
        }
        else
        {
            m_timeout_sec = timeoutFromMemory;
        }
    }
}

void DoorSteering::cycle()
{
    readDoorSwitchStatus();

    // Do timeout handling during movement operations
    if (doorIsCurrentlyMoving())
    {
        // something is going on -> check timeout
        if (timeOutOccureed())
        {
            stopMotorActions();
            Serial.print(F("ERROR during "));
            if (m_doorState == DoorState::OPENING)
            {
                m_doorState = DoorState::ERROR_OPENING;
                Serial.println(F("opening!"));
            }
            else if (m_doorState == DoorState::CLOSING)
            {
                m_doorState = DoorState::ERROR_CLOSING;
                Serial.println(F("closing!"));
            }
            else
            {
                Serial.println(F(" 'unknown'!"));
            }
        }
    }

    // do stuff during different DoorStates
    switch (m_doorState)
    {
    case DoorState::UNDEFINED:
        /* code */
        break;
    case DoorState::ERROR:
        /* code */
        break;
    case DoorState::OPEN:
        if (m_doorSwitchStatus != SwitchStatus::OPEN)
        {
            // 'Retighten' the door
            openDoor();
        }
        break;
    case DoorState::CLOSED:
        if (m_doorSwitchStatus != SwitchStatus::CLOSED)
        {
            // 'Retighten' the door
            closeDoor();
        }
        break;
    case DoorState::OPENING:
        if (m_doorSwitchStatus == SwitchStatus::OPEN)
        {
            stopMotorActions();
            stopTimeoutHandler();
            m_doorState = DoorState::OPEN;
        }
        break;
    case DoorState::ERROR_OPENING:
        /* code */
        break;
    case DoorState::CLOSING:
        if (m_doorSwitchStatus == SwitchStatus::CLOSED)
        {
            stopMotorActions();
            stopTimeoutHandler();
            m_doorState = DoorState::CLOSED;
        }
        break;
    case DoorState::ERROR_CLOSING:
        /* code */
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
    case DoorState::ERROR:
        return F("ERROR");
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
    case DoorState::ERROR_OPENING:
        return F("ERROR_OPENING");
        break;
    case DoorState::ERROR_CLOSING:
        return F("ERROR_CLOSING");
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

void DoorSteering::closeDoor()
{
    m_doorState = DoorState::CLOSING;
    startTimeoutHandler();
    activateMotorDown();
}

void DoorSteering::openDoor()
{
    m_doorState = DoorState::OPENING;
    startTimeoutHandler();
    activateMotorUp();
}

uint16_t DoorSteering::getTimeoutForDoorMoving()
{
    return m_timeout_sec;
}

void DoorSteering::setTimeoutForDoorMoving(uint16_t seconds)
{
    if (seconds < c_timeoutMinimum)
    { // The timeout shall be in a range from [1sec : 10 minuten], anything else wouldn't make sense
        m_timeout_sec = c_timeoutMinimum;
    }
    else if (seconds > c_timeoutMaximum)
    {
        m_timeout_sec = c_timeoutMaximum;
    }
    else
    {
        m_timeout_sec = seconds;
    }
    m_dataStorage->setDoorMovingTimeout(m_timeout_sec);
}

void DoorSteering::eventTimeKeeperListener(ITimeKeeperListener::Event event)
{
    if (event == ITimeKeeperListener::Event::openDoor)
    {
        stopMotorActions();
        openDoor();
    }
    else if (event == ITimeKeeperListener::Event::closeDoor)
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
    else if (!up && down)
    {
        retVal = SwitchStatus::CLOSED;
    }

    m_doorSwitchStatus = retVal;
}

bool DoorSteering::doorIsCurrentlyMoving()
{
    if ((m_doorState == DoorState::CLOSING) || (m_doorState == DoorState::OPENING))
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
    m_timeoutHandlerActive = true;
    m_lastTimeoutStartTimestamp_msec = millis();
}

void DoorSteering::stopTimeoutHandler()
{
    m_timeoutHandlerActive = false;
}

bool DoorSteering::timeOutOccureed()
{
    if (m_timeoutHandlerActive)
    {
        auto currentTimeStamp = millis();
        if (currentTimeStamp >= (m_lastTimeoutStartTimestamp_msec + 1000 * m_timeout_sec))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        // no timeout handler active
        return false;
    }
}