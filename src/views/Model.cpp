#include "Model.hpp"

Model::Model(ITimeKeeper *timekeeper, IDoorSteering *doorSteering)
    : m_timeKeeper(timekeeper),
      m_doorSteering(doorSteering)
{
}

void Model::cycle()
{
    // TODO(FHk) collect data here!

    // --- do timing stuff ---
    if (m_timeKeeper)
    {
        // the current time
        auto newTime = m_timeKeeper->getCurrentTime();
        if (m_timestamp != newTime)
        { // time has changed
            m_timestamp = newTime;
            // inform listener, if available
            if (m_eventListener)
            {
                m_eventListener->modelListener(IModelEventListener::Event::TIME_UPDATE);
            }
        }
        auto newSunrise = m_timeKeeper->getTodaysSunrise();
        auto newSunset = m_timeKeeper->getTodaysSunset();
        if ((newSunrise != m_sunrise) || (newSunset != m_sunset))
        { // sunrise or sunset or both has changed
            m_sunrise = newSunrise;
            m_sunset = newSunset;
            // inform listener, if available
            if (m_eventListener)
            {
                m_eventListener->modelListener(IModelEventListener::Event::SUNRISE_SUNSET_UPDATE);
            }
        }
    }

    // --- do door steering stuff ---
    if (m_doorSteering)
    {
        auto newDoorState = m_doorSteering->getDoorState();
        if (m_doorState != newDoorState)
        {
            m_doorState = newDoorState;
            // inform listener, if available
            if (m_eventListener)
            {
                m_eventListener->modelListener(IModelEventListener::Event::DOOR_STATE_CHANGED);
            }
        }
    }
}

void Model::registerModelEventListener(IModelEventListener *listener)
{
    m_eventListener = listener;
}

void Model::removeModelEventListener()
{
    m_eventListener = nullptr;
}

ITimeKeeper *Model::getTimeKeeper() const
{
    return m_timeKeeper;
}

IDoorSteering::DoorState Model::getDoorState() const
{
    return m_doorState;
}