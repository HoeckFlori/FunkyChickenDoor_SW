#pragma once

class ISleepingGuard
{
  public:
    virtual ~ISleepingGuard() = default;

    enum class WakeupReason
    {
        Undefined,
        Timer,
        UserInteraction,
        CriticalPowerSupplyLevel
    };

    virtual void enterSleepMode(int reawakenInMsSeconds) = 0;
    virtual WakeupReason getLastWakeupReason() = 0;
};