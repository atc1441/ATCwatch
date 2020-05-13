
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
String GetDateTimeString();
