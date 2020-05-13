
#pragma once

#include "Arduino.h"

void init_watchdog();
void watchdog_enable(int timeout);
void watchdog_feed();
