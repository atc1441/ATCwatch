
#pragma once

#include "Arduino.h"

void init_sleep();
void set_sleep(bool state);
bool get_sleep();
bool sleep_up();
void sleep_down();
void disable_hardware();
void sleep_wait();
void set_sleep_time();
void check_sleep_times();
bool get_timed_int();
long get_timed_int_time();
void set_timed_int_time(long times);
void set_i2cReading(bool state);
bool get_i2cReading();
void initRTC2();
