
#include "touch.h"
#include "Arduino.h"
#include "pinout.h"
#include "sleep.h"
#include <Wire.h>

int touch_enable = false;

touch_data_struct touch_data;

void init_touch() {
  if (!touch_enable) {
    touch_enable = true;
    pinMode(TP_RESET, OUTPUT);
    pinMode(TP_INT, INPUT);
    Wire.begin();
    Wire.setClock(200000);

    digitalWrite(TP_RESET, HIGH );
    delay(50);
    digitalWrite(TP_RESET, LOW);
    delay(5);
    digitalWrite(TP_RESET, HIGH );
    delay(50);

    set_i2cReading(true);
    Wire.beginTransmission(0x15);
    Wire.write(0x15);
    Wire.endTransmission();
    Wire.requestFrom(0x15, 1);
    byte t1 = Wire.read();

    Wire.beginTransmission(0x15);
    Wire.write(0xA7);
    Wire.endTransmission();
    Wire.requestFrom(0x15, 1);
    byte t2 = Wire.read();

    Wire.beginTransmission(0x15);
    Wire.write(0xA8);
    Wire.endTransmission();
    Wire.requestFrom(0x15, 1);
    byte t3 = Wire.read();

    Wire.beginTransmission(0x15);
    Wire.write(0xA9);
    Wire.endTransmission();
    Wire.requestFrom(0x15, 1);
    byte t4 = Wire.read();
    set_i2cReading(false);
  }
}

void sleep_touch(bool state) {
    touch_enable = false;
    digitalWrite(TP_RESET, LOW);
    delay(5);
    digitalWrite(TP_RESET, HIGH );
    delay(50);
  if (state) {
    set_i2cReading(true);
    Wire.beginTransmission(0x15);
    Wire.write(0xA5);
    Wire.write(0x03);
    Wire.endTransmission();
    set_i2cReading(false);
  }
}

void get_read_touch() {
  if (!touch_enable)init_touch();
  set_i2cReading(true);
  byte data_raw[8];
  Wire.beginTransmission(0x15);
  Wire.write(1);
  if (Wire.endTransmission())return;
  Wire.requestFrom(0x15, 6);
  for (int x = 0; x < 6; x++)
  {
    data_raw[x] = Wire.read();
  }
  touch_data.gesture = data_raw[0];
  touch_data.xpos = data_raw[3];
  touch_data.ypos = data_raw[5];
  set_i2cReading(false);
}

touch_data_struct get_touch() {
  // get_read_touch();
  return touch_data;
}
