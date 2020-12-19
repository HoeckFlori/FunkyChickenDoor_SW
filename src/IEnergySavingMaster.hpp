#pragma once

enum SystemPowerStates
{
    NORMAL,
    ENERGYSAVING // backlight dimming, ... , (?)
};

/**
 * @brief SystemPowerState relevant clients who has to get informed about state changes
 *
 */
class IEnergySavingClient
{
  public:
    virtual ~IEnergySavingClient() = default;

    virtual void updateAboutSystemPowerState(SystemPowerStates newState) = 0;
};

/**
 * @brief The source for events who influence the system wide power state (SystemPowerStates).
 *        Each client who wants to influence the SystemPowerState needs access to this interface.
 */
class IEnergySavingPreventor
{
  public:
    virtual ~IEnergySavingPreventor() = default;

    /**
     * @brief Fire the information of a user interaction with the system, like button interaction
     */
    virtual void userEvent() = 0;

    /**
     * @brief Fire the information of a domain relevant interaction, like door opening
     */
    virtual void domainEvent() = 0;
};

/**
 * @brief The EnergySavingMaster is the central instance for the management of the system wide
 *        SystemPowerStates who influences the the energy consumption behavior of the system.
 */
class IEnergySavingMaster : public virtual IEnergySavingPreventor
{
  public:
    virtual ~IEnergySavingMaster() = default;

    virtual void cycle() = 0;

    /**
     * @brief Register a client who needs information about changes of the PowerStateHandling
     *
     * @param energySavingClient The client (IEnergySavingClient)
     */
    virtual void registerClient(IEnergySavingClient *energySavingClient) = 0;
};