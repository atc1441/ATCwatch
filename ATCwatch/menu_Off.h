
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


class OffScreen : public TheScreen
{
  public:
    OffScreen() {
    }

    virtual void pre()
    {
      drawYesNoButton("Schutdown ?");
    }

    virtual void main()
    {

    }

    virtual void click(touch_data_struct touch_data)
    {
      switch (checkYesNoButtonClick(touch_data.xpos, touch_data.ypos)) {
        case 1:
          system_off();
          break;
        case 2:
          set_last_menu();
          break;
      }
    }

  private:

};
