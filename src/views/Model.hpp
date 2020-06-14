#pragma once

#include "IModel.hpp"
#include "RTClib.h"

class Model : public virtual IModel
{
public:
    Model(ITimeKeeper *timeKeeper, IDoorSteering *doorSteering);
    ~Model() = default;

    // IModel
    void cycle() override;
    void registerModelEventListener(IModelEventListener *listener) override;
    void removeModelEventListener() override;
    ITimeKeeper *getTimeKeeper() const override;
    IDoorSteering::DoorState getDoorState() const override;

private:
    ITimeKeeper *m_timeKeeper;
    IDoorSteering *m_doorSteering;

    IModelEventListener *m_eventListener;

    // working variables
    DateTime m_timestamp;
    DateTime m_sunrise;
    DateTime m_sunset;
    IDoorSteering::DoorState m_doorState;
};