
#pragma once

#include "Arduino.h"
#include "pinout.h"

#define ST77XX_SLPIN 0x10
#define ST77XX_SLPOUT 0x11
#define ST77XX_DISPOFF 0x28
#define ST77XX_DISPON 0x29

void init_display();
void display_enable(bool state);
void inc_tick();

void setAddrWindowDisplay(uint32_t x, uint32_t y, uint32_t w, uint32_t h);
void initDisplay();
void spiCommand(uint8_t d);
void startWrite_display(void);
void endWrite_display(void);
