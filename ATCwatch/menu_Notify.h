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
#include "fonts.h"


class NotifyScreen : public Screen
{
  public:
    virtual void pre()
    {
      set_gray_screen_style(&sans_regular);

      lv_obj_t * img1 = lv_img_create(lv_scr_act(), NULL);
      lv_img_set_src(img1, &IsymbolMsg);
      lv_obj_align(img1, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);

      /*
      label_msg = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_long_mode(label_msg, LV_LABEL_LONG_BREAK);
      lv_obj_set_width(label_msg,240);
      lv_label_set_text(label_msg, "");
      lv_label_set_text(label_msg, string2char(get_push_msg()));
      lv_obj_align(label_msg, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
      */



      label_msg_name = lv_label_create(lv_scr_act(), NULL);
      //lv_label_set_long_mode(label_msg_name, LV_LABEL_LONG_BREAK);
      lv_obj_set_width(label_msg_name,240);
      lv_label_set_text(label_msg_name, "");
      lv_label_set_text(label_msg_name, string2char(get_name_msg()));
      lv_obj_align(label_msg_name, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);

      label_msg_title = lv_label_create(lv_scr_act(), NULL);
      //lv_label_set_long_mode(label_msg_title, LV_LABEL_LONG_BREAK);
      lv_obj_set_width(label_msg_title,240);
      lv_label_set_text(label_msg_title, "");
      lv_label_set_text(label_msg_title, string2char(get_titl_msg()));
      lv_obj_align(label_msg_title, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 25);

      label_msg_body = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_long_mode(label_msg_body, LV_LABEL_LONG_BREAK);
      lv_obj_set_width(label_msg_body,240);
      lv_label_set_text(label_msg_body, "");
      lv_label_set_text(label_msg_body, string2char(get_body_msg()));
      lv_obj_align(label_msg_body, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 50);


    }

    virtual void main()
    {
      lv_label_set_text(label_msg_name, string2char(get_name_msg()));
      lv_label_set_text(label_msg_title, string2char(get_titl_msg()));
      lv_label_set_text(label_msg_body, string2char(get_body_msg()));
    }

    virtual void long_click()
    {
      display_home();
    }

    virtual void left()
    {
      display_home();
    }

    virtual void right()
    {
      display_home();
    }

    virtual void up()
    {
      display_home();
    }
    virtual void down()
    {
      display_home();
    }

    virtual void click(touch_data_struct touch_data)
    {
      display_home();
    }

  private:
    lv_obj_t *label, *label_msg_body, *label_msg_name, *label_msg_title, *label_msg;

    char* string2char(String command) {
      if (command.length() != 0) {
        char *p = const_cast<char*>(command.c_str());
        return p;
      }
    }
};

NotifyScreen notifyScreen;
