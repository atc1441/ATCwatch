/*
 * Copyright (c) 2020 Aaron Christophel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include "Arduino.h"

struct time_data_struct {
  int year;
  int month;
  int day;
  int hr;
  int min;
  int sec;
};

void init_time();
time_data_struct get_time();
void SetDateTimeString(String datetime);
void SetDate(int year, int month, int day);
void SetTime(int hr, int min);
String GetDateTimeString();
