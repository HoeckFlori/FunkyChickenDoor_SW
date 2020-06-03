#include "Model.hpp"

Model::Model(ITimeKeeper *timekeeper)
    : m_timeKeeper(timekeeper)
{
}

void Model::cycle()
{
    // TODO(FHk) collect data here!

    // do timing stuff
    if (m_timeKeeper)
    {
        // the current time
        auto new_Time = m_timeKeeper->getCurrentTime();
        if (m_timestamp != new_Time)
        { // time has changed
            m_timestamp = new_Time;
            // inform listener, if available
            if (m_eventListener)
            {
                m_eventListener->modelListener(IModelEventListener::Event::TIME_UPDATE);
            }
        }
        auto new_sunrise = m_timeKeeper->getTodaysSunrise();
        auto new_sunset = m_timeKeeper->getTodaysSunset();
        if ((new_sunrise != m_sunrise) || (new_sunset != m_sunset))
        { // sunrise or sunset or both has changed
            m_sunrise = new_sunrise;
            m_sunset = new_sunset;
            // inform listener, if available
            if (m_eventListener)
            {
                m_eventListener->modelListener(IModelEventListener::Event::SUNRISE_SUNSET_UPDATE);
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

ITimeKeeper *Model::getTimeKeeper()
{
    return m_timeKeeper;
}