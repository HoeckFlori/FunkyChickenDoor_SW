#include "Arduino.h"
#include "EnergySavingMaster.hpp"

EnergySavingMaster::EnergySavingMaster(uint16_t timeToPowerSavingSeconds)
 : m_systemPowerState(SystemPowerStates::NORMAL),
   c_timeToPowerSavingMillis(timeToPowerSavingSeconds*1000),
   m_workingTimerActive(true),
   m_nextTimerEvent(0)
{
    adjustTargetTimeForEnergySaving();
}

void EnergySavingMaster::userEvent()
{
    changeSystemPowerState(SystemPowerStates::NORMAL);
}

void EnergySavingMaster::domainEvent()
{
    changeSystemPowerState(SystemPowerStates::NORMAL);
}

void EnergySavingMaster::cycle()
{
    if(m_workingTimerActive)
    {
        auto currentTimeNow = millis();
        auto currentTimePlusDelay =currentTimeNow + 100; // I use the window to compensate timing issues
        if ( (currentTimeNow >= m_nextTimerEvent) && (m_nextTimerEvent <= currentTimePlusDelay))
        {
            // timing event!
            if (m_systemPowerState == SystemPowerStates::NORMAL)
            {
                changeSystemPowerState(SystemPowerStates::ENERGYSAVING);
            }
            // here would be the place for a "Deepsleep extension"!
        }
    }
}

void EnergySavingMaster::registerClient(IEnergySavingClient* energySavingClient)
{
    // find free place for new client
    bool noFreePlaceForClient(true);
    for(int runner(0); runner < c_amountOfEnergySavingClients; runner++)
    {
        if ( m_energySavingClients[runner] == nullptr )
        {
            m_energySavingClients[runner] = energySavingClient;
            noFreePlaceForClient = false;
            // debug only ...
            // Serial.print("Registered IEnergySavingClient* on place ");
            // Serial.println(runner);
            break; // leave loop
        }
    }
    // error message if buffer is full
    if(noFreePlaceForClient)
    {
        Serial.println("ERROR: No more place to store additional IEnergySavingClient*!");
    }
}

void EnergySavingMaster::informAllEnergySavingClients()
{
    for(int runner(0); runner < c_amountOfEnergySavingClients; runner++)
    {
        if ( m_energySavingClients[runner] != nullptr )
        {
            m_energySavingClients[runner]->updateAboutSystemPowerState(m_systemPowerState);
        }
    }
}

void EnergySavingMaster::adjustTargetTimeForEnergySaving()
{
    switch (m_systemPowerState)
    {
    case SystemPowerStates::NORMAL:
        m_nextTimerEvent = millis() + c_timeToPowerSavingMillis;
        break;
    case SystemPowerStates::ENERGYSAVING:
        // disable timer
        m_workingTimerActive = false;         
        break;            
    }
}

void EnergySavingMaster::changeSystemPowerState(SystemPowerStates newState)
{
    if(m_systemPowerState != newState)
    {
        m_systemPowerState = newState;
        Serial.print("SystemPowerState changed to '");

        switch (m_systemPowerState)
        {
        case SystemPowerStates::NORMAL:
            Serial.println("NORMAL'");
            m_workingTimerActive = true;
            adjustTargetTimeForEnergySaving();
            break;
        case SystemPowerStates::ENERGYSAVING:
            Serial.println("ENERGYSAVING'");
            m_workingTimerActive = false;
            break;
        }
        
        informAllEnergySavingClients();
    }
}
