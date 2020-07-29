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


class OffScreen : public Screen
{
  public:
    virtual void pre()
    {
      static const char * btns[] = {"Yes", "No", ""};
      lv_obj_t * mbox1 = lv_mbox_create(lv_scr_act(), NULL);
      lv_mbox_set_text(mbox1, "Shutdown ?");
      lv_mbox_add_btns(mbox1, btns);
      lv_obj_set_width(mbox1, 200);
      lv_obj_set_event_cb(mbox1, event_handler);
      lv_obj_align(mbox1, NULL, LV_ALIGN_CENTER, 0, 0);
    }

    virtual void main()
    {

    }
    virtual void right()
    {
      set_last_menu();
    }

    virtual void click(touch_data_struct touch_data)
    {

    }

    virtual void pre_display()// if this is set, the screen gets not cleared
    {
    }


  private:

    static void event_handler(lv_obj_t * obj, lv_event_t event)
    {
      if (event == LV_EVENT_VALUE_CHANGED) {
        if ("Yes" == lv_mbox_get_active_btn_text(obj))
          system_off();
        else if ("No" == lv_mbox_get_active_btn_text(obj))
          set_last_menu();
      }
    }
};

OffScreen offScreen;
