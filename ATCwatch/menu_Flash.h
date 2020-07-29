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
#include "flash.h"
#include "heartrate.h"
#include "screen_style.h"


class FlashScreen : public Screen
{
  public:
    virtual void pre()
    {
      label = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text(label, "Flash");
      lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 10, 0);

      label_x = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text(label_x, "0x0000000000000000");
      lv_obj_align(label_x, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 25);

      label_y = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text_fmt(label_y, "0x%04X%", flash_read_id());
      lv_obj_align(label_y, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 45);

    }

    virtual void main()
    {
      get_temp(temp);
      lv_label_set_text_fmt(label_x, "0x%02X%02X%02X%02X%02X%02X%02X%02X", temp[0], temp[1], temp[2], temp[3], temp[4], temp[5], temp[6], temp[7]);

    }

    virtual void right()
    {
      set_last_menu();
    }

    virtual void up()
    {
      flash_sleep(true);
    }

    virtual void down()
    {
      flash_sleep(false);
    }

  private:
      uint8_t temp[8];
    lv_obj_t *label, *label_x, *label_y;
};

FlashScreen flashScreen;
