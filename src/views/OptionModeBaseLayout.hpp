#pragma once

#include "ViewBase.hpp"
#include "animations/DoorWidget.hpp"

/**
 * @brief The OptionModeBaseLayout forms the basis layout for all implemented modes
 *        like the AutomaticMode, Manual Mode, ... . It ensures that the 'look and feel'
 *        is the same for every view and minimizes the work.
 *        (Always stay lazy but professional)
 */
class OptionModeBaseLayout : public ViewBase
{
public:
    OptionModeBaseLayout(IModel *model, Adafruit_GFX *tft,
                         uint16_t colorBackground,
                         uint16_t colorFrames,
                         uint16_t colorText);
    virtual ~OptionModeBaseLayout() = default;

    // IView
    void cycle() override;

protected:
    DoorWidget *m_doorWidget; // The door state animation which is part of each functional view

    void drawBaseLayout() override;

    /**
     * @brief Print the now actual time to the baselayout
     * 
     * @param hour   Hour 0-24
     * @param minute Minute 0-59
     * @param second Second 0-59
     */
    void printCurrentTimeToScreen(int hour, int minute, int second);

    /**
     * @brief Write time in format hh::mm::ss to screen
     * 
     * @param x0       Initial position left
     * @param y0       Initial position up
     * @param textSize Text size can be 1-3. Basic size is 5x8. Each size is multiplied by it.
     * @param showSeconds Show the seconds information
     * @param hour     Hour 0-24
     * @param minute   Minute 0-59
     * @param second   Second0-59
     * @param color    Text color default ST7735_WHITE
     */
    void printTimeToScreen(int x0, int y0, int textSize, bool showSeconds, int hour, int minute, int second = 0);
};