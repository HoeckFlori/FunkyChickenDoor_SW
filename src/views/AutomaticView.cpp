#include "AutomaticView.hpp"

AutomaticView::AutomaticView(IModel *model, Adafruit_GFX *tft)
    : OptionModeBaseLayout::OptionModeBaseLayout(model, tft,
                                                 ST7735_BLACK /*background color*/,
                                                 ST7735_RED /*color of frames*/,
                                                 ST7735_WHITE /*text color*/)
{

    m_tft->setTextSize(1);

    m_tft->setTextColor(ST7735_GREEN); // change default text color
    m_tft->setCursor(25, 31);
    m_tft->print(F("AUTOMATIC"));
    m_tft->setTextColor(m_defaultColorText); // switch text color bach to default

    m_tft->setCursor(5, 50);
    m_tft->print(F("Sunrise:"));
    m_tft->setCursor(5, 65);
    m_tft->print(F("Sunset:"));

    // testing only
    printCurrentTimeToScreen(9, 8, 7);
    printSunriseToScreen(5, 30);
    printSunsetToScreen(20, 45);
}

void AutomaticView::cycle()
{
    // call parent method
    OptionModeBaseLayout::cycle();
}

void AutomaticView::printSunriseToScreen(int hour, int minute)
{
    printTimeToScreen(/*x*/ 65, /*y*/ 50, /*textsize*/ 1, /*showSeconds*/ false, hour, minute);
}

void AutomaticView::printSunsetToScreen(int hour, int minute)
{
    printTimeToScreen(/*x*/ 65, /*y*/ 65, /*textsize*/ 1, /*showSeconds*/ false, hour, minute);
}