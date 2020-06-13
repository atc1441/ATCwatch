#pragma once

#include "Arduino.h"
#include <lvgl.h>

void set_gray_screen_style( lv_font_t * font = LV_FONT_DEFAULT) {
  static lv_style_t style_screen;
  lv_style_copy(&style_screen, &lv_style_plain);
  style_screen.body.main_color = LV_COLOR_GRAY;// LV_COLOR_GREEN;
  style_screen.body.grad_color = LV_COLOR_GRAY;
  style_screen.text.color = lv_color_hsv_to_rgb(10, 5, 95);
  style_screen.text.font = font;
  lv_obj_set_style(lv_scr_act(), &style_screen);
}
