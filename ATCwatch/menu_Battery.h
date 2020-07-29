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


class BatteryScreen : public Screen
{
  public:
    virtual void pre()
    {
      label = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text(label, "Battery");
      lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);

      label_battery = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text(label_battery, "---%");
      lv_obj_align(label_battery, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 10, 30);

      lv_style_copy( &st, &lv_style_plain );
      st.text.color = lv_color_hsv_to_rgb(10, 5, 95);
      st.text.font = &mksd50;

      label_battery_big = lv_label_create(lv_scr_act(), NULL);
      lv_obj_set_style( label_battery_big, &st );
      lv_label_set_text(label_battery_big, "---%");
      lv_obj_align(label_battery_big, lv_scr_act(), LV_ALIGN_CENTER, 0, -20);

      label_backlight_big = lv_label_create(lv_scr_act(), NULL);
      lv_obj_set_style( label_backlight_big, &st );
      lv_label_set_text(label_backlight_big, "-");
      lv_obj_align(label_backlight_big, lv_scr_act(), LV_ALIGN_CENTER, 0, 50);
      lv_label_set_text_fmt(label_backlight_big, "%i", get_backlight());

      lv_style_copy(&style_battery, lv_label_get_style(label_battery, LV_LABEL_STYLE_MAIN));
      style_battery.text.color = lv_color_hsv_to_rgb(10, 5, 95);
      lv_obj_set_style(label_battery, &style_battery);
    }

    virtual void main()
    {
      lv_label_set_text_fmt(label_battery, "%i%%", get_battery_percent());
      lv_label_set_text_fmt(label_battery_big, "%i%%", get_battery_percent());
      if (get_charge())
        style_battery.text.color = lv_color_hsv_to_rgb(10, 5, 95);
      else
        style_battery.text.color = LV_COLOR_MAKE(0x05, 0xF9, 0x25);
      lv_obj_set_style(label_battery, &style_battery);

    }

    virtual void up()
    {
      inc_backlight();
      set_backlight();
      lv_label_set_text_fmt(label_backlight_big, "%i", get_backlight());
    }

    virtual void down()
    {
      dec_backlight();
      set_backlight();
      lv_label_set_text_fmt(label_backlight_big, "%i", get_backlight());
    }

    virtual void right()
    {
      set_last_menu();
    }
    
  private:
    lv_obj_t *label;
    lv_obj_t *label_battery, *label_battery_big, *label_backlight_big;
    lv_style_t style_battery, st;
};

BatteryScreen batteryScreen;
