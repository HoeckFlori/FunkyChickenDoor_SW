#include "OptionModeBaseLayout.hpp"
#include "RTClib.h"

OptionModeBaseLayout::OptionModeBaseLayout(IModel *model, IOperatingElements *operatingElements, Adafruit_GFX *tft,
                                           uint16_t colorBackground,
                                           uint16_t colorFrames,
                                           uint16_t colorText)
    : ViewBase::ViewBase(model, operatingElements, tft, colorBackground, colorFrames, colorText),
      m_previousHourOfClock(-1),
      m_previousMinuteOfClock(-1),
      m_previousSecondOfClock(-1)
{
    m_doorWidget = new DoorWidget(m_model, m_tft,
                                  m_defaultColorBackground,
                                  m_defaultColorFrames,
                                  m_defaultColorText,
                                  /*x0*/ 114, /*y0*/ 20);
    m_doorWidget->passModelEventToWidget(IModelEventListener::Event::DOOR_STATE_CHANGED); // for setup in the view
}

void OptionModeBaseLayout::cycle()
{
    if (m_doorWidget)
    {
        m_doorWidget->cycle();
    }
}

void OptionModeBaseLayout::drawBaseLayout()
{
    // horizontal boarder left (upper one)
    m_tft->fillRect(/*x*/ 0, /*y*/ 37, /*w*/ 105, /*h*/ 3, m_defaultColorFrames);
    // horizontal boarder left (lower one)
    m_tft->fillRect(/*x*/ 0, /*y*/ 52, /*w*/ 105, /*h*/ 3, m_defaultColorFrames);
    //vertival boarder entire screen
    m_tft->fillRect(/*x*/ 105, /*y*/ 0, /*w*/ 4, /*h*/ m_tft->height(), m_defaultColorFrames);

    if (auto timekeeperAccess = m_model->getTimeKeeper())
    {
        // print date for the first time
        auto currentTime = timekeeperAccess->getCurrentTime();
        printCurrentDateToScreen(currentTime.day(), currentTime.month(), currentTime.year());

        // print summer/winter time information
        m_tft->setTextColor(m_defaultColorText);
        m_tft->setCursor(12, 119);
        m_tft->setTextSize(1);
        timekeeperAccess->getDaylightSaving() ? m_tft->print(F("<Summer time>")) : m_tft->print(F("<Winter time>"));
    }

    if (m_doorWidget)
        m_doorWidget->setup();
}

void OptionModeBaseLayout::printCurrentTimeToScreen(int hour, int minute, int second)
{
    printPartOfTimeToScreenHour(/*x*/ 5, /*y*/ 5, /*textsize*/ 2, hour);
    printPartOfTimeToScreenMinute(/*x*/ 5, /*y*/ 5, /*textsize*/ 2, minute);
    printPartOfTimeToScreenSecond(/*x*/ 5, /*y*/ 5, /*textsize*/ 2, second);
}

void OptionModeBaseLayout::printCurrentDateToScreen(int day, int month, int year)
{
    printDateToScreen(/*x*/ 5, /*y*/ 25, /*textsize*/ 1, day, month, year);
}

void OptionModeBaseLayout::printDateToScreen(int x0, int y0, int textSize, int day, int month, int year)
{
    m_tft->setTextSize(textSize);
    m_tft->setTextColor(m_defaultColorText);

    // clear previous date
    m_tft->fillRect(x0, y0,
                    /*w*/ (textSize * (5 + 1) * 10), // dd.mm.yyy
                    /*h*/ (textSize * 7),
                    m_defaultColorBackground);

    // print the day
    m_tft->setCursor(x0, y0);
    if (day < 10)
        m_tft->print(F("0"));
    m_tft->print(day);

    // print the month
    m_tft->print(F("."));
    if (month < 10)
        m_tft->print(F("0"));
    m_tft->print(month);

    // print the year
    m_tft->print(F("."));
    m_tft->print(year);
}

