#include "OperatingElements.hpp"

OperatingElements::OperatingElements()
    : m_backButton(22 /*pin*/, m_defaultDebounceTime, true /* puEnable*/, true /*invert*/),
      m_enterButton(24 /*pin*/, m_defaultDebounceTime, true /* puEnable*/, true /*invert*/),
      m_upButton(26 /*pin*/, m_defaultDebounceTime, true /* puEnable*/, true /*invert*/),
      m_downButton(28 /*pin*/, m_defaultDebounceTime, true /* puEnable*/, true /*invert*/)
{
    m_backButton.begin();
    m_enterButton.begin();
    m_upButton.begin();
    m_downButton.begin();
}

void OperatingElements::cycle()
{
    m_backButton.read();
    m_enterButton.read();
    m_upButton.read();
    m_downButton.read();

    // ----------------------------
    if (m_backButton.wasPressed())
    {
        Serial.println(F("m_backButton was pressed!"));
    }
    if (m_backButton.wasReleased())
    {
        Serial.println(F("m_backButton was released!"));
    }

    // ----------------------------
    if (m_enterButton.wasPressed())
    {
        Serial.println(F("m_enterButton was pressed!"));
    }
    if (m_enterButton.wasReleased())
    {
        Serial.println(F("m_enterButton was released!"));
    }

    // ----------------------------
    if (m_upButton.wasPressed())
    {
        Serial.println(F("m_upButton was pressed!"));
    }
    if (m_upButton.wasReleased())
    {
        Serial.println(F("m_upButton was released!"));
    }

    // ----------------------------
    if (m_downButton.wasPressed())
    {
        Serial.println(F("m_downButton was pressed!"));
    }
    if (m_downButton.wasReleased())
    {
        Serial.println(F("m_downButton was released!"));
    }
}