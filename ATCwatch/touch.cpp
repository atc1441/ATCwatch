/*
   Copyright (c) 2020 Aaron Christophel

   SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "touch.h"
#include "Arduino.h"
#include "pinout.h"
#include "sleep.h"
#include "i2c.h"

int touch_enable = false;
bool was_touched = false;
bool touch_interrupt = false;

uint8_t touch_dev_addr = 0x15;

touch_data_struct touch_data;

void init_touch() {
  if (!touch_enable) {
    touch_enable = true;
    pinMode(TP_RESET, OUTPUT);
    pinMode(TP_INT, INPUT);

    digitalWrite(TP_RESET, HIGH );
    delay(50);
    digitalWrite(TP_RESET, LOW);
    delay(5);
    digitalWrite(TP_RESET, HIGH );
    delay(50);

    user_i2c_read(touch_dev_addr, 0x15, &touch_data.version15, 1);
    delay(5);
    user_i2c_read(touch_dev_addr, 0xA7, touch_data.versionInfo, 3);
  }
}

void sleep_touch(bool state) {
  digitalWrite(TP_RESET, LOW);
  delay(5);
  digitalWrite(TP_RESET, HIGH );
  delay(50);
  if (state) {
    byte standby_value = 0x03;
    user_i2c_write(touch_dev_addr, 0xA5, &standby_value, 1);
  }
}

void set_new_touch_interrupt() {
  touch_interrupt = true;
}

bool get_new_touch_interrupt() {
  bool temp = touch_interrupt;
  touch_interrupt = false;
  return temp;
}

bool get_was_touched() {
  return was_touched;
}

void set_was_touched(bool state) {
  was_touched = state;
}

void get_read_touch() {
  if (!touch_enable)init_touch();

  byte data_raw[8];
  user_i2c_read(touch_dev_addr, 0x01, data_raw, 6);

  touch_data.gesture = data_raw[0];
  touch_data.touchpoints = data_raw[1];
  touch_data.event = data_raw[2] >> 6;
  touch_data.xpos = data_raw[3];
  touch_data.ypos = data_raw[5];
  if (touch_data.xpos == 255 && touch_data.ypos == 255) {
    touch_data.xpos = touch_data.last_xpos;
    touch_data.ypos = touch_data.last_ypos;
  } else {
    touch_data.last_xpos = touch_data.xpos;
    touch_data.last_ypos = touch_data.ypos;
  }
}

touch_data_struct get_touch() {
  return touch_data;
}
