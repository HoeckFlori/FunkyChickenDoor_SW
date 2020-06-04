#include "AutomaticView.hpp"
#include "RTClib.h"

AutomaticView::AutomaticView(IModel *model, Adafruit_GFX *tft)
    : OptionModeBaseLayout::OptionModeBaseLayout(model, tft,
                                                 ST7735_BLACK /*background color*/,
                                                 ST7735_RED /*color of frames*/,
                                                 ST7735_WHITE /*text color*/)
{
    drawBaseLayout();
}

void AutomaticView::cycle()
{
    // call parent method
    OptionModeBaseLayout::cycle();
}

void AutomaticView::modelListener(IModelEventListener::Event event)
{

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
        if (auto timekeeperAccess = m_model->getTimeKeeper())
        {
            auto sunrise = timekeeperAccess->getTodaysSunrise();
            printSunriseToScreen(sunrise.hour(), sunrise.minute());
            auto sunset = timekeeperAccess->getTodaysSunset();
            printSunsetToScreen(sunset.hour(), sunset.minute());
        }
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
    printTimeToScreen(/*x*/ 65, /*y*/ 50, /*textsize*/ 1, /*showSeconds*/ false, hour, minute);
}

void AutomaticView::printSunsetToScreen(int hour, int minute)
{
    printTimeToScreen(/*x*/ 65, /*y*/ 65, /*textsize*/ 1, /*showSeconds*/ false, hour, minute);
}