/*
 * Copyright (c) 2020 Aaron Christophel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include "Arduino.h"

#define WAKEUP_BLEPUSH 1
#define WAKEUP_BLECONNECTED 2
#define WAKEUP_BLEDISCONNECTED 3
#define WAKEUP_CHARGED 4
#define WAKEUP_CHARGE 5
#define WAKEUP_BUTTON 6
#define WAKEUP_TOUCH 7
#define WAKEUP_ACCL 8
#define WAKEUP_ACCL_INT 9
#define WAKEUP_BLEHTTP 10

void init_sleep();
void set_sleep(bool state);
bool get_sleep();
bool sleep_up(int reason = 0);
void sleep_down();
int get_wakeup_reason();
void disable_hardware();
void sleep_wait();
void set_sleep_time();
void check_sleep_times();
bool get_timed_int();
long get_timed_int_time();
void set_timed_int_time(long times);
void initRTC2();
