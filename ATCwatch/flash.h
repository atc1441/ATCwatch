
#pragma once

#include "Arduino.h"


void init_flash();
void flash_sleep(int state);
uint16_t flash_read_id();
void get_temp(uint8_t *ptr);
void startWrite_flash(void);
void endWrite_flash(void);
