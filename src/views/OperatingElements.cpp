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
    // --- BUTTON_BACK -------------------------
    m_backButton.read();
    if (m_backButton.wasPressed())
    {
        Serial.println(F("m_backButton was pressed!"));
        if (m_listener)
        {
            m_listener->keyEventListener(IKeyEventListener::Event::BUTTON_BACK);
        }
    }

    // --- BUTTON_ENTER -------------------------
    m_enterButton.read();
    if (m_enterButton.wasPressed())
    {
        Serial.println(F("m_enterButton was pressed!"));
        if (m_listener)
        {
            m_listener->keyEventListener(IKeyEventListener::Event::BUTTON_ENTER);
        }
    }

    // --- BUTTON_UP -------------------------
    m_upButton.read();
    if (m_upButton.wasPressed())
    {
        Serial.println(F("m_upButton was pressed!"));
        if (m_listener)
        {
            m_listener->keyEventListener(IKeyEventListener::Event::BUTTON_UP);
        }
    }

    // --- BUTTON_DOWN -------------------------
    m_downButton.read();
    if (m_downButton.wasPressed())
    {
        Serial.println(F("m_downButton was pressed!"));
        if (m_listener)
        {
            m_listener->keyEventListener(IKeyEventListener::Event::BUTTON_DOWN);
        }
    }
}

void OperatingElements::registerKeyEventListener(IKeyEventListener *listener)
{
    m_listener = listener;
}
void OperatingElements::removeKeyEventListener()
{
    m_listener = nullptr;
}