#include "WidgetBase.hpp"
#include <TFT.h>

WidgetBase::WidgetBase(IModel *model, Adafruit_GFX *tft,
                       uint16_t colorBackground,
                       uint16_t colorFrames,
                       uint16_t colorText,
                       int16_t x0, int16_t y0)
    : m_model(model), m_tft(tft),
      m_defaultColorBackground(colorBackground),
      m_defaultColorFrames(colorFrames),
      m_defaultColorText(colorText),
      m_x0(x0), m_y0(y0)
{
}