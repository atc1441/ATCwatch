
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
#include "backlight.h"


class DebugScreen : public TheScreen
{
  public:
    DebugScreen() {
    }

    virtual void pre()
    {
      displayRect(0, 0, 240, 240, 0x0000);
      displayPrintln(0, 0, "Debug:", 0xFF00, 0x0000, 2);
      displayImage(120 - (72 / 2), 240-72, 72, 72, symbolDebug);
      displayPrintln(0, 120-16, (String)NRF_POWER->RESETREAS, 0xFFFF, 0x0000, 2);
      displayPrintln(0, 120, "ÄÜÖäüöß!§$%&/()", 0xFFFF, 0x0000, 2);
      
      
      
      }

    virtual void main()
    {
      displayPrintln(0, 20, (String)millis() + "      ", 0xFFFF, 0x0000, 2);
      displayPrintln(0, 20 + 16, (String)(millis() / 1000) + "      ", 0xFFFF, 0x0000, 2);
      displayPrintln(0, 20 + 16 + 16, (String)(millis() / 1000 / 60) + "      ", 0xFFFF, 0x0000, 2);
      displayPrintln(0, 20 + 16 + 16 + 16, (String)(millis() / 1000 / 60 / 60) + "      ", 0xFFFF, 0x0000, 2);

      
    }

  private:


};
