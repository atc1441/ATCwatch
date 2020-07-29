/*
 * Copyright (c) 2020 Aaron Christophel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "inputoutput.h"
#include "Arduino.h"
#include "pinout.h"

volatile long vibration_end_time = 0;
volatile long led_end_time = 0;
volatile bool inputoutput_inited = false;
volatile int motor_power = 100;

void init_inputoutput() {

  pinMode(STATUS_LED, OUTPUT);
  pinMode(VIBRATOR_OUT, OUTPUT);
  pinMode(PUSH_BUTTON_IN, INPUT);
  if (PUSH_BUTTON_OUT != -1) {
    pinMode(PUSH_BUTTON_OUT, OUTPUT);
    digitalWrite(PUSH_BUTTON_OUT, HIGH);
  }

  set_led(0);
  set_motor(0);
  inputoutput_inited = true;
}

bool get_button() {
  if (!inputoutput_inited)init_inputoutput();
  if (PUSH_BUTTON_OUT != -1) {
    pinMode(PUSH_BUTTON_OUT, OUTPUT);
    digitalWrite(PUSH_BUTTON_OUT, HIGH);
  }
  bool button = digitalRead(PUSH_BUTTON_IN);
  return button;
}

void set_led(bool state) {
  if (state)
    digitalWrite(STATUS_LED, HIGH);
  else
    digitalWrite(STATUS_LED, LOW);
}

void set_motor(bool state) {
  if (state)
    digitalWrite(VIBRATOR_OUT, LOW);
  else
    digitalWrite(VIBRATOR_OUT, HIGH);
}

void set_motor_ms(int ms) {
  set_motor(1);
  vibration_end_time = millis() + ms;
}

void set_motor_ms() {
  set_motor(1);
  vibration_end_time = millis() + motor_power;
}

void set_motor_power(int ms) {
  motor_power = ms;
}

int get_motor_power() {
  return motor_power;
}

void set_led_ms(int ms) {
  set_led(1);
  led_end_time = millis() + ms;
}

void check_inputoutput_times() {
  if (millis() > vibration_end_time)set_motor(0);
  if (millis() > led_end_time)set_led(0);
}
