#include "ButtonLightBulb.hpp"
#include <TFT.h>

ButtonLightBulb::ButtonLightBulb(IModel *model, Adafruit_GFX *tft, uint16_t colorBackground, uint16_t colorFrames, uint16_t colorText, int16_t x0,
                                 int16_t y0, int16_t ButtonSizeX, int16_t ButtonSizeY)
    : ButtonBase(tft, colorBackground, x0, y0, ButtonSizeX, ButtonSizeY)
    , WidgetBase(model, tft, colorBackground, colorFrames, colorText, x0, y0)
{
    setup();
}

void ButtonLightBulb::setup()
{
    lightStateHandling();
}
int16_t ButtonLightBulb::getWidthOfWidget()
{
    return m_buttonSizeX;
}
int16_t ButtonLightBulb::getHeightOfWidget()
{
    return m_buttonSizeY;
}
void ButtonLightBulb::cycle()
{
}

void ButtonLightBulb::passModelEventToWidget(IModelEventListener::Event event)
{
    switch (event)
    {
    case IModelEventListener::Event::LIGHT_STATE_CHANGED:
        if (m_model)
        {
            lightStateHandling();
        }
        break;
    default:
        break;
    }
}

void ButtonLightBulb::drawBulb(bool lightOn, int x0, int y0)
{
    // draw bulb base
    m_tft->drawRect(/* x0 */ 5 + m_x0 + x0,
                    /* y0 */ 8 + m_y0 + y0,
                    /* w  */ 5,
                    /* h  */ 9, m_defaultColorText);

    // draw bulb glass
    if (lightOn)
    {
        m_tft->fillCircle(/* x0 */ 7 + m_x0 + x0,
                          /* y0 */ 7 + m_y0 + y0,
                          /* r  */ 5, ST7735_YELLOW);
    }
    else
    {
        m_tft->fillCircle(/* x0 */ 7 + m_x0 + x0,
                          /* y0 */ 7 + m_y0 + y0,
                          /* r  */ 5, m_defaultColorBackground);
    }

    m_tft->drawCircle(/* x0 */ 7 + m_x0 + x0,
                      /* y0 */ 7 + m_y0 + y0,
                      /* r  */ 5, m_defaultColorText);
}

void ButtonLightBulb::drawInActive()
{
    clearButtonArea();
    m_tft->setTextSize(1);
    m_tft->setCursor(m_x0 + (m_buttonSizeX / 2) - 3, m_y0 + 5);
    m_tft->print(F("-"));
}

void ButtonLightBulb::lightStateHandling()
{
    if (m_model)
    {
        switch (m_model->getMode())
        {
        case IOperationModeManager::OpMode::AUTOMATIC:
            clearButtonArea();
            drawBulb(m_model->getLightState(), 0, 0);
            m_tft->textSize(1);
            if (m_model->getArtificialLightOptionEnabled() == true)
            {
                m_tft->setCursor(m_x0 + (m_buttonSizeX / 2) - 5, m_y0 + 8);
                m_tft->print(F("auto"));
            }
            else
            {
                m_tft->setCursor(m_x0 + (m_buttonSizeX / 2) - 2, m_y0 + 8);
                m_tft->print(F("off"));
            }
            break;
        case IOperationModeManager::OpMode::MANUAL:
            clearButtonArea();
            drawBulb(m_model->getLightState(), (m_buttonSizeX / 2) - 7, 0);
            break;
        default:
            break;
        }
    }
}
