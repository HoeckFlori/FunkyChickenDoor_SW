#include "ViewController.hpp"
#include "AutomaticView.hpp"
#include "ManualView.hpp"
#include "Model.hpp"
#include "OperatingElements.hpp"

ViewController::ViewController(IOperationModeManager *operationModeManager, ITimeKeeper *timekeeper, IDoorSteering *doorSteering)
    : m_operationModeManager(operationModeManager),
      m_lastKnownOperationMode(IOperationModeManager::OpMode::UNDEFINED)
{
    m_model = new Model(timekeeper, doorSteering);

    m_tft = new Adafruit_ST7735(10 /* CS (chip selector pin) */,
                                8 /* A0  (TFT SPI data or command selector pin) */,
                                9 /* RST (Reset pin)*/);
    m_tft->initR(INITR_BLACKTAB); // Init ST7735S chip, black tab (You will need to do this in every sketch)
    m_tft->setRotation(3);        // rotate screen to use it in "wide mode"

    m_operatingElements = new OperatingElements();
}

void ViewController::cycle()
{
    // --- cycle the view depending components
    m_model->cycle();
    m_operatingElements->cycle();

    // --- view controlling
    // check mode change
    if (m_lastKnownOperationMode != m_operationModeManager->getMode())
    { // mode must have changed or it is a system start
        m_lastKnownOperationMode = m_operationModeManager->getMode();
        switch (m_lastKnownOperationMode)
        {
        case IOperationModeManager::OpMode::UNDEFINED:
            m_activeView = nullptr;
            break;
        case IOperationModeManager::OpMode::AUTOMATIC:
            m_activeView = new AutomaticView(m_model, m_tft);
            break;
        case IOperationModeManager::OpMode::MANUAL:
            m_activeView = new ManualView(m_model, m_tft);
            break;
        }
    }
    // cycle the view itself
    if (m_activeView)
    {
        m_activeView->cycle();
    }
}