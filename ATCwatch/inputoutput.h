/*
 * Copyright (c) 2020 Aaron Christophel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include "Arduino.h"

void init_inputoutput();
bool get_button();
void set_led(bool state);
void set_motor(bool state);
void set_motor_ms(int ms);
void set_motor_ms();
void set_motor_power(int ms);
int get_motor_power();
void set_led_ms(int ms);
void check_inputoutput_times();
