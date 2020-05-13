
#pragma once
#include "Arduino.h"
#include "class.h"
#include "menu.h"

class TheScreen : public Screen
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
};


class DemoScreen : public Screen
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

};
