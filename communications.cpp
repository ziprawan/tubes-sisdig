#include "communications.h"

void init_comm()
{
  SPI.begin();
}

void send_data(uint16_t data)
{
  latchOff();
  SPI.transfer16(data);
  latchOn();
}

void clear_data()
{
  send_data(0);
}
