#pragma once

#include <TFT.h>
#include "IWidget.hpp"
#include "../IModel.hpp"

/**
 * @brief The WidgetBase is the base for Widget implementations. It holds
 *        all needed access to Model, the TFT, ... and the default colors.
 */
class WidgetBase : public virtual IWidget
{
public:
    WidgetBase(IModel *model, Adafruit_GFX *tft,
               uint16_t colorBackground,
               uint16_t colorFrames,
               uint16_t colorText,
               int16_t x0, int16_t y0);
    ~WidgetBase() = default;

protected:
    IModel *m_model;
    Adafruit_GFX *m_tft;

    uint16_t const m_defaultColorBackground;
    uint16_t const m_defaultColorFrames;
    uint16_t const m_defaultColorText;

    const int16_t m_x0; // initial position left (from ctor)
    const int16_t m_y0; // initial position top (from cto)

    // add here all method who can be usefull from each widget
};