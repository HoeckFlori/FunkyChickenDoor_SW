#pragma once

#include "IGui.hpp"

// #include <SPI.h>
// #include <SD.h>
// #include <SdFat.h>
// #include <Adafruit_ImageReader.h>
// #include <Adafruit_SPIFlash.h>
// #include <Adafruit_ST7735.h>
#include <TFT.h>

// TODO(FHk) make this c++ conform!!!
#define TFT_CS 10
#define TFT_RST 9
#define TFT_DC 8

// !!!! We do not need this class anymore -> Kick it out, when you took over all already implemented stuff!

class GuiSt7735 : public virtual IGui
{
public:
    GuiSt7735();
    virtual ~GuiSt7735() = default;

    void turnOnDisplay() override;
    void turnOffDisplay() override;
    void showScreen(int screen) override;
    void writeNumber(int number) override;
    void writeTime(int hour, int minute, int second) override;

private:
    Adafruit_ST7735 m_tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

    /**
     * @brief Write time in format hh::mm::ss to screen
     * 
     * @param x0 Initial position left
     * @param y0 Initial position up
     * @param textSize Text size can be 1-3. Basic size is 5x8. Each size is multiplied by it.
     * @param hour Hour 0-24
     * @param minute 0-59
     * @param second 0-59
     * @param color Text color default ST7735_WHITE
     */
    void printTimeToScreen(int x0, int y0, int textSize, int hour, int minute, int second, uint16_t color = ST7735_WHITE);

    /**
     * @brief Returns the needed space in x direction of the printed time (format hh::mm::ss) according a text size
     * 
     * @param textSize The used text size (1-3)
     * @return int The needed space in X direction in pixel 
     */
    int getXSizeOfTime(int textSize);

    /**
     * @brief Returns the needed space in y direction of the printed time (format hh::mm::ss) according a text size
     * 
     * @param textSize The used text size (1-3)
     * @return int The needed space in Y direction in pixel 
     */
    int getYSizeOfTime(int textSize);
};