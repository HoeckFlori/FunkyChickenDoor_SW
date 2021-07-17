#include "Model.hpp"

Model::Model(ITimeKeeper *timekeeper, IDoorSteering *doorSteering, IOperationModeManager *opModeManager, ILightSteering *lightSteering)
    : m_timeKeeper(timekeeper)
    , m_doorSteering(doorSteering)
    , m_opModeManager(opModeManager)
    , m_lightSteering(lightSteering)
    , m_eventListener(nullptr)
    , m_doorState(IDoorSteering::DoorState::UNDEFINED)
    , m_lightState(false)
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
        { // at least time has changed
            // check if date has changed too
            bool dateChange(false);
            if ((m_timestamp.day() != newTime.day()) || (m_timestamp.year() != newTime.year()))
            {
                dateChange = true;
            }
            // set new time
            m_timestamp = newTime;
            // inform listener, if available
            if (m_eventListener != nullptr)
            {
                m_eventListener->modelListener(IModelEventListener::Event::TIME_UPDATE);
                if (dateChange)
                    m_eventListener->modelListener(IModelEventListener::Event::DATE_UPDATE);
            }
        }

        auto newSunrise = m_timeKeeper->getTodaysSunrise();
        auto newSunset = m_timeKeeper->getTodaysSunset();
        auto newOpeningTime = m_timeKeeper->getTodayOpeningTime();
        auto newClosingTime = m_timeKeeper->getTodayClosingTime();
        if ((newSunrise != m_sunrise) || (newSunset != m_sunset) || (newOpeningTime != m_openingTime) || (newClosingTime != m_closingTime))
        { // sunrise or sunset or both has changed
            m_sunrise = newSunrise;
            m_sunset = newSunset;
            m_openingTime = newOpeningTime;
            m_closingTime = newClosingTime;

            // inform listener, if available
            if (m_eventListener != nullptr)
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
            if (m_eventListener != nullptr)
            {
                m_eventListener->modelListener(IModelEventListener::Event::DOOR_STATE_CHANGED);
            }
        }
    }

    // --- fo light steering stuff ---
    if (m_lightSteering)
    {
        bool lightState = m_lightSteering->getLightStatus();
        if (m_lightState != lightState)
        {
            m_lightState = lightState;
            // inform listener, if available
            if (m_eventListener != nullptr)
            {
                m_eventListener->modelListener(IModelEventListener::Event::LIGHT_STATE_CHANGED);
            }
        }
    }

    // add event for mode change here
}

void Model::registerModelEventListener(IModelEventListener *listener)
{
    m_eventListener = listener;
}

void Model::removeModelEventListener()
{
    // delete m_eventListener;
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

void Model::requestModeChange()
{
    auto currentMode = m_opModeManager->getMode();
    // toggle the operation mode (at the moment we just have two modes)
    if (currentMode == IOperationModeManager::OpMode::AUTOMATIC)
        m_opModeManager->changeMode(IOperationModeManager::OpMode::MANUAL);
    else
        m_opModeManager->changeMode(IOperationModeManager::OpMode::AUTOMATIC);
}

IOperationModeManager::OpMode Model::getMode() const
{
    return m_opModeManager->getMode();
}

void Model::requestDoorOpen()
{
    m_doorSteering->openDoor();
}

void Model::requestDoorClose()
{
    m_doorSteering->closeDoor();
}

void Model::orderEmergencyStop()
{
    m_doorSteering->emergencyStop();
}

bool Model::getLightState() const
{
    return m_lightSteering->getLightStatus();
}