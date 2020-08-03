/*
   Copyright (c) 2020 Aaron Christophel

   SPDX-License-Identifier: GPL-3.0-or-later
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
#include "screen_style.h"


class AcclScreen : public Screen
{
  public:
    virtual void pre()
    {
      label = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text(label, "Accl");
      lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 10, 0);

      label_x = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text(label_x, "X:");
      lv_obj_align(label_x, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 25);
      label_y = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text(label_y, "Y:");
      lv_obj_align(label_y, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 45);
      label_z = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text(label_z, "Z:");
      lv_obj_align(label_z, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 65);
      label_temp = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text(label_temp, "Temp:");
      lv_obj_align(label_temp, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 85);
      label_steps = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text(label_steps, "Steps:");
      lv_obj_align(label_steps, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 105);
      label_activity = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text(label_activity, "Activity:");
      lv_obj_align(label_activity, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 125);
    }

    virtual void main()
    {
      accl_data_struct accl_data = get_accl_data();

      lv_label_set_text_fmt(label_x, "X: %i", accl_data.x);
      lv_label_set_text_fmt(label_y, "Y: %i", accl_data.y);
      lv_label_set_text_fmt(label_z, "Z: %i", accl_data.z);
      lv_label_set_text_fmt(label_temp, "Temp: %i", accl_data.temp);
      lv_label_set_text_fmt(label_steps, "Steps: %i", accl_data.steps);
      lv_label_set_text_fmt(label_activity, "Activity: %i", accl_data.activity);
    }

    virtual void right()
    {
      set_last_menu();
    }

    virtual void down()
    {
      reset_step_counter();
    }

  private:
    lv_obj_t *label, *label_x, *label_y, *label_z;
    lv_obj_t *label_temp, *label_steps, *label_activity;
};

AcclScreen acclScreen;
