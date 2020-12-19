#pragma once

#include "ILightSteering.hpp"
#include "ITimeKeeperListener.hpp"

/**
 * @brief The LightSteering class controls the switching state of an light element. The class
 *        can get registered to the emitter of ITimeKeeperListener:Events. In this implementation
 *        is this the TimeKeeper and fires events for the "Artificial Light Option". A possibility
 *        to wake up the chickens to work earlier in the wintertime.
 *
 */
class LightSteering : public virtual ILightSteering, public virtual ITimeKeeperListener
{
  public:
    LightSteering(int lightPin);
    ~LightSteering() = default;

    // ILightSteering
    void switchLightOn() override;
    void switchLightOff() override;
    bool getLightStatus() const override;

    // ITimeKeeperListener
    void eventTimeKeeperListener(ITimeKeeperListener::Event event) override;

  private:
    const int c_lightPin;
    bool m_lightStatus;
};
