/*
 * Copyright (c) 2020 Aaron Christophel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include "Arduino.h"

void init_interrupt();
void gets_interrupt_flag();
void set_charged_interrupt();
void set_charge_interrupt();
void set_button_interrupt();
void set_touch_interrupt();
void set_accl_interrupt();
void interrupt_charged();
void interrupt_charge();
void interrupt_button();
void interrupt_touch();
void interrupt_accl();
void disable_interrupt();
