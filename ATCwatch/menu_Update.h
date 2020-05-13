
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


class UpdateScreen : public TheScreen
{
  public:
    UpdateScreen() {
    }

    virtual void pre()
    {
      drawYesNoButton("Bootloader ?");
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
          start_bootloader(true);
          break;
        case 2:
          set_last_menu();
          break;
      }
    }

  private:

};
