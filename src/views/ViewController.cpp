#include "ViewController.hpp"
#include "AutomaticView.hpp"
#include "ManualView.hpp"
#include "Model.hpp"
#include "OperatingElements.hpp"

ViewController::ViewController(ITimeKeeper *timekeeper, IDoorSteering *doorSteering)
{
    m_model = new Model(timekeeper, doorSteering);

    // with default hardware spi
    m_tft = new Adafruit_ST7735(10 /* CS (chip selector pin) */,
                                8 /* A0  (TFT SPI data or command selector pin) */,
                                9 /* RST (Reset pin)*/);
    m_tft->initR(INITR_BLACKTAB); // Init ST7735S chip, black tab (You will need to do this in every sketch)
    m_tft->setRotation(3);        // rotate screen to use it in "wide mode"

    m_operatingElements = new OperatingElements();

    // TODO(FHk) for a first test we build here a view without a factory or any logic
    m_activeView = new AutomaticView(m_model, m_tft);
    // m_activeView = new ManualView(m_model, m_tft);
}

void ViewController::cycle()
{
    // TODO(FHk) kick out this existing checks, put everything in a single check in the constructor. Where should they go when they where created?

    if (m_model)
    {
        m_model->cycle();
    }
    if (m_activeView)
    {
        m_activeView->cycle();
    }
    if (m_operatingElements)
    {
        m_operatingElements->cycle();
    }
}