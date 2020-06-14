#include "ManualView.hpp"
#include "RTClib.h"

ManualView::ManualView(IModel *model, Adafruit_GFX *tft)
    : OptionModeBaseLayout::OptionModeBaseLayout(model, tft,
                                                 ST7735_WHITE /*background color*/,
                                                 ST7735_RED /*color of frames*/,
                                                 ST7735_BLACK /*text color*/)
{
    drawBaseLayout();
}

ManualView::~ManualView()
{
    // delete m_doorWidget;
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
    case Event::TIME_UPDATE:
        if (auto timekeeperAccess = m_model->getTimeKeeper())
        {
            auto newTime = timekeeperAccess->getCurrentTime();
            printCurrentTimeToScreen(newTime.hour(), newTime.minute(), newTime.second());
        }
        break;
    case Event::SUNRISE_SUNSET_UPDATE:
        break;
    case Event::MODE_CHANGED:
        break;
    case Event::DOOR_STATE_CHANGED:
        break;
    case Event::NEW_ERROR_AVAILABLE:
        break;
    case Event::RELOAD_EVERYTHING:
        break;
    default:
        // uncomment not needed events above
        break;
    }

    // pass event to widget(s)
    m_doorWidget->passModelEventToWidget(event);
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
