#pragma once

/**
 * @brief The TimeKeeperListener can be used to received events from the
 *        TimeKeeper instance in the system. To use it, you have to derive
 *        from ITimeKeeperListener and register the instance of your class
 *        to the TimeKeeper instance.
 */
class ITimeKeeperListener
{
  public:
    virtual ~ITimeKeeperListener() = default;

    /**
     * @brief The possible events that can be sent.
     *
     */
    enum class Event
    {
        openDoor,
        closeDoor,
        turnOnArtificialMorningLight,
        turnOffArtificialMorningLight,
    };

    /**
     * @brief The 'callback' method, that can be registered to the TimeKeeper.
     *
     * @param event  The information about events from the TimeKeeper
     */
    virtual void eventTimeKeeperListener(ITimeKeeperListener::Event event) = 0;
};