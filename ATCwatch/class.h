/*
   Copyright (c) 2020 Aaron Christophel

   SPDX-License-Identifier: GPL-3.0-or-later
*/

#pragma once
#include "Arduino.h"
#include "class_def.h"
#include "inputoutput.h"
#include "sleep.h"
#include "menu.h"

class Screen : public Screen_def
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
      set_last_menu();
    }

    virtual void click(touch_data_struct touch_data)
    {
    }

    virtual void long_click(touch_data_struct touch_data)
    {
    }

    virtual void button_push(int length)
    {
      display_home();
      set_motor_ms(40);
      set_sleep_time();
    }
};
