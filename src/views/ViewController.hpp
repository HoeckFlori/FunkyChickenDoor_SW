#pragma once

#include <TFT.h>
#include "../ITimeKeeper.hpp"
#include "../IDoorSteering.hpp"
#include "IViewController.hpp"
#include "IView.hpp"
#include "IModel.hpp"
#include "IOperatingElements.hpp"

class ViewController : public virtual IViewController
{
public:
    ViewController(ITimeKeeper *timekeeper, IDoorSteering *doorSteering);
    ~ViewController() = default;

    // IViewController
    void cycle() override;

private:
    IModel *m_model;
    Adafruit_ST7735 *m_tft;
    IView *m_activeView;
    IOperatingElements *m_operatingElements;
};