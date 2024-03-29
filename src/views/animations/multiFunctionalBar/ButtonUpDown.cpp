#include "ButtonUpDown.hpp"
#include <TFT.h>

ButtonUpDown::ButtonUpDown(IModel *model, Adafruit_GFX *tft, uint16_t colorBackground, uint16_t colorFrames, uint16_t colorText, int16_t x0,
                           int16_t y0, int16_t ButtonSizeX, int16_t ButtonSizeY)
    : ButtonBase(tft, colorBackground, x0, y0, ButtonSizeX, ButtonSizeY)
    , WidgetBase(model, tft, colorBackground, colorFrames, colorText, x0, y0)
{
    setup();
}

void ButtonUpDown::setup()
{
    doorStateHandling();
}
int16_t ButtonUpDown::getWidthOfWidget()
{
    return m_buttonSizeX;
}
int16_t ButtonUpDown::getHeightOfWidget()
{
    return m_buttonSizeY;
}
void ButtonUpDown::cycle()
{
}

void ButtonUpDown::passModelEventToWidget(IModelEventListener::Event event)
{
    switch (event)
    {
    case IModelEventListener::Event::DOOR_STATE_CHANGED:
        if (m_model)
        {
            doorStateHandling();
        }
        break;
    default:
        break;
    }
}

void ButtonUpDown::doorStateHandling()
{
    auto doorState = m_model->getDoorState();
    switch (doorState)
    {
    case IDoorSteering::DoorState::UNDEFINED:
        drawUp();
        break;
    case IDoorSteering::DoorState::OPEN:
        drawDown();
        break;
    case IDoorSteering::DoorState::CLOSED:
        drawUp();
        break;
    case IDoorSteering::DoorState::OPENING:
        drawPause();
        break;
    case IDoorSteering::DoorState::CLOSING:
        drawPause();
        break;
    case IDoorSteering::DoorState::ERROR:
        drawUp();
        break;
    case IDoorSteering::DoorState::ERROR_CLOSING:
        drawUp();
        break;
    case IDoorSteering::DoorState::ERROR_OPENING:
        drawDown();
        break;
    }
}

void ButtonUpDown::drawInActive()
{
    clearButtonArea();
    m_tft->setTextSize(1);
    m_tft->setCursor(m_x0 + (m_buttonSizeX / 2) - 3, m_y0 + 5);
    m_tft->print(F("-"));
}

void ButtonUpDown::drawUp()
{
    clearButtonArea();
    // clang-format off
    m_tft->fillTriangle( m_x0 + (m_buttonSizeX / 2),     m_y0 + 4,
                         m_x0 + (m_buttonSizeX / 2) + 5, m_y0 + m_buttonSizeY - 4,
                         m_x0 + (m_buttonSizeX / 2) - 5, m_y0 + m_buttonSizeY - 4,
                         m_defaultColorText);
    // clang-format on
}

void ButtonUpDown::drawDown()
{
    clearButtonArea();
    // clang-format off
    m_tft->fillTriangle( m_x0 + (m_buttonSizeX / 2),     m_y0 + m_buttonSizeY - 4,
                         m_x0 + (m_buttonSizeX / 2) + 5, m_y0 + 4,
                         m_x0 + (m_buttonSizeX / 2) - 5, m_y0 + 4,
                         m_defaultColorText);
    // clang-format on
}

void ButtonUpDown::drawPause()
{
    clearButtonArea();

    // clang-format off
    m_tft->fillRect( m_x0 + (m_buttonSizeX / 2) - 6,
                     m_y0 + 3,
                     4,
                     12,
                     m_defaultColorText);

    m_tft->fillRect( m_x0 + (m_buttonSizeX / 2) + 2,
                     m_y0 + 3,
                     4,
                     12,
                     m_defaultColorText);
    // clang-format on
}
