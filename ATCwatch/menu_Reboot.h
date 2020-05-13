
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
#include "buttonYesNo.h"


class RebootScreen : public TheScreen
{
  public:
    RebootScreen() {
    }

    virtual void pre()
    {
      drawYesNoButton("Reboot ?");
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
      switch (checkYesNoButtonClick(touch_data.xpos, touch_data.ypos)) {
        case 1:
          set_reboot();
          break;
        case 2:
          set_last_menu();
          break;
      }
    }

  private:

};
