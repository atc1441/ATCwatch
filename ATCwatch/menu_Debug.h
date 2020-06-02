
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
#include "sleep.h"
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
      displayPrintln(0, 20, "Uptime:", 0xFFFF, 0x0000, 2);
      displayPrintln(0, 120 - 16, "Reset: " + (String)NRF_POWER->RESETREAS, 0xFFFF, 0x0000, 2);
      displayPrintln(0, 120, "Wakeup: ", 0xFFFF, 0x0000, 2);
      displayImage(120 - (72 / 2), 240 - 72, 72, 72, symbolDebug);
    }

    virtual void main()
    {
      long days = 0;
      long hours = 0;
      long mins = 0;
      long secs = 0;
      secs = millis() / 1000;
      mins = secs / 60;
      hours = mins / 60;
      days = hours / 24;
      secs = secs - (mins * 60);
      mins = mins - (hours * 60);
      hours = hours - (days * 24);


      displayPrintln(0, 20 + 16, (String)millis() + "      ", 0xFFFF, 0x0000, 2);
      displayPrintln(0, 20 + 16 + 16, String(days) + " " + (String)hours + ":" + (String)mins + ":" + (String)secs + "     ", 0xFFFF, 0x0000, 2);
      displayPrintln((9 * 5 * 2), 120, (String)wakeup_reason[get_wakeup_reason()], 0xFFFF, 0x0000, 2);
    }

  private:
    String wakeup_reason[10] = {"Unset", "Push", "Connect", "Disconnect", "Charged", "Charge", "Button", "Touch", "Accl", "AcclINT"};

};
