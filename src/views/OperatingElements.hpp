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

    Button m_backButton;
    Button m_enterButton;
    Button m_upButton;
    Button m_downButton;

    IKeyEventListener *m_keyEventListener;
    IEnergySavingPreventor *m_energySavingPreventor;
};