#include <Arduino.h>
#include "MainControl.hpp"
#include "GuiSt7735.hpp"
#include "Timekeeper.hpp"
#include "ConsoleAgent.hpp"
#include "DataStorage.hpp"

MainControl::MainControl()
    : m_counter(0)
{
    // !!! Do not place initialization of anything in here. It doesn't work, I don't know why. FHk
}

void MainControl::init()
{
    Serial.begin(115200, SERIAL_8N1);

    // init participants
    m_dataStorage = new DataStorage();
    m_gui = new GuiSt7735();
    m_timeKeeper = new Timekeeper(m_dataStorage);
    m_consoleAgent = new ConsoleAgent(m_timeKeeper, m_dataStorage);

    //    delay(1000);
    //    Serial.println("Building MainControl");
    // m_st7735 = GuiSt7735();
    // m_st7735.showScreen(1);
    // Serial.println("hallo");
}

void MainControl::cycle()
{
    // kick all cycles of the components
    m_consoleAgent->cycle();

    // // counter example
    // Serial.print(F(" call: "));
    // Serial.print(m_counter);
    // Serial.print("\n");
    // m_gui->writeNumber(m_counter);
    // m_counter++;

    // timer example
    //m_gui->writeTime(9, 8, 7);
    // auto time = m_timeKeeper->getCurrentTime();
    // m_gui->writeTime(time.hour(), time.minute(), time.second());
    // String buffer2("DD.MM.YYYY, hh:mm:ss");
    // Serial.println(time.toString(buffer2.begin()));

    // delay(1000);
}