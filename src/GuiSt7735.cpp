#include <Arduino.h>
#include "GuiSt7735.hpp"

GuiSt7735::GuiSt7735()
{
    // Serial.begin(115200);
    // Serial.println(F("GuiSt7735"));
    m_tft.initR(INITR_BLACKTAB); // You will need to do this in every sketch
    m_tft.fillScreen(ST7735_BLACK);

    m_tft.setRotation(3); // rotate screen to use it in "wide mode"

    //m_tft print function!

    // m_tft.setTextColor(ST7735_BLUE);
    // m_tft.setTextSize(3);
    // m_tft.setCursor(0, 55);
    // m_tft.println(F("Vincent"));

    m_tft.setTextColor(ST7735_WHITE);
    m_tft.setTextSize(0);
    m_tft.setCursor(0, 80);
    m_tft.println(F("Lets start the project of the amazing funky chicken door!"));
    //m_tft.println("Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.");
    // m_tft.drawLine(10, 10, 118, 10, ST7735_CYAN);
    // m_tft.drawFastHLine(0, 20, 128, ST7735_GREEN);
    // m_tft.drawCircle(64, 40, 10, ST7735_CYAN);
    //    delay(1000);
    //    Serial.println("setup() - end");
}

void GuiSt7735::turnOnDisplay()
{
}

void GuiSt7735::turnOffDisplay()
{
}

void GuiSt7735::showScreen(int screen)
{
}

void GuiSt7735::writeNumber(int number)
{
    m_tft.setCursor(0, 80);
    m_tft.fillRect(0, 80, m_tft.width(), 30, ST7735_BLUE);

    m_tft.setCursor(0, 80);
    m_tft.setTextColor(ST7735_WHITE);
    m_tft.setTextSize(4);
    m_tft.println(number);
}

void GuiSt7735::writeTime(int hour, int minute, int second)
{
    auto xOffset = (m_tft.width() - getXSizeOfTime(/*text size*/ 3)) / 4;

    const int yOffsetRectangle(3);
    m_tft.fillRect(0, 0, m_tft.width(), (2 * yOffsetRectangle + getYSizeOfTime(/*text size*/ 3) - 1), ST7735_BLUE);

    printTimeToScreen(xOffset, yOffsetRectangle, /*text size*/ 3, hour, minute, second);
}

void GuiSt7735::printTimeToScreen(int x0, int y0, int textSize, int hour, int minute, int second, uint16_t color = ST7735_WHITE)
{
    m_tft.setTextSize(textSize);
    m_tft.setTextColor(color);

    // print the hour
    m_tft.setCursor(x0, y0);
    if (hour < 10)
        m_tft.print(F("0"));
    m_tft.print(hour);

    // print the minute
    m_tft.print(F(":"));
    if (minute < 10)
        m_tft.print(F("0"));
    m_tft.print(minute);

    // print the second
    m_tft.print(F(":"));
    if (second < 10)
        m_tft.print(F("0"));
    m_tft.print(second);
}

int GuiSt7735::getXSizeOfTime(int textSize)
{
    const int usedCharacters(8); // format hh:mm:ss
    return 8 /*characters*/ * 5 /*base size x per character*/ * textSize;
}

int GuiSt7735::getYSizeOfTime(int textSize)
{
    return 8 /*base size character y direction*/ * textSize;
}