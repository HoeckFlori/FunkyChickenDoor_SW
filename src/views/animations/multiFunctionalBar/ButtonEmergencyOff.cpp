#include "ButtonEmergencyOff.hpp"
#include <TFT.h>

ButtonEmergencyOff::ButtonEmergencyOff(IModel *model, Adafruit_GFX *tft, uint16_t colorBackground, uint16_t colorFrames, uint16_t colorText,
                                       int16_t x0, int16_t y0, int16_t ButtonSizeX, int16_t ButtonSizeY)
    : ButtonBase(tft, colorBackground, x0, y0, ButtonSizeX, ButtonSizeY)
    , WidgetBase(model, tft, colorBackground, colorFrames, colorText, x0, y0)
{
    setup();
}

void ButtonEmergencyOff::setup()
{
    doorStateHandling();
}
int16_t ButtonEmergencyOff::getWidthOfWidget()
{
    return m_buttonSizeX;
}
int16_t ButtonEmergencyOff::getHeightOfWidget()
{
    return m_buttonSizeY;
}
void ButtonEmergencyOff::cycle()
{
}

void ButtonEmergencyOff::passModelEventToWidget(IModelEventListener::Event event)
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

void ButtonEmergencyOff::drawActive()
{
    clearButtonArea();
    m_tft->setTextSize(1);
    m_tft->setCursor(m_x0 + (m_buttonSizeX / 2) - 12, m_y0 + 5);
    m_tft->print(F("STOP"));
}
void ButtonEmergencyOff::drawInActive()
{
    clearButtonArea();
    m_tft->setTextSize(1);
    m_tft->setCursor(m_x0 + (m_buttonSizeX / 2) - 3, m_y0 + 5);
    m_tft->print(F("-"));
}

void ButtonEmergencyOff::doorStateHandling()
{
    auto doorState = m_model->getDoorState();
    switch (doorState)
    {
    case IDoorSteering::DoorState::UNDEFINED:
        drawInActive();
        break;
    case IDoorSteering::DoorState::OPEN:
        drawInActive();
        break;
    case IDoorSteering::DoorState::CLOSED:
        drawInActive();
        break;
    case IDoorSteering::DoorState::OPENING:
        drawActive();
        break;
    case IDoorSteering::DoorState::CLOSING:
        drawActive();
        break;
    case IDoorSteering::DoorState::ERROR:
        drawInActive();
        break;
    case IDoorSteering::DoorState::ERROR_CLOSING:
        drawInActive();
        break;
    case IDoorSteering::DoorState::ERROR_OPENING:
        drawInActive();
        break;
    }
}