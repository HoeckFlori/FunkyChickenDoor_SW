#include "ViewController.hpp"
#include "AutomaticView.hpp"
#include "ManualView.hpp"
#include "Model.hpp"
#include "OperatingElements.hpp"

ViewController::ViewController(IOperationModeManager *operationModeManager, ITimeKeeper *timekeeper, IDoorSteering *doorSteering)
    : m_activeView(nullptr),
      m_operationModeManager(operationModeManager) /*,
      m_lastKnownOperationMode(IOperationModeManager::OpMode::UNDEFINED) */
{
    m_lastKnownOperationMode = m_operationModeManager->getMode();

    m_model = new Model(timekeeper, doorSteering, m_operationModeManager);

    m_tft = new Adafruit_ST7735(10 /* CS (chip selector pin) */,
                                8 /* A0  (TFT SPI data or command selector pin) */,
                                9 /* RST (Reset pin)*/);
    m_tft->initR(INITR_BLACKTAB); // Init ST7735S chip, black tab (You will need to do this in every sketch)
    m_tft->setRotation(3);        // rotate screen to use it in "wide mode"

    m_operatingElements = new OperatingElements();

    // set initial view
    setViewForOpMode(m_lastKnownOperationMode);
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
        setViewForOpMode(m_lastKnownOperationMode);
    }
    // cycle the view itself
    if (m_activeView != nullptr)
    {
        m_activeView->cycle();
    }
}

void ViewController::setViewForOpMode(IOperationModeManager::OpMode mode)
{
    switch (mode)
    {
    case IOperationModeManager::OpMode::AUTOMATIC:
        delete m_activeView;
        m_activeView = nullptr;
        m_activeView = new AutomaticView(m_model, m_operatingElements, m_tft);
        break;
    case IOperationModeManager::OpMode::MANUAL:
        delete m_activeView;
        m_activeView = nullptr;
        m_activeView = new ManualView(m_model, m_operatingElements, m_tft);
        break;
    default:
        Serial.print("ERROR: No view available for requested OpMode");
    }
}