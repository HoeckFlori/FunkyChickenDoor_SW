#include "ManualView.hpp"
#include "RTClib.h"

ManualView::ManualView(IModel *model, IOperatingElements *operatingElements, Adafruit_GFX *tft)
    : OptionModeBaseLayout::OptionModeBaseLayout(model, operatingElements, tft,
                                                 tft->newColor(/*R*/ 0x00, /*G*/ 0x00, /*B*/ 0x4D) /*background color*/,
                                                 ST7735_RED /*color of frames*/,
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
        break;
    case IKeyEventListener::Event::BUTTON_ENTER:
        m_model->requestModeChange();
        break;
    case IKeyEventListener::Event::BUTTON_UP:
        break;
    case IKeyEventListener::Event::BUTTON_DOWN:
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
    m_tft->setCursor(35, 31);
    m_tft->print(F("MANUAL"));
    m_tft->setTextColor(m_defaultColorText); // switch text color bach to default
}
