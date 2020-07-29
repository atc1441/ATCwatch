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


class DemoScreen : public Screen
{
  public:
    virtual void pre()
    {
      set_swipe_enabled(true);

      label = lv_label_create(lv_scr_act(), NULL);
      lv_label_set_text(label, "Demo");
      lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
      

      slider = lv_slider_create(lv_scr_act(), NULL);
      lv_obj_align(slider, NULL, LV_ALIGN_CENTER, 0, 0);
    }

    virtual void main()
    {
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

  private:
    lv_obj_t *label, *slider;
};

DemoScreen demoScreen;
