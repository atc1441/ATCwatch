/*
 * Copyright (c) 2020 Aaron Christophel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include "Arduino.h"

void init_bootloader();
void start_bootloader(bool without_sd=false);
void set_reboot();
bool get_sd_enabled();
void system_off();
