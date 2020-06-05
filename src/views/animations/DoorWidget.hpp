#pragma once

#include "WidgetBase.hpp"

/**
 * @brief The DoorWidget show the door with its different states
 */
class DoorWidget : public WidgetBase
{
public:
    DoorWidget(IModel *model, Adafruit_GFX *tft,
               uint16_t colorBackground,
               uint16_t colorFrames,
               uint16_t colorText,
               int16_t x0, int16_t y0);
    ~DoorWidget() = default;

    // IWidget
    void setup() override;
    int16_t getWidthOfWidget() override;
    int16_t getHeightOfWidget() override;
    void cycle() override;

    /* next jobs here:
    [ ] add Doorstate to the Widget
    [ ] build animations for door closing and opening
    [x] build error screen to widget
    */

private:
    const int16_t m_outerWidth = 42;
    const int16_t m_outerHeight = 88;
    const int16_t m_outerFrameThickness = 2;
    const int16_t m_doorflapWidth = m_outerWidth - 2 * m_outerFrameThickness;
    const int16_t m_doorflapHeight = m_doorflapWidth; // we have a square flap

    void drawClearInnerPartOfTheDoorAssembly();
    void drawDoorflap(uint8_t percentOpen);
    void drawError();
};