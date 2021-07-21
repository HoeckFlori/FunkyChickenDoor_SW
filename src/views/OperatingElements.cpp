#include "OperatingElements.hpp"

OperatingElements::OperatingElements(IEnergySavingPreventor *energySavingPreventor)
    : m_button1(22 /*pin*/, m_defaultDebounceTime, true /* puEnable*/, true /*invert*/)
    , m_button2(23 /*pin*/, m_defaultDebounceTime, true /* puEnable*/, true /*invert*/)
    , m_button3(24 /*pin*/, m_defaultDebounceTime, true /* puEnable*/, true /*invert*/)
    , m_button4(25 /*pin*/, m_defaultDebounceTime, true /* puEnable*/, true /*invert*/)
    , m_keyEventListener(nullptr)
    , m_energySavingPreventor(energySavingPreventor)
{
    m_button1.begin();
    m_button2.begin();
    m_button3.begin();
    m_button4.begin();
}

void OperatingElements::cycle()
{
    // --- BUTTON_1 -------------------------
    m_button1.read();
    if (m_button1.wasPressed())
    {
        // Serial.println(F("m_button1 was pressed!"));
        if (m_keyEventListener != nullptr)
        {
            m_keyEventListener->keyEventListener(IKeyEventListener::Event::BUTTON_1);
        }
        if (m_energySavingPreventor != nullptr)
        {
            m_energySavingPreventor->userEvent();
        }
    }

    // --- BUTTON_2 -------------------------
    m_button2.read();
    if (m_button2.wasPressed())
    {
        // Serial.println(F("m_button2 was pressed!"));
        if (m_keyEventListener != nullptr)
        {
            m_keyEventListener->keyEventListener(IKeyEventListener::Event::BUTTON_2);
        }
        if (m_energySavingPreventor != nullptr)
        {
            m_energySavingPreventor->userEvent();
        }
    }

    // --- BUTTON_3 -------------------------
    m_button3.read();
    if (m_button3.wasPressed())
    {
        // Serial.println(F("m_button3 was pressed!"));
        if (m_keyEventListener != nullptr)
        {
            m_keyEventListener->keyEventListener(IKeyEventListener::Event::BUTTON_3);
        }
        if (m_energySavingPreventor != nullptr)
        {
            m_energySavingPreventor->userEvent();
        }
    }

    // --- BUTTON_4 -------------------------
    m_button4.read();
    if (m_button4.wasPressed())
    {
        // Serial.println(F("m_button4 was pressed!"));
        if (m_keyEventListener != nullptr)
        {
            m_keyEventListener->keyEventListener(IKeyEventListener::Event::BUTTON_4);
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
