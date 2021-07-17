#pragma once
#include <stdint.h>

// forward declaration
class Adafruit_GFX;

class ButtonBase
{
  public:
    ButtonBase(Adafruit_GFX *tft, uint16_t colorBackground, int16_t x0, int16_t y0, int16_t ButtonSizeX, int16_t ButtonSizeY);
    ~ButtonBase() = default;

  protected:
    int16_t m_buttonSizeX;
    int16_t m_buttonSizeY;

    void clearButtonArea();

  private:
    Adafruit_GFX *m_tft_Base;
    uint16_t m_defaultColorBackground_Base;
    int16_t m_x0_Base;
    int16_t m_y0_Base;
};
