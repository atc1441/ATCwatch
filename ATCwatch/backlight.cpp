/*
 * Copyright (c) 2020 Aaron Christophel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "backlight.h"
#include "Arduino.h"
#include "pinout.h"

int backlight_brightness = 0;
int min_backlight_brightness = 1;
int max_backlight_brightness = 7;

void init_backlight() {
  pinMode(LCD_BACKLIGHT_LOW, OUTPUT);
  pinMode(LCD_BACKLIGHT_MID, OUTPUT);
  pinMode(LCD_BACKLIGHT_HIGH, OUTPUT);

  set_backlight(0);
}

void set_backlight() {
  set_backlight(backlight_brightness);
}

int get_backlight() {
  return backlight_brightness;
}

void set_backlight(int brightness) {
  if (brightness)backlight_brightness = brightness;
  switch (brightness) {
    case 0:
      digitalWrite(LCD_BACKLIGHT_LOW, HIGH);
      digitalWrite(LCD_BACKLIGHT_MID, HIGH);
      digitalWrite(LCD_BACKLIGHT_HIGH, HIGH);
      break;
    case 1:
      digitalWrite(LCD_BACKLIGHT_LOW, LOW);
      digitalWrite(LCD_BACKLIGHT_MID, HIGH);
      digitalWrite(LCD_BACKLIGHT_HIGH, HIGH);
      break;
    case 2:
      digitalWrite(LCD_BACKLIGHT_LOW, HIGH);
      digitalWrite(LCD_BACKLIGHT_MID, LOW);
      digitalWrite(LCD_BACKLIGHT_HIGH, HIGH);
      break;
    case 3:
      digitalWrite(LCD_BACKLIGHT_LOW, LOW);
      digitalWrite(LCD_BACKLIGHT_MID, LOW);
      digitalWrite(LCD_BACKLIGHT_HIGH, HIGH);
      break;
    case 4:
      digitalWrite(LCD_BACKLIGHT_LOW, HIGH);
      digitalWrite(LCD_BACKLIGHT_MID, HIGH);
      digitalWrite(LCD_BACKLIGHT_HIGH, LOW);
      break;
    case 5:
      digitalWrite(LCD_BACKLIGHT_LOW, LOW);
      digitalWrite(LCD_BACKLIGHT_MID, HIGH);
      digitalWrite(LCD_BACKLIGHT_HIGH, LOW);
      break;
    case 6:
      digitalWrite(LCD_BACKLIGHT_LOW, HIGH);
      digitalWrite(LCD_BACKLIGHT_MID, LOW);
      digitalWrite(LCD_BACKLIGHT_HIGH, LOW);
      break;
    case 7:
      digitalWrite(LCD_BACKLIGHT_LOW, LOW);
      digitalWrite(LCD_BACKLIGHT_MID, LOW);
      digitalWrite(LCD_BACKLIGHT_HIGH, LOW);
      break;
  }
}

void inc_backlight() {
  backlight_brightness++;
  if (backlight_brightness > max_backlight_brightness)backlight_brightness = min_backlight_brightness;
}

void dec_backlight() {
  backlight_brightness--;
  if (backlight_brightness < min_backlight_brightness)backlight_brightness = max_backlight_brightness;
}
