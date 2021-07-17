#pragma once
#include "../WidgetBase.hpp"
#include <TFT.h>

class ButtonModeChange : public WidgetBase
{
  public:
    ButtonModeChange(IModel *model, Adafruit_GFX *tft, uint16_t colorBackground, uint16_t colorFrames, uint16_t colorText, int16_t x0, int16_t y0,
                     int16_t ButtonSizeX, int16_t ButtonSizeY);
    ~ButtonModeChange() = default;

    void setup() override;
    int16_t getWidthOfWidget() override;
    int16_t getHeightOfWidget() override;
    void cycle() override;
    void passModelEventToWidget(IModelEventListener::Event event) override;

  private:
    int16_t m_buttonSizeX;
    int16_t m_buttonSizeY;

    void clearButtonArea();
    void drawText();
};
