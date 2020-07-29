/*
 * Copyright (c) 2020 Aaron Christophel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include "Arduino.h"

void init_hrs3300();
void start_hrs3300();
void end_hrs3300();
byte get_heartrate();
byte get_last_heartrate();
void get_heartrate_ms();
void check_timed_heartrate(int minutes);
