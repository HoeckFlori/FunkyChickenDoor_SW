#include "ButtonBase.hpp"
#include <TFT.h>

ButtonBase::ButtonBase(Adafruit_GFX *tft, uint16_t colorBackground, int16_t x0, int16_t y0, int16_t ButtonSizeX, int16_t ButtonSizeY)
    : m_buttonSizeX(ButtonSizeX)
    , m_buttonSizeY(ButtonSizeY)
    , m_tft_Base(tft)
    , m_defaultColorBackground_Base(colorBackground)
    , m_x0_Base(x0)
    , m_y0_Base(y0)
{
}

void ButtonBase::clearButtonArea()
{
    m_tft_Base->fillRect(m_x0_Base, m_y0_Base, m_buttonSizeX, m_buttonSizeY, m_defaultColorBackground_Base);
}
