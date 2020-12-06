#pragma once


class ITimeKeeperListener
{
public:
    virtual ~ITimeKeeperListener() = default;

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