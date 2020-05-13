
#pragma once
#include "Arduino.h"
#include "menu.h"

#define DEFAULT_SLEEP_TIMEOUT 10000
#define DEFAULT_REFRESH_TIME 40

class Screen
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
    virtual uint32_t sleepTime()
    {
      return DEFAULT_SLEEP_TIMEOUT;
    }
    
    virtual uint32_t refreshTime()
    {
      return DEFAULT_REFRESH_TIME;
    }
};
