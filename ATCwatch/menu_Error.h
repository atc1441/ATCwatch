#pragma once
#include "Arduino.h"
#include "class.h"
#include "images.h"
#include "menu.h"
#include "display.h"
#include "menuAppsBase.h"
#include "ble.h"
#include "time.h"
#include "battery.h"
#include "accl.h"
#include "push.h"
#include "heartrate.h"


class ErrorScreen : public TheScreen
{
  public:
    ErrorScreen() {
    }

    virtual void pre()
    {
      displayRect(0, 0, 240, 240, 0x0000);
      displayPrintln(0, 0, "Error", 0xFFFF, 0x0000, 2);
      displayPrintln(0, 16, "Something when wrong", 0xFFFF, 0x0000, 2);
      displayPrintln(0, 16 + 16, "Not available Menu selected", 0xFFFF, 0x0000, 2);
    }

    virtual void main()
    {

    }
    virtual void up()
    {
      display_home();
    }

    virtual void down()
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

    virtual void click(touch_data_struct touch_data)
    {
      display_home();
    }

    virtual void long_click(touch_data_struct touch_data)
    {
      display_home();
    }

  private:

};
