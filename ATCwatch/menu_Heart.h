
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
#include "inputoutput.h"
#include "heartrate.h"


class HeartScreen : public TheScreen
{
  public:
    HeartScreen() {
    }

    virtual void pre()
    {
      start_hrs3300();
      displayRect(0, 0, 240, 240, 0x0000);
      displayPrintln(0, 0, "Heartrate:", 0xFFFF, 0x0000, 2);
      displayImage(120 - (72 / 2), 240-72, 72, 72, symbolHeart);
      displayPrintln(0, 50, "Last HR:", 0xFFFF, 0x0000, 2);
    }

    virtual void main()
    {
      byte hr = get_heartrate();
      switch (hr) {
        case 0:
        case 255:
          break;
        case 254:
          displayPrintln(0, 20, "No Touch      ", 0xFFFF, 0x0000, 2);
          break;
        case 253:
          displayPrintln(0, 20, "Please Wait   ", 0xFFFF, 0x0000, 2);
          break;
        default:
          displayPrintln(0, 20, (String)hr + "          ", 0xFFFF, 0x0000, 2);
          break;
      }
      displayPrintln(0, 70, (String)get_last_heartrate() + "   ", 0xFFFF, 0x0000, 2);
    }

    virtual void post()
    {
      end_hrs3300();
    }

    virtual uint32_t sleepTime()
    {
      return 50000;
    }

  private:


};
