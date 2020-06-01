#include "OptionModeBaseLayout.hpp"

OptionModeBaseLayout::OptionModeBaseLayout(IModel *model, Adafruit_GFX *tft,
                                           uint16_t colorBackground,
                                           uint16_t colorFrames,
                                           uint16_t colorText)
    : ViewBase::ViewBase(model, tft, colorBackground, colorFrames, colorText)
{
    drawBaseLayout();
}

void OptionModeBaseLayout::cycle()
{
}

void OptionModeBaseLayout::drawBaseLayout()
{
    // horizontal boarder left (upper one)
    m_tft->fillRect(/*x*/ 0, 25, /*w*/ 105, /*h*/ 3, m_defaultColorFrames);
    // horizontal boarder left (lower one)
    m_tft->fillRect(/*x*/ 0, 40, /*w*/ 105, /*h*/ 3, m_defaultColorFrames);
    //vertival boarder entire screen
    m_tft->fillRect(/*x*/ 105, /*y*/ 0, /*w*/ 4, /*h*/ m_tft->height(), m_defaultColorFrames);

    // TODO(FHk) write information about summer- or wintertime to bottom of left side (when model is available)
}

void OptionModeBaseLayout::printCurrentTimeToScreen(int hour, int minute, int second)
{
    printTimeToScreen(/*x*/ 5, /*y*/ 5, /*textsize*/ 2, hour, minute, second);
}

void OptionModeBaseLayout::printTimeToScreen(int x0, int y0, int textSize, bool showSeconds, int hour, int minute, int second)
{
    m_tft->setTextSize(textSize);
    m_tft->setTextColor(m_defaultColorText);

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