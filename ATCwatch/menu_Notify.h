
#pragma once
#include "Arduino.h"
#include "classScreen.h"
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


class NotifyScreen : public TheScreen
{
  public:
    NotifyScreen() {
    }

    virtual void pre()
    {
      displayRect(0, 0, 240, 240, 0x0000);
      displayPrintln(0, 0, "Notification:");
      displayImage(120 - (72 / 2), 240-72, 72, 72, symbolMsg);
    }

    virtual void main()
    {
      String notification = get_push_msg();
      if (last_notification != notification) {
        last_notification = notification;
        displayRect(0, 9, 240, (150 - 9), 0x0000);
        displayPrintln(0, 10, notification, 0xFFFF, 0x0000, 2);
      }
    }

    virtual void post()
    {
      last_notification = "";
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
    String last_notification = "";
};
