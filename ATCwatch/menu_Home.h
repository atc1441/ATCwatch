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
#include "inputoutput.h"
#include "display.h"
#include "ble.h"
#include "time.h"
#include "battery.h"
#include "accl.h"
#include "push.h"
#include "heartrate.h"
#include "fonts.h"
#include "sleep.h"
#include <lvgl.h>


class HomeScreen : public Screen
{
  public:
    virtual void pre()
    {
      time_data = get_time();
      accl_data = get_accl_data();

      lv_style_copy( &st, &lv_style_plain );
      st.text.color = lv_color_hsv_to_rgb(10, 5, 95);
      st.text.font = &mksd50;

      label_time = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text_fmt(label_time,  "%02i:%02i:%02i", time_data.hr, time_data.min, time_data.sec);
      lv_obj_set_style( label_time, &st );
      lv_obj_align(label_time, NULL, LV_ALIGN_CENTER, 0, -40);
      label_date = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text_fmt(label_date, "%02i.%02i.%04i", time_data.day, time_data.month, time_data.year);
      lv_obj_set_style( label_date, &st );
      lv_obj_align(label_date, NULL, LV_ALIGN_CENTER, 0, 30);


      label_battery = lv_label_create(lv_scr_act(), NULL);
      lv_obj_align(label_battery, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 25, 5);
      lv_label_set_text_fmt(label_battery, "%i%%", get_battery_percent());


      label_ble = lv_label_create(lv_scr_act(), NULL);
      lv_obj_align(label_ble, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 5, 5);
      lv_label_set_text(label_ble, LV_SYMBOL_BLUETOOTH);

      lv_style_copy(&style_ble, lv_label_get_style(label_ble, LV_LABEL_STYLE_MAIN));
      style_ble.text.color = LV_COLOR_RED;
      style_ble.text.font = LV_FONT_DEFAULT;
      lv_obj_set_style(label_ble, &style_ble);

      lv_style_copy(&style_battery, lv_label_get_style(label_battery, LV_LABEL_STYLE_MAIN));
      style_battery.text.color = lv_color_hsv_to_rgb(10, 5, 95);
      lv_obj_set_style(label_battery, &style_battery);


      img_heart = lv_img_create(lv_scr_act(), NULL);
      lv_img_set_src(img_heart, &IsymbolHeartSmall);
      lv_obj_align(img_heart, NULL, LV_ALIGN_IN_BOTTOM_LEFT,  0, -34);

      label_heart = lv_label_create(lv_scr_act(), NULL);
      lv_obj_set_width(label_heart, 240);
      lv_label_set_text_fmt(label_heart, "%i", get_last_heartrate());
      lv_obj_align(label_heart, img_heart, LV_ALIGN_OUT_RIGHT_MID, 2, 0);


      img_steps = lv_img_create(lv_scr_act(), NULL);
      lv_img_set_src(img_steps, &IsymbolStepsSmall);
      lv_obj_align(img_steps, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 120, -34);

      label_steps = lv_label_create(lv_scr_act(), NULL);
      lv_obj_set_width(label_steps, 240);
      lv_label_set_text_fmt(label_steps, "%i", accl_data.steps);
      lv_obj_align(label_steps, img_steps, LV_ALIGN_OUT_RIGHT_MID, 2, 0);


      img_msg = lv_img_create(lv_scr_act(), NULL);
      lv_img_set_src(img_msg, &IsymbolMsgSmall);
      lv_obj_align(img_msg, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 0, -8);

      label_msg = lv_label_create(lv_scr_act(), NULL);

      lv_style_copy(&style_msg, lv_label_get_style(label_ble, LV_LABEL_STYLE_MAIN));
      style_msg.text.color = lv_color_hsv_to_rgb(10, 5, 95);
      style_msg.text.font = &sans_regular;
      lv_obj_set_style(label_msg, &style_msg);

      lv_obj_set_width(label_msg, 240);
      lv_label_set_text(label_msg, " ");
      lv_label_set_text(label_msg, string2char(get_push_msg(30)));
      lv_obj_align(label_msg, img_msg, LV_ALIGN_OUT_RIGHT_MID, 2, 0);
    }

    virtual void main()
    {
      time_data = get_time();
      accl_data = get_accl_data();

      lv_label_set_text_fmt(label_time,  "%02i:%02i:%02i", time_data.hr, time_data.min, time_data.sec);
      lv_label_set_text_fmt(label_date, "%02i.%02i.%04i", time_data.day, time_data.month, time_data.year);

      lv_label_set_text_fmt(label_battery, "%i%%", get_battery_percent());

      lv_label_set_text_fmt(label_heart, "%i", get_last_heartrate());
      lv_label_set_text_fmt(label_steps, "%i", accl_data.steps);

      if (get_vars_ble_connected())
        style_ble.text.color = LV_COLOR_MAKE(0x27, 0xA6, 0xFF);
      else
        style_ble.text.color = LV_COLOR_RED;
      lv_obj_set_style(label_ble, &style_ble);

      if (get_charge())
        style_battery.text.color = lv_color_hsv_to_rgb(10, 5, 95);
      else
        style_battery.text.color = LV_COLOR_MAKE(0x05, 0xF9, 0x25);
      lv_obj_set_style(label_battery, &style_battery);

    }

    virtual void up()
    {
      inc_vars_menu();
    }

    virtual void down()
    {
      dec_vars_menu();
    }

    virtual void left()
    {
    }

    virtual void right()
    {
    }

    virtual void button_push(int length)
    {
      sleep_down();
    }

  private:
    time_data_struct time_data;
    accl_data_struct accl_data;
    lv_style_t st;
    lv_obj_t *label, *label_heart, *label_steps, *label_msg;
    lv_obj_t *label_time, *label_date;
    lv_obj_t *label_ble, *label_battery;
    lv_style_t style_ble, style_battery, style_msg;
    lv_obj_t * img_heart, *img_steps, *img_msg;

    char* string2char(String command) {
      if (command.length() != 0) {
        char *p = const_cast<char*>(command.c_str());
        return p;
      }
    }
};

HomeScreen homeScreen;
