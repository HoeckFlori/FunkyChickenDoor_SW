#pragma once

class ILightSteering
{
  public:
    virtual ~ILightSteering() = default;

    /**
     * @brief Switch the light ON
     *
     */
    virtual void switchLightOn() = 0;

    /**
     * @brief Switch the ligh OFF
     *
     */
    virtual void switchLightOff() = 0;

    /**
     * @brief Query the switching status of the light
     *
     * @return true  Light is ON
     * @return false Light is OFF
     */
    virtual bool getLightStatus() const = 0;
};
