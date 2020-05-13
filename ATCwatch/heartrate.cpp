
#include "heartrate.h"
#include "pinout.h"
#include "inputoutput.h"
#include "sleep.h"
#include "HRS3300lib.h"

HRS3300lib HRS3300;
bool heartrate_enable = false;
bool is_heartrate_enable = false;
byte last_heartrate_ms;
byte last_heartrate;
//timed heartrate stuff
bool timed_heart_rates = true;
bool has_good_heartrate = false;
int hr_answers;
bool disabled_hr_allready = false;

void init_hrs3300() {
  pinMode(HRS3300_TEST, INPUT);
  start_hrs3300();
  end_hrs3300();
}

void start_hrs3300() {
  if (!heartrate_enable) {
    heartrate_enable = true;
    set_i2cReading(true);
    HRS3300.begin();
    set_i2cReading(false);
  }
}

void end_hrs3300() {
  if (heartrate_enable) {
    heartrate_enable = false;
    set_i2cReading(true);
    HRS3300.end();
    set_i2cReading(false);
  }
}

byte get_heartrate() {
  // get_heartrate_ms();
  set_i2cReading(true);
  byte hr = last_heartrate_ms;
  set_i2cReading(false);
  switch (hr) {
    case 0:
      break;
    case 255:
      break;
    case 254:
      // display.println("NO TOUCH    ");
      break;
    case 253:
      // display.println("Please wait    ");
      break;
    default:
      last_heartrate = hr;
      break;
  }
  return hr;
}

byte get_last_heartrate() {
  return last_heartrate;
}

void get_heartrate_ms() {
  if (heartrate_enable)
    last_heartrate_ms = HRS3300.getHR();
}

void check_timed_heartrate(int minutes) {
  if (timed_heart_rates) {
    if (minutes == 0 || minutes == 15 || minutes == 30 || minutes == 45) {
      if (!has_good_heartrate) {
        disabled_hr_allready = false;
        start_hrs3300();
        byte hr = get_heartrate();
        if (hr > 0 && hr < 253) {
          hr_answers++;
          if (hr_answers >= 5) {
            has_good_heartrate = true;
          }
        } else if (hr == 254) {
          hr_answers++;
          if (hr_answers >= 10) {
            has_good_heartrate = true;
          }
        }
      } else {
        end_hrs3300();
      }
    } else {
      if (!disabled_hr_allready) {
        disabled_hr_allready = true;
        end_hrs3300();
        hr_answers = 0;
        has_good_heartrate = false;
      }
    }
  }
}
