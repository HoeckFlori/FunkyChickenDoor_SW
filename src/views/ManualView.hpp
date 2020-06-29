#pragma once

#include "OptionModeBaseLayout.hpp"

/**
 * @brief The View in which the 'Manual Mode' is visualized
 *        (The mode in which the user opens ans closes the door manually)
  */
class ManualView : public OptionModeBaseLayout
{
public:
    explicit ManualView(IModel *model, IOperatingElements *operatingElements, Adafruit_GFX *tft);
    virtual ~ManualView() = default;

    // IView
    void cycle() override;

    // IModelViewListener
    void modelListener(IModelEventListener::Event event) override;

    // IKeyEventListener
    void keyEventListener(IKeyEventListener::Event event) override;

private:
    void drawBaseLayout() override;
};