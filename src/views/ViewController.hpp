#pragma once

#include "../ITimeKeeper.hpp"
#include "../IDoorSteering.hpp"
#include "IViewController.hpp"
#include "IView.hpp"
#include "IModel.hpp"
#include "IOperatingElements.hpp"
#include "IOperationModeManager.hpp"
#include "BacklightControl.hpp"
#include "../IEnergySavingMaster.hpp"
#include "../ILightSteering.hpp"

// foward declaration
class Adafruit_ST7735;

class ViewController : public virtual IViewController
{
public:
    ViewController(IOperationModeManager *operationModeManager, ITimeKeeper *timekeeper, IDoorSteering *doorSteering, IEnergySavingMaster *energySavingMaster, ILightSteering *lightSteering);
    ~ViewController() = default;

    // IViewController
    void cycle() override;

    void setViewForOpMode(IOperationModeManager::OpMode mode);

private:
    IModel *m_model;
    Adafruit_ST7735 *m_tft;
    BacklightControl *m_backlightControl;

    IView *m_activeView;
    IOperatingElements *m_operatingElements;
    IOperationModeManager *m_operationModeManager;
    IOperationModeManager::OpMode m_lastKnownOperationMode;
};