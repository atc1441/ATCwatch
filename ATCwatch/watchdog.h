/*
 * Copyright (c) 2020 Aaron Christophel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later WITH GPL-3.0-linking-exception
 */

#pragma once

#include "Arduino.h"

void init_watchdog();
void watchdog_enable(int timeout);
void watchdog_feed();
