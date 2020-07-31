/*
 * Copyright (c) 2020 Aaron Christophel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once
#include "Arduino.h"
#include "menu.h"
#include <lvgl.h>

#define DEFAULT_SLEEP_TIMEOUT 10000
#define DEFAULT_REFRESH_TIME 40

class Screen_def
{
  public:
    virtual void pre()
    {
    }

    virtual void main()
    {
    }

    virtual void post()
    {
    }

    virtual void up()
    {
    }

    virtual void down()
    {
    }

    virtual void left()
    {
    }

    virtual void right()
    {
    }

    virtual void click(touch_data_struct touch_data)
    {
    }

    virtual void long_click(touch_data_struct touch_data)
    {
    }
    
    virtual void button_push(int length)
    {
    }

    virtual uint32_t sleepTime()
    {
      return DEFAULT_SLEEP_TIMEOUT;
    }
    
    virtual uint32_t refreshTime()
    {
      return DEFAULT_REFRESH_TIME;
    }
    
    virtual void lv_event_class(lv_obj_t * object, lv_event_t event)
    {
      
    }

    virtual void pre_display()
    {
      lv_obj_clean(lv_scr_act());
    }    
};
