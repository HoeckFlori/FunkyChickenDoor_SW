#ifndef THEBASE_HPP
#define THEBASE_HPP

#include <Arduino.h>
//#include <memory>

#include <TFT.h>
#include <SPI.h>

//#include "MotorController.hpp"


#define TFT_CS     10
#define TFT_RST    9  
#define TFT_DC     8

#define TFT_SCLK 13   
#define TFT_MOSI 11  

class TheBase
{

public:
    TheBase() = default;
    ~TheBase() = default;

    void setup()
    {
        Serial.begin(115200);
        Serial.println("setup() - start");
        tft.initR(INITR_BLACKTAB);  // You will need to do this in every sketch
        tft.fillScreen(ST7735_BLACK); 

        //tft print function!
        tft.setTextColor(ST7735_WHITE);
        tft.setTextSize(0);
        tft.setCursor(0,80);
        tft.println("Print something to the screen!");
        //tft.println("Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.");
        tft.drawLine(10, 10, 118, 10, ST7735_CYAN);
        tft.drawFastHLine(0,20, 128, ST7735_GREEN);
        tft.drawCircle(64, 40, 10, ST7735_CYAN);
        delay(1000);
        Serial.println("setup() - end");
    }

    void loop()
    {
          // tft.invertDisplay(true);
  // delay(500);
  // tft.invertDisplay(false);
  // delay(500);
  // m_motor.loop();
    }

private:
    Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);
    
};


#endif // THEBASE_HPP