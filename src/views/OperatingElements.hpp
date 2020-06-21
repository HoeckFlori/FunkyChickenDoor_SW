#pragma once

#include <JC_Button.h>
#include "IOperatingElements.hpp"

class OperatingElements : public virtual IOperatingElements
{
public:
    OperatingElements();
    ~OperatingElements() = default;

    void cycle() override;
    void registerKeyEventListener(IKeyEventListener *listener) override;
    void removeKeyEventListener() override;

private:
    const int m_defaultDebounceTime = 40; // ms

    Button m_backButton;
    Button m_enterButton;
    Button m_upButton;
    Button m_downButton;

    IKeyEventListener *m_listener;
};