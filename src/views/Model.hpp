#pragma once

#include "IModel.hpp"
#include "RTClib.h"

class Model : public virtual IModel
{
public:
    Model(ITimeKeeper *timeKeeper);
    ~Model() = default;

    // IModel
    void cycle() override;
    void registerModelEventListener(IModelEventListener *listener) override;
    void removeModelEventListener() override;
    ITimeKeeper *getTimeKeeper() override;

private:
    ITimeKeeper *m_timeKeeper;

    IModelEventListener *m_eventListener;

    // working variables
    DateTime m_timestamp;
    DateTime m_sunrise;
    DateTime m_sunset;
};