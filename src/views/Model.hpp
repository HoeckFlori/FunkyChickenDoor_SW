#pragma once

#include "../ILightSteering.hpp"
#include "IModel.hpp"
#include "IOperationModeManager.hpp"
#include "RTClib.h"

class Model : public virtual IModel
{
  public:
    Model(ITimeKeeper *timeKeeper, IDoorSteering *doorSteering, IOperationModeManager *opModeManager, ILightSteering *lightSteering);
    ~Model() = default;

    // IModel
    void cycle() override;
    void registerModelEventListener(IModelEventListener *listener) override;
    void removeModelEventListener() override;
    ITimeKeeper *getTimeKeeper() const override;
    IDoorSteering::DoorState getDoorState() const override;
    void requestModeChange() override;
    IOperationModeManager::OpMode getMode() const override;
    void requestDoorOpen() override;
    void requestDoorClose() override;
    void requestDoorToggling() override;
    void orderEmergencyStop() override;
    bool getLightState() const override;
    bool getArtificialLightOptionEnabled() const override;
    void requestLightToggling() override;

  private:
    ITimeKeeper *m_timeKeeper;
    IDoorSteering *m_doorSteering;
    IOperationModeManager *m_opModeManager;
    ILightSteering *m_lightSteering;
    IModelEventListener *m_eventListener;

    // working variables
    DateTime m_timestamp;
    DateTime m_sunrise;
    DateTime m_sunset;
    DateTime m_openingTime;
    DateTime m_closingTime;
    IDoorSteering::DoorState m_doorState;
    bool m_lightState;
};