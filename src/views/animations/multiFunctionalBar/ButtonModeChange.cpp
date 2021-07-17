#include "ButtonModeChange.hpp"
#include <TFT.h>

ButtonModeChange::ButtonModeChange(IModel *model, Adafruit_GFX *tft, uint16_t colorBackground, uint16_t colorFrames, uint16_t colorText, int16_t x0,
                                   int16_t y0, int16_t ButtonSizeX, int16_t ButtonSizeY)
    : ButtonBase(tft, colorBackground, x0, y0, ButtonSizeX, ButtonSizeY)
    , WidgetBase(model, tft, colorBackground, colorFrames, colorText, x0, y0)
{
    setup();
}

void ButtonModeChange::setup()
{
    drawText();
}
int16_t ButtonModeChange::getWidthOfWidget()
{
    return m_buttonSizeX;
}
int16_t ButtonModeChange::getHeightOfWidget()
{
    return m_buttonSizeY;
}
void ButtonModeChange::cycle()
{
}

void ButtonModeChange::passModelEventToWidget(IModelEventListener::Event)
{
    // nothing to do here with this simple button
}

void ButtonModeChange::drawText()
{
    clearButtonArea();
    m_tft->setTextSize(1);
    m_tft->setCursor(m_x0 + (m_buttonSizeX / 2) - 12, m_y0 + 5);
    m_tft->print(F("MODE"));
}
