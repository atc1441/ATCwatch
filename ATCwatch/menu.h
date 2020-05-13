
#pragma once

#include "Arduino.h"
#include "touch.h"
#include "class.h"

void init_menu();
void display_home();
void display_error();
void display_notify();
void display_booting();
void display_screen(bool ignoreWait=false);
void check_menu();
uint32_t get_menu_delay_time();
int get_sleep_time_menu();
void change_screen(Screen* screen);
void set_last_menu();
void inc_vars_menu();
void dec_vars_menu();
