#pragma once

#include "IModel.hpp"
#include "IOperationModeManager.hpp"
#include "RTClib.h"

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
    void requestDoorOpen() override;
    void requestDoorClose() override;
    void orderEmergencyStop() override;

  private:
    ITimeKeeper *m_timeKeeper;
    IDoorSteering *m_doorSteering;
    IOperationModeManager *m_opModeManager;
    IModelEventListener *m_eventListener;

    // working variables
    DateTime m_timestamp;
    DateTime m_sunrise;
    DateTime m_sunset;
    DateTime m_openingTime;
    DateTime m_closingTime;
    IDoorSteering::DoorState m_doorState;
};