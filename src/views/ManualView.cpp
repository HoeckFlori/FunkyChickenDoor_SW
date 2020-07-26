#include "ManualView.hpp"
#include "RTClib.h"
#include "TFT.h"

ManualView::ManualView(IModel *model, IOperatingElements *operatingElements, Adafruit_GFX *tft)
    : OptionModeBaseLayout::OptionModeBaseLayout(model, operatingElements, tft,
                                                 tft->newColor(/*R*/ 0x00, /*G*/ 0x33, /*B*/ 0xCC) /*background color*/,
                                                 tft->newColor(/*R*/ 0xFF, /*G*/ 0x99, /*B*/ 0x00) /*color of frames*/,
                                                 ST7735_WHITE /*text color*/)
{
    drawBaseLayout();
}

void ManualView::cycle()
{
    // call parent method
    OptionModeBaseLayout::cycle();
}

void ManualView::modelListener(IModelEventListener::Event event)
{
    // local event handling
    switch (event)
    {
    case IModelEventListener::Event::TIME_UPDATE:
        if (auto timekeeperAccess = m_model->getTimeKeeper())
        {
            auto newTime = timekeeperAccess->getCurrentTime();
            printCurrentTimeToScreen(newTime.hour(), newTime.minute(), newTime.second());
        }
        break;
    case IModelEventListener::Event::DATE_UPDATE:
        if (auto timekeeperAccess = m_model->getTimeKeeper())
        {
            auto newTime = timekeeperAccess->getCurrentTime();
            printCurrentTimeToScreen(newTime.hour(), newTime.minute(), newTime.second());
        }
        break;
    case IModelEventListener::Event::SUNRISE_SUNSET_UPDATE:
        break;
    case IModelEventListener::Event::MODE_CHANGED:
        break;
    case IModelEventListener::Event::DOOR_STATE_CHANGED:
        break;
    case IModelEventListener::Event::NEW_ERROR_AVAILABLE:
        break;
    case IModelEventListener::Event::RELOAD_EVERYTHING:
        break;
    default:
        // uncomment not needed events above
        break;
    }

    // pass event to widget(s)
    if (m_doorWidget)
        m_doorWidget->passModelEventToWidget(event);
}

void ManualView::keyEventListener(IKeyEventListener::Event event)
{
    switch (event)
    {
    case IKeyEventListener::Event::BUTTON_BACK:
        m_model->orderEmergencyStop();
        break;
    case IKeyEventListener::Event::BUTTON_ENTER:
        m_model->requestModeChange();
        break;
    case IKeyEventListener::Event::BUTTON_UP:
        m_model->requestDoorOpen();
        break;
    case IKeyEventListener::Event::BUTTON_DOWN:
        m_model->requestDoorClose();
        break;
    case IKeyEventListener::Event::BUTTON_SETTINGS:
        break;
    }
}

void ManualView::drawBaseLayout()
{
    // call base method to (re)draw the basics
    OptionModeBaseLayout::drawBaseLayout();

    // ManualView specials:
    m_tft->setTextSize(1);

    m_tft->setTextColor(ST7735_GREEN); // change default text color
    m_tft->setCursor(35, 43);
    m_tft->print(F("MANUAL"));
    m_tft->setTextColor(m_defaultColorText); // switch text color bach to default
}
