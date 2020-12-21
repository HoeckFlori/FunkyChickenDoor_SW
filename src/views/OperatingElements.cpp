#include "OperatingElements.hpp"

OperatingElements::OperatingElements(IEnergySavingPreventor *energySavingPreventor)
    : m_backButton(22 /*pin*/, m_defaultDebounceTime, true /* puEnable*/, true /*invert*/)
    , m_enterButton(23 /*pin*/, m_defaultDebounceTime, true /* puEnable*/, true /*invert*/)
    , m_upButton(24 /*pin*/, m_defaultDebounceTime, true /* puEnable*/, true /*invert*/)
    , m_downButton(25 /*pin*/, m_defaultDebounceTime, true /* puEnable*/, true /*invert*/)
    , m_energySavingPreventor(energySavingPreventor)
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
        // Serial.println(F("m_backButton was pressed!"));
        if (m_keyEventListener != nullptr)
        {
            m_keyEventListener->keyEventListener(IKeyEventListener::Event::BUTTON_BACK);
        }
        if (m_energySavingPreventor != nullptr)
        {
            m_energySavingPreventor->userEvent();
        }
    }

    // --- BUTTON_ENTER -------------------------
    m_enterButton.read();
    if (m_enterButton.wasPressed())
    {
        // Serial.println(F("m_enterButton was pressed!"));
        if (m_keyEventListener != nullptr)
        {
            m_keyEventListener->keyEventListener(IKeyEventListener::Event::BUTTON_ENTER);
        }
        if (m_energySavingPreventor != nullptr)
        {
            m_energySavingPreventor->userEvent();
        }
    }

    // --- BUTTON_UP -------------------------
    m_upButton.read();
    if (m_upButton.wasPressed())
    {
        // Serial.println(F("m_upButton was pressed!"));
        if (m_keyEventListener != nullptr)
        {
            m_keyEventListener->keyEventListener(IKeyEventListener::Event::BUTTON_UP);
        }
        if (m_energySavingPreventor != nullptr)
        {
            m_energySavingPreventor->userEvent();
        }
    }

    // --- BUTTON_DOWN -------------------------
    m_downButton.read();
    if (m_downButton.wasPressed())
    {
        // Serial.println(F("m_downButton was pressed!"));
        if (m_keyEventListener != nullptr)
        {
            m_keyEventListener->keyEventListener(IKeyEventListener::Event::BUTTON_DOWN);
        }
        if (m_energySavingPreventor != nullptr)
        {
            m_energySavingPreventor->userEvent();
        }
    }
}

void OperatingElements::registerKeyEventListener(IKeyEventListener *listener)
{
    m_keyEventListener = listener;
}

void OperatingElements::removeKeyEventListener()
{
    // delete m_listener;
    m_keyEventListener = nullptr;
}
