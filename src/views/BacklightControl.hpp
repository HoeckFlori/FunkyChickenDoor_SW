#pragma once

#include <stdint.h>
#include "../IEnergySavingMaster.hpp"

class BacklightControl : public virtual IEnergySavingClient
{
    public:
        BacklightControl(int outputPin);
        virtual ~BacklightControl() = default;

        void setDefaultIlluminance(uint8_t percent);
        void setDimmedIlluminance(uint8_t percent);
        
        void activateDefaultIlluminance();
        void activateDimmedIlluminance();
        void deactivateBacklight();

        // IEnergySavingClient
        void updateAboutSystemPowerState(SystemPowerStates newState) override;

    private:
        const int c_tftDimmingControlPin;
        uint8_t m_defaultIlluminance;
        uint8_t m_dimmedIlluminance;
};