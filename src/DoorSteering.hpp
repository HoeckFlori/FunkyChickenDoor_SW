#pragma once

#include "IDoorSteering.hpp"

class DoorSteering : public virtual IDoorSteering
{
public:
    DoorSteering();
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
    DoorState m_doorState;
};