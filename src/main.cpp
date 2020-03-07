#include <Arduino.h>
#include "TheBase.hpp"

TheBase m_TheBase = TheBase();

void setup(void) {
  m_TheBase.setup();
}
void loop() {
  m_TheBase.loop();
}
