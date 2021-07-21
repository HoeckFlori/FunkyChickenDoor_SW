#pragma once

class IKeyEventListener
{
  public:
    virtual ~IKeyEventListener() = default;

    enum class Event
    {
        BUTTON_1,
        BUTTON_2,
        BUTTON_3,
        BUTTON_4
    };

    /**
     * @brief The 'callback' method, to be triggered if the user interacts with device control elements (button, turns, ...)
     *
     * @param event Information which interaction has taken place
     */
    virtual void keyEventListener(IKeyEventListener::Event event) = 0;
};