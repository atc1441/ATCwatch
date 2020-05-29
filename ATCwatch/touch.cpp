
#include "touch.h"
#include "Arduino.h"
#include "pinout.h"
#include "sleep.h"
#include <Wire.h>

int touch_enable = false;

touch_data_struct touch_data;

void init_touch() {
  if (!touch_enable) {
    set_i2cReading(true);
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
  //  Wire.beginTransmission(0x15);
  //  Wire.write(0xA5);
  //  Wire.write(0x03);
  //  Wire.endTransmission();
    set_i2cReading(false);
  }
}

void sleep_touch() {
  if (touch_enable) {
    set_i2cReading(true);
    touch_enable = false;
    digitalWrite(TP_RESET, LOW);
    delay(5);
    digitalWrite(TP_RESET, HIGH );
    delay(50);
 //   Wire.beginTransmission(0x15);
 //   Wire.write(0xA5);
 //   Wire.write(0x03);
 //   Wire.endTransmission();
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
  Wire.requestFrom(0x15, 7);
  for (int x = 0; x < 8; x++)
  {
    data_raw[x] = Wire.read();
  }
  touch_data.gesture = data_raw[0];
  touch_data.xpos = data_raw[3];
  touch_data.ypos = data_raw[5];
  set_i2cReading(false);
}

touch_data_struct get_touch() {
  get_read_touch();
  return touch_data;
}
