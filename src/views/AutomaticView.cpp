#include "AutomaticView.hpp"
#include "RTClib.h"
#include "TFT.h"

AutomaticView::AutomaticView(IModel *model, IOperatingElements *operatingElements, Adafruit_GFX *tft)
    : OptionModeBaseLayout::OptionModeBaseLayout(model, operatingElements, tft,
                                                 ST7735_BLACK /*background color*/,
                                                 ST7735_RED /*color of frames*/,
                                                 ST7735_WHITE /*text color*/)
{
    drawBaseLayout();
    if (auto timekeeperAccess = m_model->getTimeKeeper())
    {
        // print sunrise and sunset info
        auto sunrise = timekeeperAccess->getTodaysSunrise();
        printSunriseToScreen(sunrise.hour(), sunrise.minute());
        auto sunset = timekeeperAccess->getTodaysSunset();
        printSunsetToScreen(sunset.hour(), sunset.minute());

        // print the opening and closing time to the door widget
        auto doNotOpenBefore = timekeeperAccess->getTodayOpeningTime();
        printOpeningTime(doNotOpenBefore.hour(), doNotOpenBefore.minute());
        auto todaysClosingTime = timekeeperAccess->getTodayClosingTime();
        printClosingTime(todaysClosingTime.hour(), todaysClosingTime.minute());
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
    case IModelEventListener::Event::DATE_UPDATE:
        if (auto timekeeperAccess = m_model->getTimeKeeper())
        {
            auto time = timekeeperAccess->getCurrentTime();
            printCurrentDateToScreen(time.day(), time.month(), time.year());
        }
        break;
    case IModelEventListener::Event::SUNRISE_SUNSET_UPDATE:
        if (auto timekeeperAccess = m_model->getTimeKeeper())
        {
            auto sunrise = timekeeperAccess->getTodaysSunrise();
            printSunriseToScreen(sunrise.hour(), sunrise.minute());
            auto sunset = timekeeperAccess->getTodaysSunset();
            printSunsetToScreen(sunset.hour(), sunset.minute());
            auto doNotOpenBefore = timekeeperAccess->getTodayOpeningTime();
            printOpeningTime(doNotOpenBefore.hour(), doNotOpenBefore.minute());
            auto todaysClosingTime = timekeeperAccess->getTodayClosingTime();
            printClosingTime(todaysClosingTime.hour(), todaysClosingTime.minute());
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
        m_model->orderEmergencyStop();
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
    m_tft->setCursor(25, 43);
    m_tft->print(F("AUTOMATIC"));
    m_tft->setTextColor(m_defaultColorText); // switch text color bach to default

    m_tft->setCursor(5, 62);
    m_tft->print(F("Sunrise:"));
    m_tft->setCursor(5, 77);
    m_tft->print(F("Sunset:"));
}

void AutomaticView::printSunriseToScreen(int hour, int minute)
{
    m_tft->setTextColor(m_defaultColorText);
    printTimeToScreen(/*x*/ 65, /*y*/ 62, /*textsize*/ 1, /*showSeconds*/ false, hour, minute);
}

void AutomaticView::printSunsetToScreen(int hour, int minute)
{
    m_tft->setTextColor(m_defaultColorText);
    printTimeToScreen(/*x*/ 65, /*y*/ 77, /*textsize*/ 1, /*showSeconds*/ false, hour, minute);
}

void AutomaticView::printOpeningTime(int hour, int minute)
{
    m_tft->setTextColor(m_defaultColorText);
    printTimeToScreen(/*x*/ 120, /*y*/ 8, /*textsize*/ 1, /*showSeconds*/ false, hour, minute);
}

void AutomaticView::printClosingTime(int hour, int minute)
{
    m_tft->setTextColor(m_defaultColorText);
    printTimeToScreen(/*x*/ 120, /*y*/ 114, /*textsize*/ 1, /*showSeconds*/ false, hour, minute);
}