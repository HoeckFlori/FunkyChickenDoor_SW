#pragma once

#include <TFT.h>
#include "../ITimeKeeper.hpp"
#include "../IDoorSteering.hpp"
#include "IViewController.hpp"
#include "IView.hpp"
#include "IModel.hpp"
#include "IOperatingElements.hpp"
#include "IOperationModeManager.hpp"

class ViewController : public virtual IViewController
{
public:
    ViewController(IOperationModeManager *operationModeManager, ITimeKeeper *timekeeper, IDoorSteering *doorSteering);
    ~ViewController() = default;

    // IViewController
    void cycle() override;

private:
    IModel *m_model;
    Adafruit_ST7735 *m_tft;
    IView *m_activeView;
    IOperatingElements *m_operatingElements;
    IOperationModeManager *m_operationModeManager;
    IOperationModeManager::OpMode m_lastKnownOperationMode;
};