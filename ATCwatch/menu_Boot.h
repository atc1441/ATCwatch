
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


class BootScreen : public TheScreen
{
  public:
    BootScreen() {
    }

    virtual void pre()
    {
      displayImage(96, 96, 48, 48, image2);
      displayPrintln(10, 10, "Booting", 0xFFFF, 0x0000, 3);
    }

    virtual void main()
    {

    }

  private:
};
