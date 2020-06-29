#include "AutomaticView.hpp"
#include "RTClib.h"

AutomaticView::AutomaticView(IModel *model, IOperatingElements *operatingElements, Adafruit_GFX *tft)
    : OptionModeBaseLayout::OptionModeBaseLayout(model, operatingElements, tft,
                                                 ST7735_BLACK /*background color*/,
                                                 ST7735_RED /*color of frames*/,
                                                 ST7735_WHITE /*text color*/)
{
    drawBaseLayout();
    if (auto timekeeperAccess = m_model->getTimeKeeper())
    {
        auto sunrise = timekeeperAccess->getTodaysSunrise();
        printSunriseToScreen(sunrise.hour(), sunrise.minute());
        auto sunset = timekeeperAccess->getTodaysSunset();
        printSunsetToScreen(sunset.hour(), sunset.minute());
    }
}

void AutomaticView::cycle()
{
    // call parent method
    OptionModeBaseLayout::cycle();
}

void AutomaticView::modelListener(IModelEventListener::Event event)
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
        if (auto timekeeperAccess = m_model->getTimeKeeper())
        {
            auto sunrise = timekeeperAccess->getTodaysSunrise();
            printSunriseToScreen(sunrise.hour(), sunrise.minute());
            auto sunset = timekeeperAccess->getTodaysSunset();
            printSunsetToScreen(sunset.hour(), sunset.minute());
        }
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

void AutomaticView::keyEventListener(IKeyEventListener::Event event)
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

void AutomaticView::drawBaseLayout()
{
    // call base method to (re)draw the basics
    OptionModeBaseLayout::drawBaseLayout();

    // AutomaticView specials:
    m_tft->setTextSize(1);

    m_tft->setTextColor(ST7735_GREEN); // change default text color
    m_tft->setCursor(25, 31);
    m_tft->print(F("AUTOMATIC"));
    m_tft->setTextColor(m_defaultColorText); // switch text color bach to default

    m_tft->setCursor(5, 50);
    m_tft->print(F("Sunrise:"));
    m_tft->setCursor(5, 65);
    m_tft->print(F("Sunset:"));
}

void AutomaticView::printSunriseToScreen(int hour, int minute)
{
    m_tft->setTextColor(m_defaultColorText);
    printTimeToScreen(/*x*/ 65, /*y*/ 50, /*textsize*/ 1, /*showSeconds*/ false, hour, minute);
}

void AutomaticView::printSunsetToScreen(int hour, int minute)
{
    m_tft->setTextColor(m_defaultColorText);
    printTimeToScreen(/*x*/ 65, /*y*/ 65, /*textsize*/ 1, /*showSeconds*/ false, hour, minute);
}