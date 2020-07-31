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


class SettingsDateScreen : public Screen
{
  public:
    virtual void pre()
    {
      set_swipe_enabled(true);

      label_screen = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text(label_screen, "Set Date");
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

      roller1 = lv_roller_create(lv_scr_act(), NULL);
      lv_roller_set_options(roller1,
                            "January\n"
                            "February\n"
                            "March\n"
                            "April\n"
                            "May\n"
                            "June\n"
                            "July\n"
                            "August\n"
                            "September\n"
                            "October\n"
                            "November\n"
                            "December",
                            LV_ROLLER_MODE_INIFINITE);

      lv_roller_set_visible_row_count(roller1, 4);
      lv_obj_align(roller1, NULL, LV_ALIGN_CENTER, -14, -15);

      roller = lv_roller_create(lv_scr_act(), NULL);
      lv_roller_set_options(roller,
                            "01\n"
                            "02\n"
                            "03\n"
                            "04\n"
                            "05\n"
                            "06\n"
                            "07\n"
                            "08\n"
                            "09\n"
                            "10\n"
                            "11\n"
                            "12\n"
                            "13\n"
                            "14\n"
                            "15\n"
                            "16\n"
                            "17\n"
                            "18\n"
                            "19\n"
                            "20\n"
                            "21\n"
                            "22\n"
                            "23\n"
                            "24\n"
                            "25\n"
                            "26\n"
                            "27\n"
                            "28\n"
                            "29\n"
                            "30\n"
                            "31",
                            LV_ROLLER_MODE_INIFINITE);

      lv_roller_set_visible_row_count(roller, 4);
      lv_obj_align(roller, roller1, LV_ALIGN_OUT_LEFT_MID, -5, 0);

      roller2 = lv_roller_create(lv_scr_act(), NULL);
      lv_roller_set_options(roller2,
                            "2020\n"
                            "2021\n"
                            "2022\n"
                            "2023\n"
                            "2024\n"
                            "2025\n"
                            "2026\n"
                            "2027\n"
                            "2028\n"
                            "2029\n"
                            "2030\n"
                            "2031\n"
                            "2032\n"
                            "2033",
                            LV_ROLLER_MODE_INIFINITE);

      lv_roller_set_visible_row_count(roller2, 4);
      lv_obj_align(roller2, roller1, LV_ALIGN_OUT_RIGHT_MID, 5, 0);

      time_data_struct time_data = get_time();
      lv_roller_set_selected(roller, ( time_data.day - 1), LV_ANIM_OFF);
      lv_roller_set_selected(roller1, (time_data.month - 1), LV_ANIM_OFF);
      lv_roller_set_selected(roller2, (time_data.year - 2020), LV_ANIM_OFF);
    }

    virtual void lv_event_class(lv_obj_t * object, lv_event_t event)
    {
      if (object == btn1 && event == LV_EVENT_SHORT_CLICKED) {
        set_last_menu();
      } else if (object == btn2 && event == LV_EVENT_SHORT_CLICKED) {
        int roller_day = lv_roller_get_selected(roller) + 1;
        int roller_month = lv_roller_get_selected(roller1) + 1;
        int roller_year = lv_roller_get_selected(roller2) + 2020;
        SetDate(roller_year, roller_month, roller_day);
        set_last_menu();
        set_motor_ms(35);
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
    lv_obj_t *label_screen;
    lv_obj_t *btn1, *btn2, *btn1_label, *btn2_label, *label_points;
    lv_obj_t *roller, *roller1, *roller2;
};

SettingsDateScreen settingsDateScreen;
