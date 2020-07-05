#pragma once

#include "Arduino.h"
#include <lvgl.h>

lv_color_t color_list[] = {lv_color_hsv_to_rgb(10, 5, 95), LV_COLOR_GRAY, LV_COLOR_BLACK, LV_COLOR_RED, LV_COLOR_GREEN, LV_COLOR_BLUE};

int main_color_save = 2;
int grad_color_save = 2;
int font_color_save = 0;

void set_gray_screen_style( lv_font_t * font = LV_FONT_DEFAULT) {
  static lv_style_t style_screen;
  lv_style_copy(&style_screen, &lv_style_plain);
  style_screen.body.main_color = color_list[main_color_save];// LV_COLOR_GREEN;
  style_screen.body.grad_color = color_list[grad_color_save];//LV_COLOR_BLUE;
  style_screen.text.color = color_list[font_color_save];
  style_screen.text.font = font;
  lv_obj_set_style(lv_scr_act(), &style_screen);
}

void set_main_color(int new_color) {
  main_color_save = new_color;
}

void set_grad_color(int new_color) {
  grad_color_save = new_color;
}

void set_font_color(int new_color) {
  font_color_save = new_color;
}

int get_main_color() {
  return main_color_save;
}

int get_grad_color() {
  return grad_color_save;
}

int get_font_color() {
  return font_color_save;
}
