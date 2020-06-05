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
    // draw the frame of the complete 'door arrangement'
    m_tft->fillRoundRect(m_x0, m_y0, m_outerWidth, m_outerHeight, /*radius*/ 4, m_defaultColorFrames);
    drawClearInnerPartOfTheDoorAssembly();

    // scribling only
    //drawDoorflap(100 /* % open*/);
    //drawDoorflap(50  /* % open*/);
    //drawDoorflap(0   /* % open*/);
    drawError();
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

void DoorWidget::drawClearInnerPartOfTheDoorAssembly()
{
    m_tft->fillRoundRect(m_x0 + m_outerFrameThickness,
                         m_y0 + m_outerFrameThickness,
                         m_outerWidth - 2 * m_outerFrameThickness,
                         m_outerHeight - 2 * m_outerFrameThickness,
                         /*radius*/ 1,
                         m_defaultColorBackground);
}

void DoorWidget::drawDoorflap(uint8_t percentOpen)
{
    auto minY = m_y0 + m_outerFrameThickness;
    auto maxY = m_y0 + m_outerHeight - m_outerFrameThickness - m_doorflapHeight;
    auto yRange = maxY - minY;

    // check and correct upper limit if needed
    percentOpen = percentOpen > 100 ? 100 : percentOpen;

    auto yOffset = yRange * (100 - percentOpen) / 100;

    drawClearInnerPartOfTheDoorAssembly();

    auto color_greyOuterFrame = m_tft->newColor(0xA0, 0xA0, 0xA0);
    auto color_greyInlet = m_tft->newColor(0xE0, 0xE0, 0xE0);
    // draw outer frame
    m_tft->fillRoundRect(m_x0 + m_outerFrameThickness,
                         m_y0 + yOffset + m_outerFrameThickness,
                         m_doorflapWidth,
                         m_doorflapWidth,
                         /*radius*/ 1,
                         color_greyOuterFrame);
    // draw inlet
    m_tft->fillRoundRect(m_x0 + m_outerFrameThickness + 2,
                         m_y0 + yOffset + m_outerFrameThickness + 2,
                         m_doorflapWidth - 4,
                         m_doorflapWidth - 4,
                         /*radius*/ 1,
                         color_greyInlet);
}

void DoorWidget::drawError()
{
    drawClearInnerPartOfTheDoorAssembly();

    auto xCenter = m_x0 + m_outerWidth / 2;
    auto yCenter = m_y0 + m_outerHeight / 2;

    // Warning sign
    m_tft->fillTriangle(xCenter, yCenter - 20,      // top
                        xCenter - 17, yCenter + 10, // left
                        xCenter + 17, yCenter + 10, // right
                        ST7735_RED);
    m_tft->fillTriangle(xCenter, yCenter - 17,     // top
                        xCenter - 14, yCenter + 8, // left
                        xCenter + 14, yCenter + 8, // right
                        ST7735_YELLOW);

    // Exclamation mark
    m_tft->fillRect(xCenter - 1, yCenter - 10, 3, 12, ST7735_RED);
    m_tft->fillRect(xCenter - 1, yCenter + 4, 3, 3, ST7735_RED);
}