#include "ViewController.hpp"

#include "AutomaticView.hpp"

ViewController::ViewController()
{
    // TODO(FHk) build model
    m_model = nullptr;

    m_tft = new Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
    m_tft->initR(INITR_BLACKTAB); // You will need to do this in every sketch
    m_tft->setRotation(3);        // rotate screen to use it in "wide mode"

    // TODO(FHk) for a first test we build here a view without a factory or any logic
    m_activeView = new AutomaticView(m_model, m_tft);
}

void ViewController::cycle()
{
    if (m_activeView)
    {
        m_activeView->cycle();
    }
}