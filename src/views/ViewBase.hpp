#pragma once

#include "IView.hpp"
#include "IModel.hpp"
#include "IOperatingElements.hpp"

// forward declaration
class Adafruit_GFX;

/**
 * @brief The ViewBase is the base for all implemented and to implemented views.
 *        It holds all needed access to Model and the relevant listener, the TFT,
 *        ... (whatever is comming) and the default color settings.
 */
class ViewBase : public virtual IView,
                 public virtual IModelEventListener,
                 public virtual IKeyEventListener
{
public:
    ViewBase(IModel *model, IOperatingElements *operatingElements, Adafruit_GFX *tft,
             uint16_t colorBackground,
             uint16_t colorFrames,
             uint16_t colorText);
    virtual ~ViewBase();

protected:
    IModel *m_model;
    IOperatingElements *m_operatingElements;
    Adafruit_GFX *m_tft;

    uint16_t const m_defaultColorBackground;
    uint16_t const m_defaultColorFrames;
    uint16_t const m_defaultColorText;

    // add here all method who can be usefull from each view

    /**
     * @brief Draw all needed frames, ...
     */
    virtual void drawBaseLayout() = 0; // TODO(FHk) !!!! We will need a event to redraw a entire view is something changed like "Wintertime->SummerTime" or Position has changed, which affects Sunrise/Sunset, .... May not here ...
};