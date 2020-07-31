/*
 * Copyright (c) 2020 Aaron Christophel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include "Arduino.h"
#include "touch.h"
#include "class_def.h"
#include <lvgl.h>

void init_menu();
void display_home();
void display_notify();
void display_charging();
void display_booting();
void display_screen(bool ignoreWait = false);
void check_button_push(int length);
void check_menu(touch_data_struct touch_data);
uint32_t get_menu_delay_time();
int get_sleep_time_menu();
void change_screen(Screen_def* screen);
void set_last_menu();
void set_swipe_enabled(bool state);
bool swipe_enabled();
void inc_vars_menu();
void dec_vars_menu();
static void lv_event_handler(lv_obj_t * object, lv_event_t event);
