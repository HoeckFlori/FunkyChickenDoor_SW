#include "ButtonLightBulb.hpp"

ButtonLightBulb::ButtonLightBulb(IModel *model, Adafruit_GFX *tft, uint16_t colorBackground, uint16_t colorFrames, uint16_t colorText, int16_t x0,
                                 int16_t y0, int16_t ButtonSizeX, int16_t ButtonSizeY)
    : WidgetBase(model, tft, colorBackground, colorFrames, colorText, x0, y0)
    , m_buttonSizeX(ButtonSizeX)
    , m_buttonSizeY(ButtonSizeY)
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

void ButtonLightBulb::clearButtonArea()
{
    m_tft->fillRect(m_x0, m_y0, m_buttonSizeX, m_buttonSizeY, m_defaultColorBackground);
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

void ButtonLightBulb::lightStateHandling()
{
    if (m_model)
    {
        switch (m_model->getMode())
        {
        case IOperationModeManager::OpMode::AUTOMATIC:
            clearButtonArea();

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
