
#pragma once
#include "Arduino.h"

void displayIconAndText(uint32_t x,uint32_t y,uint32_t w,uint32_t h,String text,const uint16_t *buff);
void menuAppsBase(uint32_t page);
int check_app_click(uint32_t x,uint32_t y);
