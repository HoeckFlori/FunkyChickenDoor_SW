#pragma once

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcpp" // doesn't work to suppress the warning '.pio/libdeps/megaatmega2560/TFT_ID886/src/utility/Adafruit_GFX.h:60:3: warning: #warning "The SD library was not found. loadImage() and image() won't be supported." [-Wcpp]'
#include <TFT.h>
#pragma GCC diagnostic pop

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

    void setViewForOpMode(IOperationModeManager::OpMode mode);

private:
    IModel *m_model;
    Adafruit_ST7735 *m_tft;
    IView *m_activeView;
    IOperatingElements *m_operatingElements;
    IOperationModeManager *m_operationModeManager;
    IOperationModeManager::OpMode m_lastKnownOperationMode;

    // //scribling:
    // void requestViewRenewal(); // callback which can get called from the active view in case of OperationMode change, redrawing everything, ...
    // //Achtung, wenn wir die View damit direkt abschießen haben wir ein unbestimmtes verhalten, da sich die view selbst einen Kopfschuß geben würde

    // bool m_requestViewRenewal;
};