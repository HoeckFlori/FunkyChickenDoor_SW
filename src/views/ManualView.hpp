#pragma once

#include "OptionModeBaseLayout.hpp"

/**
 * @brief The View in which the 'Manual Mode' is visualized
 *        (The mode in which the user opens ans closes the door manually)
  */
class ManualView : public OptionModeBaseLayout
{
public:
    explicit ManualView(IModel *model, Adafruit_GFX *tft);
    ~ManualView();

    // IView
    void cycle() override;

    // IModelViewListener
    void modelListener(IModelEventListener::Event event) override;

private:
    void drawBaseLayout() override;
};