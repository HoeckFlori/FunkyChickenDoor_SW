#include "DoorWidget.hpp"

DoorWidget::DoorWidget(IModel *model, Adafruit_GFX *tft,
                       uint16_t colorBackground,
                       uint16_t colorFrames,
                       uint16_t colorText,
                       int16_t x0, int16_t y0)
    : WidgetBase(model, tft,
                 colorBackground,
                 colorFrames,
                 colorText,
                 x0, y0)
{
}

void DoorWidget::setup()
{
    m_tft->drawRect(m_x0, m_y0, m_outerWidth, m_outerHeight, m_defaultColorFrames);
}

int16_t DoorWidget::getWidthOfWidget()
{
    return m_outerWidth;
}

int16_t DoorWidget::getHeightOfWidget()
{
    return m_outerHeight;
}

void DoorWidget::cycle()
{
}