#pragma once

#include "IEnergySavingMaster.hpp"

class EnergySavingMaster : public virtual IEnergySavingMaster
{
  public:
    EnergySavingMaster(uint16_t timeToPowerSavingSeconds);
    virtual ~EnergySavingMaster() = default;

    // IEnergySavingPreventor
    void userEvent() override;
    void domainEvent() override;

    // IEnergySavingMaster
    void cycle() override;
    void registerClient(IEnergySavingClient *energySavingClient) override;

  private:
    /**
     * @brief Inform all registrated clients about the current SystemPowerState of the device
     */
    void informAllEnergySavingClients();

    /**
     * @brief Readjust the timer for the current SystemPowerState (if present)
     */
    void adjustTargetTimeForEnergySaving();

    /**
     * @brief Change the SystemPowerState, start timer if needed, inform all registered clients.
     *        If the state is already valid, nothing happens.
     *
     * @param newState The new systemwide valid PowerState
     */
    void changeSystemPowerState(SystemPowerStates newState);

    static const int c_amountOfEnergySavingClients = 2;
    IEnergySavingClient *m_energySavingClients[c_amountOfEnergySavingClients] =
        {}; // !!! the size is static, there are no dynamic container in these environment
    SystemPowerStates m_systemPowerState;
    const uint32_t c_timeToPowerSavingMillis;
    bool m_workingTimerActive;
    unsigned long m_nextTimerEvent;
};