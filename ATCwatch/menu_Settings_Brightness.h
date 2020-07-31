/*
 * Copyright (c) 2020 Aaron Christophel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once
#include "Arduino.h"
#include "class.h"
#include "images.h"
#include "menu.h"
#include "display.h"
#include "ble.h"
#include "time.h"
#include "battery.h"
#include "accl.h"
#include "push.h"
#include "heartrate.h"


class SettingsBrightnessScreen : public Screen
{
  public:
    virtual void pre()
    {
      set_swipe_enabled(true);

      backlight_brightness = get_backlight();

      label_screen = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text(label_screen, "Set Brightness");
      lv_obj_align(label_screen, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);

      btn1 = lv_btn_create(lv_scr_act(), NULL);
      lv_obj_set_event_cb(btn1, lv_event_handler);
      lv_obj_align(btn1, NULL, LV_ALIGN_IN_BOTTOM_MID, -55, 0);
      lv_btn_set_fit2(btn1, LV_FIT_NONE, LV_FIT_TIGHT);
      btn1_label = lv_label_create(btn1, NULL);
      lv_label_set_text(btn1_label, "Abort");

      btn2 = lv_btn_create(lv_scr_act(), NULL);
      lv_obj_set_event_cb(btn2, lv_event_handler);
      lv_btn_set_fit2(btn2, LV_FIT_NONE, LV_FIT_TIGHT);
      lv_obj_align(btn2, NULL, LV_ALIGN_IN_BOTTOM_MID, 55, 0);
      btn2_label = lv_label_create(btn2, NULL);
      lv_label_set_text(btn2_label, "Save");

      slider = lv_slider_create(lv_scr_act(), NULL);
      lv_slider_set_range(slider, 1, 7);
      lv_obj_set_event_cb(slider, lv_event_handler);
      lv_obj_align(slider, NULL, LV_ALIGN_CENTER, 0, -10);
      lv_slider_set_value(slider, get_backlight(), LV_ANIM_OFF);

      slider_label = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text_fmt(slider_label, "%u", lv_slider_get_value(slider));
      lv_obj_set_auto_realign(slider_label, true);
      lv_obj_align(slider_label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
    }

    virtual void lv_event_class(lv_obj_t * object, lv_event_t event)
    {
      if (object == btn1 && event == LV_EVENT_SHORT_CLICKED) {
        set_backlight(backlight_brightness);
        set_last_menu();
      } else if (object == btn2 && event == LV_EVENT_SHORT_CLICKED) {
        set_last_menu();
        set_motor_ms(35);
      } else if (object == slider && event == LV_EVENT_VALUE_CHANGED) {
        int slider_backlight = lv_slider_get_value(slider);
        lv_label_set_text_fmt(slider_label, "%u", slider_backlight);
        set_backlight(slider_backlight);
      }
    }

    virtual void up()
    {
    }

    virtual void down()
    {
    }

    virtual void right()
    {
    }

    virtual void left()
    {
    }

  private:
    int backlight_brightness;
    lv_obj_t *label_screen;
    lv_obj_t *btn1, *btn2, *btn1_label, *btn2_label, *label_points;
    lv_obj_t *slider, *slider_label;
};

SettingsBrightnessScreen settingsBrightnessScreen;
