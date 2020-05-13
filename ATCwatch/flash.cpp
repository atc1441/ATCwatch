
#include "flash.h"
#include "pinout.h"

void init_flash() {
  pinMode(SPI_CE,OUTPUT);
  digitalWrite(SPI_CE,HIGH);
}
