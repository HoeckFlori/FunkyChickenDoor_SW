#pragma once

#include "IModel.hpp"
#include "RTClib.h"
#include "IOperationModeManager.hpp"

class Model : public virtual IModel
{
public:
    Model(ITimeKeeper *timeKeeper, IDoorSteering *doorSteering, IOperationModeManager *opModeManager);
    ~Model() = default;

    // IModel
    void cycle() override;
    void registerModelEventListener(IModelEventListener *listener) override;
    void removeModelEventListener() override;
    ITimeKeeper *getTimeKeeper() const override;
    IDoorSteering::DoorState getDoorState() const override;
    void requestModeChange() override;

private:
    ITimeKeeper *m_timeKeeper;
    IDoorSteering *m_doorSteering;
    IOperationModeManager *m_opModeManager;

    IModelEventListener *m_eventListener;

    // // working variables
    DateTime m_timestamp;
    DateTime m_sunrise;
    DateTime m_sunset;
    IDoorSteering::DoorState m_doorState;
};