#include "ViewController.hpp"
#include "AutomaticView.hpp"
#include "ManualView.hpp"
#include "Model.hpp"

ViewController::ViewController(ITimeKeeper *timekeeper)
{
    // TODO(FHk) build model
    m_model = new Model(timekeeper);

    m_tft = new Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
    m_tft->initR(INITR_BLACKTAB); // You will need to do this in every sketch
    m_tft->setRotation(3);        // rotate screen to use it in "wide mode"

    // TODO(FHk) for a first test we build here a view without a factory or any logic
    // m_activeView = new AutomaticView(m_model, m_tft);
    m_activeView = new ManualView(m_model, m_tft);
}

void ViewController::cycle()
{
    if (m_model)
    {
        m_model->cycle();
    }
    if (m_activeView)
    {
        m_activeView->cycle();
    }
}