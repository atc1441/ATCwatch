
#include "battery.h"
#include "Arduino.h"
#include "push.h"
#include "pinout.h"
#include "bootloader.h"

long lastReq = 10000;
int lastReturn;
int lastCounter;
int lastmvolts;

//check battery stuff
int battery_delay = 60000;
long last_battery_run;
bool batteryWasNotified = false;

void init_battery() {
  pinMode(CHARGE_INDICATION, INPUT);
  pinMode(POWER_INDICATION, INPUT);
  pinMode(POWER_CONTROL, OUTPUT);
  digitalWrite(POWER_CONTROL, HIGH);
  lastReturn = mv_to_percent(get_battery());
}

float get_battery() {
  return map(get_battery_raw(), 496, 696, 3000, 4200) / 1000.0;
}

int get_battery_percent() {
  lastmvolts += map(get_battery_raw(), 496, 696, 3000, 4200);
  lastCounter++;
  if (millis() - lastReq > 10000) {
    lastReq = millis();
    lastReturn =  mv_to_percent(lastmvolts / lastCounter);
    lastCounter = 0;
    lastmvolts = 0;
    return lastReturn;
  }
  return lastReturn;
}

int mv_to_percent(float mvolts) {
  if ( mvolts >= 4145 ) return 100;
  else if ( mvolts > 4010 ) return (99 - (int16_t)(4145 - mvolts) / 13);
  else if ( mvolts > 3920 ) return (90 - (int16_t)(4010 - mvolts) / 9);
  else if ( mvolts > 3850 ) return (80 - (int16_t)(3920 - mvolts) / 7);
  else if ( mvolts > 3789 ) return (70 - (int16_t)(3850 - mvolts) / 6);
  else if ( mvolts > 3740 ) return (60 - (int16_t)(3789 - mvolts) / 4);
  else if ( mvolts > 3703 ) return (50 - (int16_t)(3740 - mvolts) / 3);
  else if ( mvolts > 3676 ) return (40 - (int16_t)(3703 - mvolts) / 2);
  else if ( mvolts > 3648 ) return (30 - (int16_t)(3676 - mvolts) / 2);
  else if ( mvolts > 3609 ) return (20 - (int16_t)(3648 - mvolts) / 3);
  else if ( mvolts > 3575 ) return (10 - (int16_t)(3609 - mvolts) / 6);
  else if ( mvolts > 3482 ) return ( 5 - (int16_t)(3575 - mvolts) / 18);
  else return 0;
}

int get_battery_raw() {
  return analogRead(BATTERY_VOLTAGE);
}

bool get_charge() {
  return digitalRead(POWER_INDICATION);
}

bool get_charged() {
  return digitalRead(CHARGE_INDICATION);
}

void check_battery_status() {
  if (millis() - last_battery_run > battery_delay) {
    if (get_battery_percent() < 15) {
      if (!batteryWasNotified) {
        batteryWasNotified = true;
        show_push("Battery Empty");
      }
    } else if (get_battery_percent() < 5) {
      system_off();
    } else {
      batteryWasNotified = false;
    }
  }
}
