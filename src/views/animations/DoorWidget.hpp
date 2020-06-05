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

private:
    const int16_t m_outerWidth = 30;
    const int16_t m_outerHeight = 90;
};