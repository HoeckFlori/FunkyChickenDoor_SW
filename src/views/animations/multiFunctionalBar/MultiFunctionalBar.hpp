#pragma once

#include "../WidgetBase.hpp"

#include "ButtonEmergencyOff.hpp"
#include "ButtonLightBulb.hpp"
#include "ButtonModeChange.hpp"
#include "ButtonUpDown.hpp"

class MultiFunctionalBar : public WidgetBase
{
  public:
    MultiFunctionalBar(IModel *model, Adafruit_GFX *tft, uint16_t colorBackground, uint16_t colorFrames, uint16_t colorText, int16_t x0, int16_t y0);
    ~MultiFunctionalBar() = default;

    // IWidget
    void setup() override;
    int16_t getWidthOfWidget() override;
    int16_t getHeightOfWidget() override;
    void cycle() override;
    void passModelEventToWidget(IModelEventListener::Event event) override;

  private:
    // Widget size itself
    const int16_t m_outerWidth = 160;
    const int16_t m_outerHeight = 20;
    const int16_t m_outerFrameThickness = 2;
    const int8_t m_amountOfFields = 4;
    const int16_t m_gapSizeX = (m_outerWidth - 4) / 4;
    const int16_t m_gapSizeY = m_outerHeight - m_outerFrameThickness;

    // Buttons
    ButtonModeChange *m_buttonModeChange;
    ButtonUpDown *m_buttonUpDown;
    ButtonEmergencyOff *m_buttonEmergencyOff;
    ButtonLightBulb *m_buttonLightBulb;

    void drawBaseGrid();
    void buildBarAccordingMode();
    int16_t getX0ForButton(int buttonNumber /* 1, 2, 3, 4 */);
};
