#include "MultiFunctionalBar.hpp"
#include <TFT.h>

MultiFunctionalBar::MultiFunctionalBar(IModel *model, Adafruit_GFX *tft, uint16_t colorBackground, uint16_t colorFrames, uint16_t colorText,
                                       int16_t x0, int16_t y0)
    : WidgetBase(model, tft, colorBackground, colorFrames, colorText, x0, y0)
    , m_buttonModeChange(NULL)
    , m_buttonUpDown(NULL)
    , m_buttonEmergencyOff(NULL)
    , m_buttonLightBulb(NULL)
{
}

void MultiFunctionalBar::setup()
{
    drawBaseGrid();

    // drawClearInnerPartOfBar();

    // drawInnerSegmentation();

    buildBarAccordingMode();
}

int16_t MultiFunctionalBar::getWidthOfWidget()
{
    return m_outerWidth;
}

int16_t MultiFunctionalBar::getHeightOfWidget()
{
    return m_outerHeight;
}

void MultiFunctionalBar::cycle()
{
    // todo
}

void MultiFunctionalBar::passModelEventToWidget(IModelEventListener::Event event)
{
    // work off event here in general ...
    // ... nothing to do here

    // work off event in buttons
    if (m_buttonModeChange)
        m_buttonModeChange->passModelEventToWidget(event);
    if (m_buttonUpDown)
        m_buttonUpDown->passModelEventToWidget(event);
    if (m_buttonEmergencyOff)
        m_buttonEmergencyOff->passModelEventToWidget(event);
    if (m_buttonLightBulb)
        m_buttonLightBulb->passModelEventToWidget(event);
}

void MultiFunctionalBar::drawBaseGrid()
{
    // clear area
    m_tft->fillRoundRect(/*x0*/ m_x0,
                         /*y0*/ m_y0,
                         /*w */ m_outerWidth,
                         /*h */ m_outerHeight,
                         /*radius*/ 0, m_defaultColorBackground);

    // upper line
    m_tft->fillRoundRect(/*x0*/ m_x0,
                         /*y0*/ m_y0,
                         /*w */ m_outerWidth,
                         /*h */ m_outerFrameThickness,
                         /*radius*/ 0, m_defaultColorFrames);

    // inner segmentation
    // - first from left with 2px thick
    m_tft->fillRoundRect(/*x0*/ m_x0 + m_gapSizeX,
                         /*y0*/ m_y0,
                         /*w */ 2,
                         /*h */ m_outerHeight,
                         /*radius*/ 0, m_defaultColorFrames);

    // - second line normal
    m_tft->drawLine(/*x0*/ m_x0 + 2 * m_gapSizeX + 2,
                    /*y0*/ m_y0,
                    /*x1*/ m_x0 + 2 * m_gapSizeX + 2,
                    /*y1*/ m_y0 + m_outerHeight, m_defaultColorFrames);

    // - third line normal
    m_tft->drawLine(/*x0*/ m_x0 + 3 * m_gapSizeX + 3,
                    /*y0*/ m_y0,
                    /*x1*/ m_x0 + 3 * m_gapSizeX + 3,
                    /*y1*/ m_y0 + m_outerHeight, m_defaultColorFrames);
}

void MultiFunctionalBar::buildBarAccordingMode()
{
    if (m_model)
    {
        auto mode = m_model->getMode();
        if (mode == IOperationModeManager::OpMode::MANUAL)
        {
            // Button A
            delete m_buttonModeChange;
            m_buttonModeChange = new ButtonModeChange(WidgetBase::m_model, WidgetBase::m_tft, WidgetBase::m_defaultColorBackground,
                                                      WidgetBase::m_defaultColorFrames, WidgetBase::m_defaultColorText, getX0ForButton(1),
                                                      WidgetBase::m_y0 + m_outerFrameThickness, m_gapSizeX, m_gapSizeY);

            // Button B
            delete m_buttonLightBulb;
            m_buttonLightBulb = new ButtonLightBulb(WidgetBase::m_model, WidgetBase::m_tft, WidgetBase::m_defaultColorBackground,
                                                    WidgetBase::m_defaultColorFrames, WidgetBase::m_defaultColorText, getX0ForButton(2),
                                                    WidgetBase::m_y0 + m_outerFrameThickness, m_gapSizeX, m_gapSizeY);

            // Button C
            delete m_buttonUpDown;
            m_buttonUpDown =
                new ButtonUpDown(WidgetBase::m_model, WidgetBase::m_tft, WidgetBase::m_defaultColorBackground, WidgetBase::m_defaultColorFrames,
                                 WidgetBase::m_defaultColorText, getX0ForButton(3), WidgetBase::m_y0 + m_outerFrameThickness, m_gapSizeX, m_gapSizeY);

            // Button D
            delete m_buttonEmergencyOff;
            m_buttonEmergencyOff = new ButtonEmergencyOff(WidgetBase::m_model, WidgetBase::m_tft, WidgetBase::m_defaultColorBackground,
                                                          WidgetBase::m_defaultColorFrames, WidgetBase::m_defaultColorText, getX0ForButton(4),
                                                          WidgetBase::m_y0 + m_outerFrameThickness, m_gapSizeX, m_gapSizeY);
        }

        else if (mode == IOperationModeManager::OpMode::AUTOMATIC)
        {
            // Button A
            delete m_buttonModeChange;
            m_buttonModeChange = new ButtonModeChange(WidgetBase::m_model, WidgetBase::m_tft, WidgetBase::m_defaultColorBackground,
                                                      WidgetBase::m_defaultColorFrames, WidgetBase::m_defaultColorText, getX0ForButton(1),
                                                      WidgetBase::m_y0 + m_outerFrameThickness, m_gapSizeX, m_gapSizeY);

            // Button B
            delete m_buttonLightBulb;
            m_buttonLightBulb = new ButtonLightBulb(WidgetBase::m_model, WidgetBase::m_tft, WidgetBase::m_defaultColorBackground,
                                                    WidgetBase::m_defaultColorFrames, WidgetBase::m_defaultColorText, getX0ForButton(2),
                                                    WidgetBase::m_y0 + m_outerFrameThickness, m_gapSizeX, m_gapSizeY);

            // Button C
            // -nothing-

            // Button D
            delete m_buttonEmergencyOff;
            m_buttonEmergencyOff = new ButtonEmergencyOff(WidgetBase::m_model, WidgetBase::m_tft, WidgetBase::m_defaultColorBackground,
                                                          WidgetBase::m_defaultColorFrames, WidgetBase::m_defaultColorText, getX0ForButton(4),
                                                          WidgetBase::m_y0 + m_outerFrameThickness, m_gapSizeX, m_gapSizeY);
        }
    }
}

int16_t MultiFunctionalBar::getX0ForButton(int buttonNumber /* 1, 2, 3, 4 */)
{
    int16_t accu(0);
    if (buttonNumber == 1)
        return accu;
    accu += m_gapSizeX + 2;
    if (buttonNumber == 2)
        return accu;
    accu += m_gapSizeX + 1;
    if (buttonNumber == 3)
        return accu;
    accu += m_gapSizeX + 1;
    return accu;
}