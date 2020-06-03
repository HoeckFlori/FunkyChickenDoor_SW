#pragma once

#include "OptionModeBaseLayout.hpp"

/**
 * @brief The View in which the 'Automatic Mode' is visualized
 *        (The mode that works with sunrise and sunset)
  */
class AutomaticView : public OptionModeBaseLayout
{
public:
    explicit AutomaticView(IModel *model, Adafruit_GFX *tft);
    ~AutomaticView() = default;

    // IView
    void cycle() override;

    // IModelViewListener
    void modelListener(IModelEventListener::Event event) override;

private:
    /**
     * @brief Print the todays sunrise to the screen
     * 
     * @param hour   Hour 0-24
     * @param minute Minute 0-59
     */
    void printSunriseToScreen(int hour, int minute);

    /**
     * @brief Print the todays sunset to the screen
     * 
     * @param hour   Hour 0-24
     * @param minute Minute 0-59
     */
    void printSunsetToScreen(int hour, int minute);
};