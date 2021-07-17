#pragma once
#include "../WidgetBase.hpp"
#include "ButtonBase.hpp"

// forward declaration
class Adafruit_GFX;

class ButtonEmergencyOff : public ButtonBase, public WidgetBase
{
  public:
    ButtonEmergencyOff(IModel *model, Adafruit_GFX *tft, uint16_t colorBackground, uint16_t colorFrames, uint16_t colorText, int16_t x0, int16_t y0,
                       int16_t ButtonSizeX, int16_t ButtonSizeY);
    ~ButtonEmergencyOff() = default;

    // IWidget
    void setup() override;
    int16_t getWidthOfWidget() override;
    int16_t getHeightOfWidget() override;
    void cycle() override;
    void passModelEventToWidget(IModelEventListener::Event event) override;

  private:
    void drawActive();
    void drawInActive();
    void doorStateHandling();
};
