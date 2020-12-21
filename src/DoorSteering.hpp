#pragma once

#include "IDoorSteering.hpp"
#include "ITimeKeeperListener.hpp"
#include <JC_Button.h>

// forward declarations
class IDataStorage;

class DoorSteering : public virtual IDoorSteering, public virtual ITimeKeeperListener
{
  public:
    DoorSteering(IDataStorage *dataStorage, int motorUpPin, int motorDownPin, int doorUpPin, int doorDownPin);
    ~DoorSteering() = default;

    // IDoorSteering
    void cycle() override;
    DoorState getDoorState() const override;
    String getDoorStateHumanReadable() const override;
    void emergencyStop() override;
    void closeDoor() override;
    void openDoor() override;
    uint16_t getTimeoutForDoorMoving() override;
    void setTimeoutForDoorMoving(uint16_t seconds) override;

    // ITimeKeeperListener
    void eventTimeKeeperListener(ITimeKeeperListener::Event event) override;

  private:
    const int c_defaultDebounceTime = 5;            // ms
    const uint16_t c_defaultTimeoutDoorMoving = 30; // sec
    const uint16_t c_timeoutMinimum = 1;            // sec
    const uint16_t c_timeoutMaximum = 600;          // sec

    enum SwitchStatus
    {
        UNDEFINED,
        CLOSED,
        OPEN
    };

    SwitchStatus m_doorSwitchStatus;
    IDataStorage *m_dataStorage;
    DoorState m_doorState;
    const int c_motorUpPin;
    const int c_motorDownPin;
    Button m_doorSwitchUp;
    Button m_doorSwitchDown;
    uint16_t m_timeout_sec;
    bool m_timeoutHandlerActive;
    unsigned long m_lastTimeoutStartTimestamp_msec;

    void stopMotorActions();
    void activateMotorUp();
    void activateMotorDown();

    void readDoorSwitchStatus();
    bool doorIsCurrentlyMoving();

    void startTimeoutHandler();
    void stopTimeoutHandler();
    bool timeOutOccureed();
};