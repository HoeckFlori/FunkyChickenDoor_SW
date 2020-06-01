#pragma once

#include <TFT.h>
#include "IView.hpp"
#include "IModel.hpp"

/**
 * @brief The ViewBase is the base for all implemented and to implemented views.
 *        It holds all needed access to Model, the TFT, ... (whatever is comming)
 *        and the default color settings.
 */
class ViewBase : public virtual IView
{
public:
    ViewBase(IModel *model, Adafruit_GFX *tft,
             uint16_t colorBackground,
             uint16_t colorFrames,
             uint16_t colorText);
    virtual ~ViewBase() = default;

protected:
    IModel *m_model;
    Adafruit_GFX *m_tft;

    uint16_t const m_defaultColorBackground;
    uint16_t const m_defaultColorFrames;
    uint16_t const m_defaultColorText;

    // add here all method who can be usefull from each view
    // ...
};