void OptionModeBaseLayout::printTimeToScreen(int x0, int y0, int textSize, bool showSeconds, int hour, int minute, int second)
{
    m_tft->setTextSize(textSize);
    m_tft->setTextColor(m_defaultColorText);

    // clear previous time (simple version)
    m_tft->fillRect(x0, y0,
                    /*w*/ (showSeconds ? (textSize * (5 + 1) * 8) : (textSize * (5 + 1) * 5)),
                    /*h*/ (textSize * 7),
                    m_defaultColorBackground);

    // print the hour
    m_tft->setCursor(x0, y0);
    if (hour < 10)
        m_tft->print(F("0"));
    m_tft->print(hour);

    // print the minute
    m_tft->print(F(":"));
    if (minute < 10)
        m_tft->print(F("0"));
    m_tft->print(minute);

    // print the second
    if (showSeconds)
    {
        m_tft->print(F(":"));
        if (second < 10)
            m_tft->print(F("0"));
        m_tft->print(second);
    }
}

void OptionModeBaseLayout::printPartOfTimeToScreenHour(int x0, int y0, int textSize, int hour)
{
    if (m_previousHourOfClock != hour)
    {
        m_tft->setTextSize(textSize);

        // overwrite/clear last second value
        if (m_previousHourOfClock > -1)
        {
            m_tft->setTextColor(m_defaultColorBackground);
            m_tft->setCursor(x0, y0);
            if (m_previousHourOfClock < 10)
                m_tft->print(F("0"));
            m_tft->print(m_previousHourOfClock);
        }

        // set new hour for next overwrite action
        m_previousHourOfClock = hour;

        // print the new hour value
        m_tft->setTextColor(m_defaultColorText);
        m_tft->setCursor(x0, y0);
        if (hour < 10)
            m_tft->print(F("0"));
        m_tft->print(hour);
    }
}

void OptionModeBaseLayout::printPartOfTimeToScreenMinute(int x0, int y0, int textSize, int minute)
{
    if (m_previousMinuteOfClock != minute)
    {
        m_tft->setTextSize(textSize);

        // overwrite/clear last second value
        if (m_previousMinuteOfClock > -1)
        {
            m_tft->setTextColor(m_defaultColorBackground);
            m_tft->setCursor((x0 + 3 * textSize * 6 /* width of a character*/), (y0));
            if (m_previousMinuteOfClock < 10)
                m_tft->print(F("0"));
            m_tft->print(m_previousMinuteOfClock);
        }

        // set new minute for next overwrite action
        m_previousMinuteOfClock = minute;

        // print the new minute value
        m_tft->setTextColor(m_defaultColorText);
        m_tft->setCursor((x0 + 2 * textSize * 6 /* width of a character*/), (y0));
        m_tft->print(F(":"));
        if (minute < 10)
            m_tft->print(F("0"));
        m_tft->print(minute);
    }
}

void OptionModeBaseLayout::printPartOfTimeToScreenSecond(int x0, int y0, int textSize, int second)
{
    if (m_previousSecondOfClock != second)
    {
        m_tft->setTextSize(textSize);

        // overwrite/clear last second value
        if (m_previousSecondOfClock > -1)
        {
            m_tft->setTextColor(m_defaultColorBackground);
            m_tft->setCursor((x0 + 6 * textSize * 6 /* width of a character*/), (y0));
            if (m_previousSecondOfClock < 10)
                m_tft->print(F("0"));
            m_tft->print(m_previousSecondOfClock);
        }

        // set new second for next overwrite action
        m_previousSecondOfClock = second;

        // print the new second value
        m_tft->setTextColor(m_defaultColorText);
        m_tft->setCursor((x0 + 5 * textSize * 6 /* width of a character*/), (y0));
        m_tft->print(F(":"));
        if (second < 10)
            m_tft->print(F("0"));
        m_tft->print(second);
    }
}