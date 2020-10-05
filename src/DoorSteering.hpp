#pragma once

#include "IDoorSteering.hpp"
#include <JC_Button.h>

class DoorSteering : public virtual IDoorSteering
{
public:
    DoorSteering(int motorUpPin, int motorDownPin, int doorUpPin, int doorDownPin);
    ~DoorSteering() = default;

    // IDoorSteering
    void cycle() override;
    DoorState getDoorState() const override;
    String getDoorStateHumanReadable() const override;
    void emergencyStop() override;
    void initDoor() override;
    void closeDoor() override;
    void openDoor() override;

private:
    const int m_defaultDebounceTime = 5; // ms

    enum SwitchStatus
    {
        UNDEFINED,
        CLOSED,
        OPEN
    };

    SwitchStatus m_doorSwitchStatus;

    DoorState m_doorState;
    const int c_motorUpPin;
    const int c_motorDownPin;
    Button m_doorSwitchUp;
    Button m_doorSwitchDown;

    void stopMotorActions();
    void activateMotorUp();
    void activateMotorDown();
    void readDoorSwitchStatus();

    bool doorIsCurrentlyMoving();

    // TODO
    void startTimeoutHandler();
    bool timeOutOccureed();
};