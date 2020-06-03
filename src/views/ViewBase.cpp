#include "ViewBase.hpp"

ViewBase::ViewBase(IModel *model, Adafruit_GFX *tft,
                   uint16_t colorBackground,
                   uint16_t colorFrames,
                   uint16_t colorText)
    : m_model(model), m_tft(tft),
      m_defaultColorBackground(colorBackground),
      m_defaultColorFrames(colorFrames),
      m_defaultColorText(colorText)
{
  // register the view instance als listener to the model
  m_model->registerModelEventListener(this);

  // draw background (once for all)
  m_tft->fillScreen(m_defaultColorBackground);
}

ViewBase::~ViewBase()
{
  // remove the model listener
  m_model->removeModelEventListener();
}