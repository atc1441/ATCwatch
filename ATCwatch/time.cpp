

#include "Arduino.h"
#include "sleep.h"
#include "time.h"
#include "heartrate.h"
#include "inputoutput.h"
#include <TimeLib.h>

time_data_struct time_data;

void init_time() {
  int year = 2020;
  int month = 5;
  int day = 12;
  int hr = 13;
  int min = 41;
  int sec = 0;
  setTime( hr, min, sec, day, month, year);
}

time_data_struct get_time() {
  time_data.year = year();
  time_data.month = month();
  time_data.day = day();
  time_data.hr = hour();
  time_data.min = minute();
  time_data.sec = second();
  return time_data;
}

void SetDateTimeString(String datetime) {
  int year = datetime.substring(0, 4).toInt();
  int month = datetime.substring(4, 6).toInt();
  int day = datetime.substring(6, 8).toInt();
  int hr = datetime.substring(8, 10).toInt();
  int min = datetime.substring(10, 12).toInt();
  int sec = datetime.substring(12, 14).toInt();
  setTime( hr, min, sec, day, month, year);
}

String GetDateTimeString() {
  String datetime = String(year());
  if (month() < 10) datetime += "0";
  datetime += String(month());
  if (day() < 10) datetime += "0";
  datetime += String(day());
  if (hour() < 10) datetime += "0";
  datetime += String(hour());
  if (minute() < 10) datetime += "0";
  datetime += String(minute());
  return datetime;
}
