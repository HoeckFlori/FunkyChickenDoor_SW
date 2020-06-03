#pragma once

#include <TFT.h>
#include "../ITimeKeeper.hpp"
#include "IViewController.hpp"
#include "IView.hpp"
#include "IModel.hpp"

// TODO(FHk) make this c++ conform!!!
#define TFT_CS 10
#define TFT_RST 9
#define TFT_DC 8

class ViewController : public virtual IViewController
{
public:
    ViewController(ITimeKeeper *timekeeper);
    ~ViewController() = default;

    // IViewController
    void cycle() override;

private:
    IModel *m_model;
    Adafruit_ST7735 *m_tft;
    IView *m_activeView;
};