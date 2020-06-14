#pragma once

#include <stdint.h>
#include "../IModelEventListener.hpp"

class IWidget
{
public:
    virtual ~IWidget() = default;

    /**
     * @brief Setup the widget. Draw the base layout, texts, ...
     */
    virtual void setup() = 0;

    /**
     * @brief Get the Width of Widget object
     * 
     * @return int16_t The Width in x direction.
     */
    virtual int16_t getWidthOfWidget() = 0;

    /**
     * @brief Get the Height Of Widget object
     * 
     * @return int16_t The Height in y direction
     */
    virtual int16_t getHeightOfWidget() = 0;

    /**
     * @brief The cycle method that must be called regulary from the 'main-cycle'
     */
    virtual void cycle() = 0;

    /**
     * @brief Views have the possibility to receive Events from the Model by a listener. This
     *        method can be used to pass these events to Widgets which are embedded in a View.
     * 
     * @param event The Model event to pass
     */
    virtual void passModelEventToWidget(IModelEventListener::Event event) = 0;
};