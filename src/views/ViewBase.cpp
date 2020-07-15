#include "ViewBase.hpp"
#include "TFT.h"

ViewBase::ViewBase(IModel *model, IOperatingElements *operatingElements, Adafruit_GFX *tft,
                   uint16_t colorBackground,
                   uint16_t colorFrames,
                   uint16_t colorText)
    : m_model(model), m_operatingElements(operatingElements), m_tft(tft),
      m_defaultColorBackground(colorBackground),
      m_defaultColorFrames(colorFrames),
      m_defaultColorText(colorText)
{
  // register the view instance as listener to the model
  m_model->registerModelEventListener(this);

  // register the view instance as listener to the OperatingElements
  m_operatingElements->registerKeyEventListener(this);

  // draw background (once for all)
  m_tft->fillScreen(m_defaultColorBackground);
}

ViewBase::~ViewBase()
{
  // remove the model listener
  m_model->removeModelEventListener();

  // remove the OperatingElements
  m_operatingElements->removeKeyEventListener();
}