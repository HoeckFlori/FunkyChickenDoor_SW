#pragma once

#include "../IEnergySavingMaster.hpp"
#include "IOperatingElements.hpp"
#include <JC_Button.h>

class OperatingElements : public virtual IOperatingElements
{
  public:
    explicit OperatingElements(IEnergySavingPreventor *energySavingPreventor);
    ~OperatingElements() = default;

    // IOperatingElements
    void cycle() override;
    void registerKeyEventListener(IKeyEventListener *listener) override;
    void removeKeyEventListener() override;

  private:
    const int m_defaultDebounceTime = 40; // ms

    // buttons, below the display, numbered from left to right
    Button m_button1;
    Button m_button2;
    Button m_button3;
    Button m_button4;

    IKeyEventListener *m_keyEventListener;
    IEnergySavingPreventor *m_energySavingPreventor;
};